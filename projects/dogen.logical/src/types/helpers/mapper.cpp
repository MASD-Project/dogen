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
#include <boost/lexical_cast.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.identification/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/helpers/mapping_error.hpp"
#include "dogen.logical/io/helpers/mapping_context_io.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/types/helpers/visual_studio_project_type_mapper.hpp"
#include "dogen.logical/types/helpers/mapper.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("logical.helpers.mapper"));

const dogen::identification::entities::logical_id lam_pointer("lam.pointer");

const std::string missing_mapping("Mapping not found for ID: ");
const std::string unsupported_technical_space(
    "Technical space is not supported: ");
const std::string unexpected_number_of__children("Expected exactly one child.");
const std::string root_module_not_found("Root module not found: ");

}

namespace dogen::logical::helpers {

using identification::entities::logical_name_tree;

mapper::mapper(const mapping_set_repository& msrp)
    : mapping_set_repository_(msrp) { }

entities::model mapper::clone(const entities::model& m) const {
    auto r(m);

    /*
     * Create deep copies of the elements affected by mapping. This
     * needs to be replaced by a proper clone implementation by the
     * code generator.
     *
     * Note that we worry mainly about structural elements because the
     * rest of the meta-types are largely unaffected by mappings, with
     * the exception of visual studio projects.
     */
    r.structural_elements().object_templates(
        clone(m.structural_elements().object_templates()));
    r.structural_elements().builtins(
        clone(m.structural_elements().builtins()));
    r.structural_elements().enumerations(
        clone(m.structural_elements().enumerations()));
    r.structural_elements().primitives(
        clone(m.structural_elements().primitives()));
    r.structural_elements().objects(clone(
            m.structural_elements().objects()));
    r.structural_elements().exceptions(
        clone(m.structural_elements().exceptions()));
    r.structural_elements().visitors(clone(
            m.structural_elements().visitors()));
    r.visual_studio_elements().projects(clone(
            m.visual_studio_elements().projects()));

    /*
     * Copy across the modules, and sync up the root module.
     */
    r.structural_elements().modules(clone(m.structural_elements().modules()));
    const auto rm_id(m.name().id());
    const auto i(r.structural_elements().modules().find(rm_id));
    if (i == r.structural_elements().modules().end()) {
        BOOST_LOG_SEV(lg, error) << root_module_not_found << rm_id;
        BOOST_THROW_EXCEPTION(
            mapping_error(root_module_not_found + rm_id.value()));
    }
    r.root_module(i->second);

    return r;
}

const std::unordered_map<identification::entities::logical_id,
                         identification::entities::logical_name>&
mapper::translations_for_technical_space(const mapping_set& ms,
    const identification::entities::technical_space from,
    const identification::entities::technical_space to) const {
    if (from == identification::entities::technical_space::agnostic) {
        const auto& blai(ms.by_agnostic_id());
        const auto i(blai.find(to));
        if (i != blai.end())
            return i->second;

        const auto s(boost::lexical_cast<std::string>(to));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_technical_space + s));
    }

    const auto s(boost::lexical_cast<std::string>(from));
    BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
    BOOST_THROW_EXCEPTION(mapping_error(unsupported_technical_space + s));
}

std::unordered_map<identification::entities::logical_id,
                   identification::entities::logical_name>
mapper::codecs_for_technical_space(const mapping_set& ms,
    const identification::entities::technical_space ts,
    const entities::model& m) const {

    std::unordered_map<identification::entities::logical_id,
                       identification::entities::logical_name> r;
    const auto cpp(identification::entities::technical_space::cpp);
    if (ts != cpp)
        return r;

    const auto& blai(ms.by_agnostic_id());
    const auto i(blai.find(cpp));
    if (i == blai.end()) {
        const auto s(boost::lexical_cast<std::string>(cpp));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_technical_space + s));
    }

    /*
     * If there are no mappings for LAM pointers, then there is
     * nothing to do. This is the case for languages such as C#.
     */
    const auto& map(i->second);
    const auto j(map.find(lam_pointer));
    if (j == map.end()) {
        BOOST_LOG_SEV(lg, debug) << "No mapping for LAM pointer.";
        return r;
    }

    const auto& n(j->second);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(pair.second);
        for (const auto& pn : o->parents()) {
            const auto pair(std::make_pair(pn.qualified().dot(), n));
            r.insert(pair);
        }
    }

    return r;
}

mapping_context mapper::create_mapping_context(const mapping_set& ms,
    const identification::entities::technical_space from,
    const identification::entities::technical_space to,
    const entities::model& m) const {
    mapping_context r;
    r.translations(translations_for_technical_space(ms, from, to));
    r.codecs(codecs_for_technical_space(ms, to, m));

    const auto i(ms.erasures_by_technical_space().find(to));
    if (i != ms.erasures_by_technical_space().end())
        r.erasures(i->second);

    return r;
}

