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
#include <boost/throw_exception.hpp>
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/io/type_io.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/optional_io.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.generation/io/meta_model/model_io.hpp"
#include "masd.dogen.generation/io/meta_model/element_archetype_io.hpp"
#include "masd.dogen.generation/io/meta_model/backend_properties_io.hpp"
#include "masd.dogen.generation/io/meta_model/facet_properties_io.hpp"
#include "masd.dogen.generation/io/meta_model/archetype_properties_io.hpp"
#include "masd.dogen.coding/io/meta_model/local_archetype_location_properties_io.hpp"
#include "masd.dogen.generation/types/transforms/transformation_error.hpp"
#include "masd.dogen.generation/types/transforms/archetype_location_properties_transform.hpp"

namespace {

const std::string transform_id(
    "generation.transforms.archetype_location_properties_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string type_group_not_found(
    "Could not find a type group for archetype: ");
const std::string backend_not_found("Could not find backend: ");
const std::string facet_not_found("Could not find facet: ");
const std::string archetype_not_found("Could not find archetype: ");

}

namespace masd::dogen::generation::transforms {

inline std::ostream& operator<<(std::ostream& s,
    const archetype_location_properties_transform::backend_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"coding::transform::"
      << "archetype_location_properties_transform::backend_type_group\"" << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"directory\": " << v.directory
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s,
    const archetype_location_properties_transform::facet_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"coding::transform::"
      << "archetype_location_properties_transform::facet_type_group\"" << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"overwrite\": " << v.overwrite << ", "
      << "\"directory\": " << v.directory << ", "
      << "\"postfix\": " << v.postfix
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s, const
    archetype_location_properties_transform::global_archetype_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"coding::transform::"
      << "archetype_location_properties_transform::global_archetype_type_group\""
      << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"overwrite\": " << v.overwrite << ", "
      << "\"postfix\": " << v.postfix
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s, const
    archetype_location_properties_transform::local_archetype_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"coding::transform::"
      << "archetype_location_properties_transform::local_archetype_type_group\""
      << ", "
      << "\"facet_enabled\": " << v.facet_enabled << ", "
      << "\"archetype_enabled\": " << v.archetype_enabled << ", "
      << "\"facet_overwrite\": " << v.facet_overwrite << ", "
      << "\"archetype_overwrite\": " << v.archetype_overwrite
      << " }";

    return s;
}

std::unordered_map<std::string,
                   archetype_location_properties_transform::backend_type_group>
archetype_location_properties_transform::
make_backend_type_group(const variability::type_repository& atrp,
    const archetypes::location_repository& alrp) {
    std::unordered_map<std::string, backend_type_group> r;

    const variability::type_repository_selector s(atrp);
    for (const auto& pair : alrp.facet_names_by_backend_name()) {
        const auto& backend(pair.first);
        backend_type_group btg;
        const auto ebl(coding::traits::enabled());
        btg.enabled = s.select_type_by_name(backend, ebl);

        const auto dir(coding::traits::directory());
        btg.directory = s.select_type_by_name(backend, dir);

        r.insert(std::make_pair(backend, btg));
    }
    return r;
}

std::unordered_map<std::string,
                   archetype_location_properties_transform::facet_type_group>
archetype_location_properties_transform::
make_facet_type_group(const variability::type_repository& atrp,
    const archetypes::location_repository& alrp) {
    std::unordered_map<std::string, facet_type_group> r;

    const variability::type_repository_selector s(atrp);
    for (const auto& pair : alrp.facet_names_by_backend_name()) {
        for (const auto& fct : pair.second) {
            facet_type_group ftg;
            const auto ebl(coding::traits::enabled());
            ftg.enabled = s.select_type_by_name(fct, ebl);

            const auto ow(coding::traits::overwrite());
            ftg.overwrite = s.select_type_by_name(fct, ow);

            ftg.directory = s.try_type_field_by_name(fct,
                coding::traits::directory());
            ftg.postfix = s.try_type_field_by_name(fct,
                coding::traits::postfix());

            r.insert(std::make_pair(fct, ftg));
        }
    }
    return r;
}

std::unordered_map<
    std::string,
    archetype_location_properties_transform::global_archetype_type_group>
archetype_location_properties_transform::
make_global_archetype_type_group(const variability::type_repository& atrp,
    const archetypes::location_repository& alrp) {
    std::unordered_map<std::string, global_archetype_type_group> r;

    const variability::type_repository_selector s(atrp);
    for (const auto& al : alrp.all()) {
        global_archetype_type_group gatg;
        const auto ebl(coding::traits::enabled());
        gatg.enabled = s.select_type_by_name(al.archetype(), ebl);

        const auto ow(coding::traits::overwrite());
        gatg.overwrite = s.select_type_by_name(al.archetype(), ow);

        const auto postfix(coding::traits::postfix());
        gatg.postfix = s.select_type_by_name(al.archetype(), postfix);

        r.insert(std::make_pair(al.archetype(), gatg));
    }
    return r;
}


std::unordered_map<
    std::string,
    archetype_location_properties_transform::local_archetype_type_group>
archetype_location_properties_transform::
make_local_archetype_type_group(const variability::type_repository& atrp,
    const archetypes::location_repository& alrp) {
    std::unordered_map<std::string, local_archetype_type_group> r;

    const variability::type_repository_selector s(atrp);
    for (const auto& al : alrp.all()) {
        local_archetype_type_group latg;
        const auto ebl(coding::traits::enabled());
        latg.facet_enabled = s.select_type_by_name(al.facet(), ebl);
        latg.archetype_enabled = s.select_type_by_name(al.archetype(), ebl);

        const auto ow(coding::traits::overwrite());
        latg.facet_overwrite = s.select_type_by_name(al.facet(), ow);
        latg.archetype_overwrite = s.select_type_by_name(al.archetype(), ow);

        r.insert(std::make_pair(al.archetype(), latg));
    }
    return r;
}

std::unordered_map<std::string, meta_model::backend_properties>
archetype_location_properties_transform::obtain_backend_properties(
    const std::unordered_map<std::string, backend_type_group>& tgs,
    const variability::annotation& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating backend properties.";

    std::unordered_map<std::string, meta_model::backend_properties> r;
    const variability::entry_selector s(ra);
    for (const auto& pair : tgs) {
        const auto& backend(pair.first);
        const auto& tg(pair.second);

        meta_model::backend_properties bp;
        bp.enabled(s.get_boolean_content_or_default(tg.enabled));
        bp.directory(s.get_text_content_or_default(tg.directory));

        r[backend] = bp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created backend properties. Result: " << r;
    return r;
}

std::unordered_map<std::string, meta_model::facet_properties>
archetype_location_properties_transform::obtain_facet_properties(
    const std::unordered_map<std::string, facet_type_group>& tgs,
    const variability::annotation& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating facet properties.";

    std::unordered_map<std::string, meta_model::facet_properties> r;
    const variability::entry_selector s(ra);
    for (const auto& pair : tgs) {
        const auto& facet(pair.first);
        const auto& tg(pair.second);

        meta_model::facet_properties fp;
        fp.enabled(s.get_boolean_content_or_default(tg.enabled));
        fp.overwrite(s.get_boolean_content_or_default(tg.overwrite));
        if (tg.directory)
            fp.directory(s.get_text_content_or_default(*tg.directory));

        if (tg.postfix)
            fp.postfix(s.get_text_content_or_default(*tg.postfix));

        r[facet] = fp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created facet properties. Result: " << r;
    return r;
}

std::unordered_map<std::string, meta_model::archetype_properties>
archetype_location_properties_transform::obtain_archetype_properties(
    const std::unordered_map<std::string, global_archetype_type_group>& tgs,
    const variability::annotation& ra) {

    BOOST_LOG_SEV(lg, debug) << "Creating archetype properties.";

    std::unordered_map<std::string, meta_model::archetype_properties> r;
    const variability::entry_selector s(ra);
    for (const auto& pair : tgs) {
        const auto& archetype(pair.first);
        const auto& tg(pair.second);

        meta_model::archetype_properties ap;
        ap.enabled(s.get_boolean_content_or_default(tg.enabled));
        if (s.has_entry(tg.overwrite))
            ap.overwrite(s.get_boolean_content(tg.overwrite));

        ap.postfix(s.get_text_content_or_default(tg.postfix));

        r[archetype] = ap;
    }

    BOOST_LOG_SEV(lg, debug) << "Created archetype properties. Result: " << r;
    return r;
}

void archetype_location_properties_transform::
populate_global_archetype_location_properties(
    const variability::type_repository& atrp,
    const archetypes::location_repository& alrp,
    meta_model::model& m) {

    const auto btg(make_backend_type_group(atrp, alrp));
    const auto ftg(make_facet_type_group(atrp, alrp));
    const auto atg(make_global_archetype_type_group(atrp, alrp));

    const auto& ra(m.root_module()->annotation());
    auto& galp(m.global_archetype_location_properties());
    galp.backend_properties(obtain_backend_properties(btg, ra));
    galp.facet_properties(obtain_facet_properties(ftg, ra));
    galp.archetype_properties(obtain_archetype_properties(atg, ra));

    /*
     * Now populate the denormalised archetype properties by querying
     * the containers we've already populated.
     */
    for (const auto& backend_pair : alrp.by_backend_by_facet()) {
        /*
         * First we locate the backend for the current batch of
         * artchetype locations.
         */
        const auto& bn(backend_pair.first);
        const auto i(galp.backend_properties().find(bn));
        if (i == galp.backend_properties().end()) {
            BOOST_LOG_SEV(lg, error) << backend_not_found << bn;
            BOOST_THROW_EXCEPTION(transformation_error(backend_not_found + bn));
        }
        const auto& backend(i->second);

        /*
         * Next we loop through all of its facets and locate each facet.
         */
        for (const auto& facet_pair : backend_pair.second) {
            const auto& fn(facet_pair.first);
            const auto j(galp.facet_properties().find(fn));
            if (j == galp.facet_properties().end()) {
                BOOST_LOG_SEV(lg, error) << facet_not_found << fn;
                BOOST_THROW_EXCEPTION(
                    transformation_error(facet_not_found + fn));
            }
            const auto& facet(j->second);

            /*
             * Finally we can loop through all of the archetype
             * locations owned by both this backend and facet and
             * populate the denormalised properties.
             */
            for (const auto& an : facet_pair.second) {
                meta_model::denormalised_archetype_properties dap;
                dap.backend_enabled(backend.enabled());
                dap.backend_directory(backend.directory());
                dap.facet_enabled(facet.enabled());
                dap.facet_overwrite(facet.overwrite());
                dap.facet_directory(facet.directory());
                dap.facet_postfix(facet.postfix());

                const auto k(galp.archetype_properties().find(an));
                if (k == galp.archetype_properties().end()) {
                    BOOST_LOG_SEV(lg, error) << archetype_not_found << an;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(archetype_not_found + an));
                }
                const auto& archetype(k->second);
                dap.archetype_enabled(archetype.enabled());
                dap.archetype_overwrite(archetype.overwrite());
                dap.archetype_postfix(archetype.postfix());
                galp.denormalised_archetype_properties()
                    .insert(std::make_pair(an, dap));
            }
        }
    }
}

std::unordered_map<std::string,
                   coding::meta_model::local_archetype_location_properties>
archetype_location_properties_transform::
obtain_local_archetype_location_properties(
    const std::unordered_map<std::string, local_archetype_type_group>& tgs,
    const std::list<archetypes::location>& als,
    const variability::annotation& a) {

    BOOST_LOG_SEV(lg, debug) << "Creating local archetype location properties.";

    std::unordered_map<
        std::string,
        coding::meta_model::local_archetype_location_properties> r;
    const variability::entry_selector s(a);
    for (const auto& al : als) {
        const auto archetype(al.archetype());
        const auto i(tgs.find(archetype));
        if (i == tgs.end()) {
            BOOST_LOG_SEV(lg, error) << type_group_not_found << archetype;
            BOOST_THROW_EXCEPTION(
                transformation_error(type_group_not_found + archetype));
        }
        const auto tg(i->second);

        coding::meta_model::local_archetype_location_properties lalp;
        if (s.has_entry(tg.facet_enabled)) {
            lalp.facet_enabled(
                s.get_boolean_content_or_default(tg.facet_enabled));
        }

        if (s.has_entry(tg.archetype_enabled)) {
            lalp.archetype_enabled(
                s.get_boolean_content_or_default(tg.archetype_enabled));
        }

        if (s.has_entry(tg.facet_overwrite))
            lalp.facet_overwrite(s.get_boolean_content(tg.facet_overwrite));

        if (s.has_entry(tg.archetype_overwrite)) {
            lalp.archetype_overwrite(
                s.get_boolean_content(tg.archetype_overwrite));
        }

        r[archetype] = lalp;
    }

    BOOST_LOG_SEV(lg, debug) << "Created local archetype location properties."
                             << "Result: " << r;
    return r;
}

void archetype_location_properties_transform::
populate_local_archetype_location_properties(
    const variability::type_repository& atrp,
    const archetypes::location_repository& alrp,
    meta_model::model& m) {
    /*
     * Computes all of the possible types for every archetype
     * location. Not all of these will be of use to a given element,
     * because they may not be expressed for that element.
     */
    const auto tgs(make_local_archetype_type_group(atrp, alrp));

    /*
     * Bucket all elements by their meta-name.
     */
    std::unordered_map<std::string,
                       std::list<boost::shared_ptr<coding::meta_model::element>>>
        bucketed_elements;
    for (auto ptr : m.elements())
        bucketed_elements[ptr->meta_name().qualified().dot()].push_back(ptr);

    for (auto& pair : bucketed_elements) {
        /*
         * Locate all of the archetype locations that make sense for
         * the current meta-name. If none do, there nothing for us to
         * do here. This can happen if the meta-model element is not
         * expressed as an artefact at all. This is the case, for
         * example, for object templates (at the time of this
         * wwritting).
         */
        const auto mn_id(pair.first);
        const auto& albmn(alrp.by_meta_name());
        const auto i(albmn.find(mn_id));
        if (i == albmn.end())
            continue;

        const auto& als(i->second.locations());

        /*
         * Now process each of the elements of this meta-type, only
         * taking into account the archetype locations relevant to the
         * meta-type.
         */
        for (auto ptr : pair.second) {
            auto& e(*ptr);
            const auto& a(e.annotation());
            e.archetype_location_properties(
                obtain_local_archetype_location_properties(tgs, als, a));
        }
    }
}

void archetype_location_properties_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "archetype location properties transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& atrp(*ctx.type_repository());
    const auto& alrp(*ctx.archetype_location_repository());
    populate_global_archetype_location_properties(atrp, alrp, m);
    populate_local_archetype_location_properties(atrp, alrp, m);
}

}
