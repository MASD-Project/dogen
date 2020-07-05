/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/types/features/physical.hpp"
#include "dogen.logical/types/features/physical_relations.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/helpers/name_builder.hpp"
#include "dogen.logical/types/entities/physical/part.hpp"
#include "dogen.logical/types/entities/physical/facet.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/entities/physical/constant_relation.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/physical_entities_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.physical_entities_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string separator(".");
const std::string meta_model_name("masd");
const std::string relation_status_not_relatable("not_relatable");
const std::string relation_status_relatable("relatable");
const std::string relation_status_facet_default("facet_default");

const std::string varibale_relation_type_self("self");
const std::string varibale_relation_type_parent("parent");
const std::string varibale_relation_type_child("child");
const std::string varibale_relation_type_transparent("transparent");
const std::string varibale_relation_type_opaque("opaque");
const std::string varibale_relation_type_associative_key("associative_key");
const std::string varibale_relation_type_visitation("visitation");

const std::string invalid_relation_status(
    "Relation status is not valid: ");
const std::string ambiguous_name("Name maps to more than one element type:");
const std::string unsupported_composition(
    "Physical element composition is not supported: ");
const std::string duplicate_part_id("Duplicate part ID: ");
const std::string missing_part("Part could not be located: ");
const std::string missing_logical_meta_element(
    "Meta-element name not supplied.");
const std::string uncontained_archetype(
    "Archetype must be contained by a backend and a facet. Name: ");
const std::string uncontained_facet(
    "Facet must be contained by a backend. Name: ");
const std::string uncontained_part(
    "Parts must be contained by a backend. Name: ");
const std::string uncontained_archetype_kind(
    "Archetype kind must be contained by a backend. Name: ");
const std::string invalid_constant_relation(
    "Constant relation must have 2 or 3 parameters. Found: ");
const std::string invalid_variable_relation(
    "Variable relations must have 2 parameters. Found: ");
const std::string invalid_label("Label must have a key and a value. Found: ");
const std::string invalid_relation_type("Invalid relation type: ");

}

