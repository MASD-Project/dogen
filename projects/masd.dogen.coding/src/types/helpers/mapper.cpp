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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.coding/io/meta_model/technical_space_io.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.coding/types/helpers/mapping_error.hpp"
#include "masd.dogen.coding/io/helpers/mapping_context_io.hpp"
#include "masd.dogen.coding/types/helpers/mapper.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("coding.helpers.mapper"));

const std::string lam_pointer("lam.pointer");

const std::string missing_mapping("Mapping not found for ID: ");
const std::string unsupported_technical_space(
    "Technical space is not supported: ");
const std::string unexpected_number_of__children("Expected exactly one child.");

}

namespace masd::dogen::coding::helpers {

mapper::mapper(const mapping_set_repository& msrp)
    : mapping_set_repository_(msrp) { }

meta_model::model mapper::
clone(const meta_model::model& m) const {
    auto r(m);

    /*
     * Create deep copies of each element type. This needs to be
     * replaced by a proper clone implementation by the code
     * generator.
     */
    r.modules(clone(m.modules()));
    r.object_templates(clone(m.object_templates()));
    r.builtins(clone(m.builtins()));
    r.enumerations(clone(m.enumerations()));
    r.primitives(clone(m.primitives()));
    r.objects(clone(m.objects()));
    r.exceptions(clone(m.exceptions()));
    r.visitors(clone(m.visitors()));
    return r;
}

const std::unordered_map<std::string, meta_model::name>&
mapper::translations_for_technical_space(const mapping_set& ms,
    const meta_model::technical_space from,
    const meta_model::technical_space to) const {
    if (from == meta_model::technical_space::agnostic) {
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

std::unordered_map<std::string, meta_model::name>
mapper::injections_for_technical_space(const mapping_set& ms,
    const meta_model::technical_space ts,
    const meta_model::model& m) const {

    std::unordered_map<std::string, meta_model::name> r;
    const auto cpp(meta_model::technical_space::cpp);
    if (ts != cpp)
        return r;

    const auto& blai(ms.by_agnostic_id());
    const auto i(blai.find(cpp));
    if (i == blai.end()) {
        const auto s(boost::lexical_cast<std::string>(cpp));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_technical_space + s));
    }

    const auto& map(i->second);
    const auto j(map.find(lam_pointer));
    if (j == map.end()) {
        BOOST_LOG_SEV(lg, error) << missing_mapping << lam_pointer;
        BOOST_THROW_EXCEPTION(mapping_error(missing_mapping + lam_pointer));
    }
    const auto& n(j->second);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        for (const auto& pn : o->parents()) {
            const auto pair(std::make_pair(pn.qualified().dot(), n));
            r.insert(pair);
        }
    }

    return r;
}

mapping_context mapper::create_mapping_context(const mapping_set& ms,
    const meta_model::technical_space from,
    const meta_model::technical_space to, const meta_model::model& m) const {
    mapping_context r;
    r.translations(translations_for_technical_space(ms, from, to));
    r.injections(injections_for_technical_space(ms, to, m));

    const auto i(ms.erasures_by_technical_space().find(to));
    if (i != ms.erasures_by_technical_space().end())
        r.erasures(i->second);

    return r;
}

meta_model::name_tree mapper::walk_name_tree(const mapping_context& mc,
    const meta_model::name_tree& nt, const bool skip_injection) const {
    const auto id(nt.current().qualified().dot());
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
     * Now we handle injections. This is the insertion of an
     * additional type above current. For example, we want to inject a
     * pointer element for all abstract classes in C++. Note that by
     * definitions, injections will always expect exactly one type
     * parameter. We do not attempt injections if we are already under
     * an injection or else we would create an infinite loop.
     */
    meta_model::name_tree r;
    if (!skip_injection) {
        const auto i(mc.injections().find(id));
        if (i != mc.injections().end()) {
            const auto& n(i->second);
            r.current(n);
            r.children().push_back(walk_name_tree(mc, nt, !skip_injection));
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
    std::list<meta_model::attribute>& attrs) const {
    for (auto& attr : attrs)
        attr.parsed_type(walk_name_tree(mc, attr.parsed_type()));
}

bool mapper::is_mappable(const meta_model::technical_space from,
    const meta_model::technical_space to) {
    return from == to || from == meta_model::technical_space::agnostic;
}

meta_model::model mapper::map(const meta_model::technical_space from,
    const meta_model::technical_space to,
    const meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started mapping. Model: "
                             << m.name().qualified().dot();
    BOOST_LOG_SEV(lg, debug) << "Mapping from: " << from << " to: " << to;
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
     * this will be configurable via annotations.
     */
    const auto& ms(mapping_set_repository_.default_mapping_set());
    const auto mc(create_mapping_context(ms, from, to, m));
    BOOST_LOG_SEV(lg, debug) << "Mapping context: " << mc;

    for (auto& pair : r.objects())
        map_attributes(mc, pair.second->local_attributes());

    for (auto& pair : r.object_templates())
        map_attributes(mc, pair.second->local_attributes());

    r.input_technical_space(to);
    r.output_technical_spaces().clear();
    r.output_technical_spaces().push_back(to);

    BOOST_LOG_SEV(lg, debug) << "Output technical spaces: "
                             << r.output_technical_spaces();
    BOOST_LOG_SEV(lg, debug) << "Finished mapping.";

    return r;
}

}
