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
#include <set>
#include <list>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/association_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.association_expander"));

const std::string object_not_found("Object not found in object container: ");

}

namespace dogen {
namespace yarn {

void association_expander::remove_duplicates(std::list<name>& names,
    std::unordered_set<name> processed) const {
    BOOST_LOG_SEV(lg, debug) << "Removing duplicates from list. Original size: "
                             << names.size() << ". Processed starts with size: "
                             << processed.size();

    auto i(names.begin());
    while (i != names.end()) {
        const auto n(*i);
        if (processed.find(n) != processed.end()) {
            const auto j(i++);
            names.erase(j);
            continue;
        }
        ++i;
        processed.insert(n);
    }

    BOOST_LOG_SEV(lg, debug) << "Removed duplicates from list. final size: "
                             << names.size();
}

void association_expander::walk_name_tree(
    const intermediate_model& im, object& o, const name_tree& nt,
    const bool inherit_opaqueness_from_parent) const {

    const auto n(nt.current());
    if (inherit_opaqueness_from_parent)
        o.opaque_associations().push_back(n);
    else
        o.transparent_associations().push_back(n);

    const auto i(im.primitives().find(n.id()));
    if (i != im.primitives().end())
        return;

    const auto j(im.enumerations().find(n.id()));
    if (j != im.enumerations().end())
        return;

    const auto k(im.objects().find(n.id()));
    if (k == im.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << n.id();
        BOOST_THROW_EXCEPTION(expansion_error(object_not_found + n.id()));
    }

    /*
     * if the parent type is an associative container, the first child
     * type will represent the key of the associative container and
     * the second type will be its value. We need to remember the
     * keys.
     */
    bool is_first(true);
    for (const auto c : nt.children()) {
        const auto ac(object_types::associative_container);
        if (is_first && k->second.object_type() == ac)
            o.associative_container_keys().push_back(c.current());

        walk_name_tree(im, o, c, nt.are_children_opaque());
        is_first = false;
    }
}

void association_expander::
expand_object(const intermediate_model& im, object& o) const {
    BOOST_LOG_SEV(lg, debug) << "Expand object: " << o.name().id();

    for (const auto& p : o.local_attributes()) {
        const auto& nt(p.parsed_type());
        walk_name_tree(im, o, nt, false/*inherit_opaqueness_from_parent*/);
    }

    std::unordered_set<name> transparent_associations;
    if (!o.transparent_associations().empty()) {
        remove_duplicates(o.transparent_associations());
        for (const auto n : o.transparent_associations())
            transparent_associations.insert(n);
    }

    if (!o.opaque_associations().empty()) {
        /*
         * Ensure we remove any items which are simultaneously regular
         * and weak associations.
         */
        remove_duplicates(o.opaque_associations(), transparent_associations);
    }

    if (!o.associative_container_keys().empty())
        remove_duplicates(o.associative_container_keys());
}

void association_expander::expand(intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Expanding objects. Total objects: "
                             << im.objects().size();

    for (auto& pair : im.objects()) {
        auto& o(pair.second);
        expand_object(im, o);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished expanding objects.";
}

} }