namespace dogen::logical::transforms {

void physical_entities_transform::
process_backends(const context& ctx, entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Processing backends.";
    using features::physical;
    const auto& pe(m.physical_elements());
    const auto& fm(*ctx.feature_model());
    const auto fg(physical::make_feature_group(fm));

    auto& bs(pe.backends());
    for (auto& pair : bs) {
        BOOST_LOG_SEV(lg, debug) << "Processing: " << pair.first;
        auto& b(*pair.second);
        const auto scfg(physical::make_static_configuration(fg, b));
        b.backend_name(scfg.backend_name);
        b.meta_model_name(meta_model_name);

        /*
         * Generate the ID for this backend.
         */
        std::ostringstream os;
        os << meta_model_name << separator << b.backend_name();
        b.id(os.str());
        BOOST_LOG_SEV(lg, debug) << "ID: " << b.id();

        /*
         * Read the technical space.
         */
        using boost::lexical_cast;
        using entities::technical_space;
        const auto mts(scfg.major_technical_space);
        BOOST_LOG_SEV(lg, debug) << "Major technical space: " << mts;
        b.major_technical_space(lexical_cast<technical_space>(mts));

        bool found(false);
        for (const auto& qn : b.contains()) {
            /*
             * Check to see if the contained element is a facet, and
             * if so add it to the facets container.
             */
            found = false;
            const auto& fcts(pe.facets());
            const auto i(fcts.find(qn));
            if (i != fcts.end()) {
                auto& fct(*i->second);
                b.facets().push_back(fct.name());
                fct.backend_name(b.backend_name());
                fct.major_technical_space(b.major_technical_space());
                found = true;
                BOOST_LOG_SEV(lg, debug) << "Contains facet: "
                                         << fct.name().qualified().dot();
            }

            /*
             * Check to see if the contained element is a part, and
             * if so add it to the parts container.
             */
            const auto& parts(pe.parts());
            const auto j(parts.find(qn));
            if (j != parts.end()) {
                if (found) {
                    BOOST_LOG_SEV(lg, error) << ambiguous_name << qn;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(ambiguous_name + qn));
                }

                auto& part(*j->second);
                b.parts().push_back(part.name());
                part.backend_name(b.backend_name());
                part.major_technical_space(b.major_technical_space());
                found = true;
                BOOST_LOG_SEV(lg, debug) << "Contains part: "
                                         << part.name().qualified().dot();
            }

            /*
             * Check to see if the contained element is an archetype
             * kind, and if so add it to the archetype kinds
             * container.
             */
            const auto& aks(pe.archetype_kinds());
            const auto k(aks.find(qn));
            if (k != aks.end()) {
                if (found) {
                    BOOST_LOG_SEV(lg, error) << ambiguous_name << qn;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(ambiguous_name + qn));
                }

                auto& ak(*k->second);
                b.archetype_kinds().push_back(ak.name());
                ak.major_technical_space(b.major_technical_space());
                ak.backend_name(b.backend_name());
                BOOST_LOG_SEV(lg, debug) << "Contains archetype kind: "
                                         << ak.name().qualified().dot();
            }

            /*
             * Backends cannot contain backends or archetypes. Note
             * also that we are letting through any other kind of
             * meta-model element here. This is just to make our life
             * easier - one can use all other regular types without
             * being hindered.
             */
            const bool is_backend(bs.find(qn) != bs.end());
            const auto& archs(pe.archetypes());
            const bool is_archetype(archs.find(qn) != archs.end());
            if (is_backend || is_archetype) {
                BOOST_LOG_SEV(lg, error) << unsupported_composition << qn
                                         << " Container: "
                                         << b.name().qualified().dot();
                BOOST_THROW_EXCEPTION(
                    transformation_error(unsupported_composition + qn));
            }
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished processing backends.";
}

void physical_entities_transform::process_facets(entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Processing facets.";
    using features::physical;
    const auto& pe(m.physical_elements());
    auto& fcts(pe.facets());
    for (auto& pair : fcts) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing: " << id;
        auto& fct(*pair.second);
        fct.meta_model_name(meta_model_name);

        /*
         * Facets can only exist in the context of a backend.
         */
        if (fct.backend_name().empty()) {
            BOOST_LOG_SEV(lg, error) << uncontained_facet << id;
            BOOST_THROW_EXCEPTION(transformation_error(uncontained_facet + id));
        }

        /*
         * Generate the ID for this facet.
         */
        std::ostringstream os;
        os << meta_model_name << separator
           << fct.backend_name() << separator
           << fct.name().simple();
        fct.id(os.str());
        BOOST_LOG_SEV(lg, debug) << "ID: " << fct.id();

        /*
         * Check all of the elements contained within this facet.
         */

        for (const auto& qn : fct.contains()) {
            /*
             * Check to see if the contained element is an archetype,
             * and if so add it to the facets container.
             */
            const auto& archs(pe.archetypes());
            const auto i(archs.find(qn));
            if (i != archs.end()) {
                auto& arch(*i->second);
                fct.archetypes().push_back(arch.name());
                arch.facet_name(fct.name().simple());
                arch.backend_name(fct.backend_name());
                arch.major_technical_space(fct.major_technical_space());
                BOOST_LOG_SEV(lg, debug) << "Contains archetype: "
                                         << arch.name().qualified().dot();
            }

            /*
             * Facets cannot contain any other kind of physical
             * elements. As with backends, note that we are letting
             * through any other kind of meta-model element here. This
             * is just to make our life easier - one can use all other
             * regular types without being hindered.
             */
            const auto& bs(pe.backends());
            const bool is_backend(bs.find(qn) != bs.end());
            const auto& fcts(pe.facets());
            const bool is_facet(fcts.find(qn) != fcts.end());
            const auto& parts(pe.parts());
            const bool is_part(parts.find(qn) != parts.end());
            const auto& aks(pe.archetype_kinds());
            const bool is_ak(aks.find(qn) != aks.end());
            if (is_backend || is_facet || is_part || is_ak) {
                BOOST_LOG_SEV(lg, error) << unsupported_composition << qn
                                         << " Container: "
                                         << fct.name().qualified().dot();
                BOOST_THROW_EXCEPTION(
                    transformation_error(unsupported_composition + qn));
            }
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished processing facets.";
}

void physical_entities_transform::process_archetype_kinds(entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Processing archetype kinds.";
    const auto& pe(m.physical_elements());
    auto& aks(pe.archetype_kinds());
    for (auto& pair : aks) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing: " << id;
        auto& ak(*pair.second);
        ak.meta_model_name(meta_model_name);

        /*
         * Archetype kinds can only exist in the context of a backend.
         */
        if (ak.backend_name().empty()) {
            BOOST_LOG_SEV(lg, error) << uncontained_archetype_kind << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(uncontained_archetype_kind + id));
        }

        /*
         * Generate the ID for this archetype kind.
         */
        std::ostringstream os;
        os << meta_model_name << separator
           << ak.backend_name() << separator
           << ak.name().simple();
        ak.id(os.str());
        BOOST_LOG_SEV(lg, debug) << "ID: " << ak.id();
    }
    BOOST_LOG_SEV(lg, debug) << "Finished processing archetype kinds.";
}