logical_name_tree
mapper::walk_name_tree(const mapping_context& mc,
    const logical_name_tree& nt,
    const bool skip_codec) const {
    const auto id(nt.current().id());
    if (mc.erasures().find(id) != mc.erasures().end()) {
        /*
         * We need to erase this type from the name tree. We do this
         * by skipping it. Note that, for erasures, only one child is
         * permitted. An erasure is required, for example, for
         * technical space agnostic pointers in technical_space where
         * all objects are pointers anyway (such as C#).
         */
        if (nt.children().size() != 1) {
            BOOST_LOG_SEV(lg, error) << unexpected_number_of__children
                                     << " Children: " << nt.children().size();
            BOOST_THROW_EXCEPTION(
                mapping_error(unexpected_number_of__children));
        }
        const auto& c(nt.children().front());
        return walk_name_tree(mc, c);
    }

    /*
     * Now we handle codecs. This is the insertion of an
     * additional type above current. For example, we want to inject a
     * pointer element for all abstract classes in C++. Note that by
     * definitions, codecs will always expect exactly one type
     * parameter. We do not attempt codecs if we are already under
     * an codec or else we would create an infinite loop.
     */
    logical_name_tree r;
    if (!skip_codec) {
        const auto i(mc.codecs().find(id));
        if (i != mc.codecs().end()) {
            const auto& n(i->second);
            r.current(n);
            r.children().push_back(walk_name_tree(mc, nt, !skip_codec));
            return r;
        }
    }

    /*
     * Finally we handle translations. We locate a maping for the
     * current ID; if one is found, we replace the name with the
     * mapped name. Otherwise we copy across the original name.
     */
    const auto i(mc.translations().find(id));
    if (i != mc.translations().end()) {
        r.current(i->second);
        BOOST_LOG_SEV(lg, debug) << "Mapping from: " << id
                                 << " to: " << i->second.qualified().dot();
    } else {
        BOOST_LOG_SEV(lg, debug) << "No translation for: " << id;
        r.current(nt.current());
    }

    /*
     * We now repeat the whole process for all our children.
     */
    for (const auto& c : nt.children())
        r.children().push_back(walk_name_tree(mc, c));

    return r;
}

void mapper::map_attributes(const mapping_context& mc,
    std::list<entities::attribute>& attrs) const {
    for (auto& attr : attrs)
        attr.parsed_type(walk_name_tree(mc, attr.parsed_type()));
}

bool mapper::is_mappable(const identification::entities::technical_space from,
    const identification::entities::technical_space to) {
    using identification::entities::technical_space;
    return from == to || from == technical_space::agnostic;
}

entities::model mapper::
map(const identification::entities::technical_space from,
    const identification::entities::technical_space to,
    const entities::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started mapping. Model: "
                             << m.name().qualified().dot();
    BOOST_LOG_SEV(lg, debug) << "Mapping from: "
                             << boost::lexical_cast<std::string>(from)
                             << " to: " << boost::lexical_cast<std::string>(to);
    if (from == to) {
        BOOST_LOG_SEV(lg, debug) << "No mapping required";
        return m;
    }

    /*
     * We make a clone of the original intermediate model, so that we
     * have our own set of elements. Otherwise, all mapped models
     * would be pointing to the same elements, causing confusion and
     * chaos.
     */
    auto r(clone(m));

    /*
     * For now we always use the default mapping set. In the future
     * this will be configurable via variability.
     */
    const auto& ms(mapping_set_repository_.default_mapping_set());
    if (!ms.by_agnostic_id().empty()) {
        const auto mc(create_mapping_context(ms, from, to, m));
        BOOST_LOG_SEV(lg, debug) << "Mapping context: " << mc;

        for (auto& pair : r.structural_elements().objects())
            map_attributes(mc, pair.second->local_attributes());

        for (auto& pair : r.structural_elements().object_templates())
            map_attributes(mc, pair.second->local_attributes());
    }

    /*
     * Visual studio project types are relative to the technical space
     * we are in.
     */
    helpers::visual_studio_project_type_mapper tm;
    for (auto& pair : r.visual_studio_elements().projects()) {
        auto& proj(*pair.second);
        proj.type_guid(tm.from_technical_space(to));
    }

    /*
     * Finally, update all the technical space-related properties. We
     * set both the input and output to the mapped technical space for
     * consistency reasons, as it doesn't actually do anything (at
     * least at present).
     */
    r.input_technical_space(to);
    r.output_technical_spaces().clear();
    r.output_technical_spaces().push_back(to);

    BOOST_LOG_SEV(lg, debug) << "Output technical spaces: "
                             << r.output_technical_spaces();
    BOOST_LOG_SEV(lg, debug) << "Finished mapping.";

    return r;
}

}