void physical_entities_transform::process_parts(entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Processing parts.";
    const auto& pe(m.physical_elements());
    auto& parts(pe.parts());
    for (auto& pair : parts) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing: " << id;
        auto& part(*pair.second);
        part.meta_model_name(meta_model_name);

        /*
         * Parts can only exist in the context of a backend.
         */
        if (part.backend_name().empty()) {
            BOOST_LOG_SEV(lg, error) << uncontained_part << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(uncontained_part + id));
        }

        /*
         * Generate the ID for this part.
         */
        std::ostringstream os;
        os << meta_model_name << separator
           << part.backend_name() << separator
           << part.name().simple();
        part.id(os.str());
        BOOST_LOG_SEV(lg, debug) << "ID: " << part.id();
    }
    BOOST_LOG_SEV(lg, debug) << "Finished processing parts.";
}

entities::physical::relations
physical_entities_transform::process_relations(const context& ctx,
    const variability::entities::configuration& cfg) {
    using features::physical_relations;
    const auto& fm(*ctx.feature_model());
    const auto fg(physical_relations::make_feature_group(fm));
    const auto scfg(physical_relations::make_static_configuration(fg, cfg));

    /*
     * Read and validate the relation status. For now we ignore empty
     * relation status. This is because the generators are not
     * populating it.
     */
    entities::physical::relations r;
    const auto rs(scfg.relation_status);
    if (!rs.empty()) {
        const bool is_valid_rs(
            rs == relation_status_not_relatable ||
            rs == relation_status_relatable ||
            rs == relation_status_facet_default);

        if (!is_valid_rs) {
            BOOST_LOG_SEV(lg, error) << invalid_relation_status << rs;
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_relation_status + rs));
        }
        r.status(rs);
    }

    /*
     * Process the constant relations. These are CSV values with
     * either 2 or three fields. The first field is the logical
     * model element ID, the second field the original URN and the
     * final, possibly optional field, is a colon separated label.
     */
    for (const auto& cr : scfg.constant_relation) {
        const auto sz(cr.size());
        if (sz != 2 && sz != 3) {
            std::ostringstream os;
            os << invalid_constant_relation << cr;
            const auto s(os.str());

            BOOST_LOG_SEV(lg, error) << s;
            BOOST_THROW_EXCEPTION(transformation_error(s));
        }

        /*
         * Read the logical model meta-element ID we are related to.
         */
        auto i(cr.begin());
        entities::physical::constant_relation lcr;
        lcr.logical_model_element_id(*i);

        /*
         * Read the URN, as it was originally supplied by the user.
         */
        ++i;
        lcr.original_urn(*i);

        /*
         * If present, read the label.
         */
        if (sz == 3) {
            ++i;
            const auto s(*i);
            using utility::string::splitter;
            const auto splitted(splitter::split_delimited(s, ":"));
            if (splitted.size() != 2) {
                BOOST_LOG_SEV(lg, error) << invalid_label << s;
                BOOST_THROW_EXCEPTION(transformation_error(invalid_label + s));
            }
            entities::label lbl;
            lbl.key(splitted.front());
            lbl.value(splitted.back());
            lcr.labels().push_back(lbl);
        }
        r.constant().push_back(lcr);
    }

    /*
     * Process the variable relations. These are CSV values with
     * 2 fields. The first field is the original URN and the
     * second is the relation type.
     */
    for (const auto& vr : scfg.variable_relation) {
        const auto sz(vr.size());
        if (sz != 2) {
            std::ostringstream os;
            os << invalid_variable_relation << vr;
            const auto s(os.str());

            BOOST_LOG_SEV(lg, error) << s;
            BOOST_THROW_EXCEPTION(transformation_error(s));
        }

        /*
         * Read the relation type.
         */
        auto i(vr.begin());
        const auto rt(*i);
        if (rt != varibale_relation_type_self &&
            rt != varibale_relation_type_parent &&
            rt != varibale_relation_type_child &&
            rt != varibale_relation_type_transparent &&
            rt != varibale_relation_type_opaque &&
            rt != varibale_relation_type_associative_key &&
            rt != varibale_relation_type_visitation) {
            BOOST_LOG_SEV(lg, error) << invalid_relation_type << rt;
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_relation_type + rt));
        }

        entities::physical::variable_relation lvr;
        lvr.type(rt);

        /*
         * Read the URN, as it was originally supplied by the user.
         */
        ++i;
        lvr.original_urn(*i);
        r.variable().push_back(lvr);
    }
    return r;
}

void physical_entities_transform::
process_archetypes(const context& ctx, entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Processing archetypes.";

    using features::physical;
    const auto& pe(m.physical_elements());
    const auto& fm(*ctx.feature_model());
    const auto fg(physical::make_feature_group(fm));

    /*
     * First, we organise the parts by their IDs.
     */
    const auto& parts(pe.parts());
    std::unordered_map<std::string,
                       boost::shared_ptr<entities::physical::part>>
        parts_by_ids;
    for (const auto& pair : parts) {
        const auto& part(*pair.second);
        const auto id(part.id());
        const auto new_pair(std::make_pair(id, pair.second));
        const auto inserted(parts_by_ids.insert(new_pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_part_id << part.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_part_id + part.id()));
        }
    }

    /*
     * Now we can process the archetypes proper.
     */
    auto& archs(pe.archetypes());
    for (auto& pair : archs) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing: " << id;
        auto& arch(*pair.second);

        /*
         * The meta-model name is hard-coded as we only support one.
         */
        arch.meta_model_name(meta_model_name);

        /*
         * Read all of the associated meta-data. First we get the
         * logical model meta-element ID. It must not be empty, but
         * otherwise We don't validate it here - this will be done
         * later on.
         */
        const auto scfg(physical::make_static_configuration(fg, arch));
        arch.part_id(scfg.part_id);
        const auto lmen(scfg.logical_meta_element_id);
        if (lmen.empty()) {
            BOOST_LOG_SEV(lg, error) << missing_logical_meta_element;
            BOOST_THROW_EXCEPTION(
                transformation_error(missing_logical_meta_element));
        }
        arch.logical_meta_element_id(lmen);

        /*
        * Read all relations for both the archetype and its generator.
        */
        arch.relations(process_relations(ctx, *arch.configuration()));
        auto& g(arch.generator());
        g.relations(process_relations(ctx, *g.configuration()));

        /*
         * Read the reference to a wale template. Its existence will
         * be validated later on during resolution. It may be empty
         * since not all archetypes need a wale template.
         */
        const auto wtr(scfg.wale_template_reference);
        if (!wtr.empty()) {
            const auto n(helpers::name_builder::build(wtr));
            arch.generator().wale_template(n);
        }

        /*
         * Archetypes can only exist in the context of a backend and a
         * facet.
         */
        if (arch.backend_name().empty() || arch.facet_name().empty()) {
            BOOST_LOG_SEV(lg, error) << uncontained_archetype << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(uncontained_archetype + id));
        }

        /*
         * Generate the ID for this archetype.
         */
        std::ostringstream os;
        const auto sn(arch.name().simple());
        os << meta_model_name << separator
           << arch.backend_name() << separator
           << arch.facet_name() << separator << sn;
        arch.id(os.str());
        BOOST_LOG_SEV(lg, debug) << "ID: " << arch.id();

        /*
         * Locate the containing part and update it.
         */
        const auto qn(arch.name().qualified().dot());
        const auto pid(arch.part_id());
        const auto j(parts_by_ids.find(pid));
        if (j == parts_by_ids.end()) {
            BOOST_LOG_SEV(lg, error) << missing_part << pid;
            BOOST_THROW_EXCEPTION(transformation_error(missing_part + pid));
        }

        auto& part(*j->second);
        part.archetypes().push_back(arch.name());
    }
    BOOST_LOG_SEV(lg, debug) << "Finished processing archetypes.";
}

void physical_entities_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "physical entities transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    process_backends(ctx, m);
    process_facets(m);
    process_archetype_kinds(m);
    process_parts(m);
    process_archetypes(ctx, m);

    stp.end_transform(m);
}

}
