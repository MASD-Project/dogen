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
#include "dogen/yarn/types/indexing_error.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/association_indexer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.association_indexer"));

const std::string object_not_found("Object not found in object container: ");

}

namespace dogen {
namespace yarn {

void association_indexer::remove_duplicates(std::list<name>& names,
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

void association_indexer::walk_name_tree(const intermediate_model& m,
    object& o, const name_tree& nt, bool& is_opaque) const {
    const auto n(nt.parent());
    if (is_opaque)
        o.opaque_associations().push_back(n);
    else
        o.transparent_associations().push_back(n);

    const auto i(m.primitives().find(n.qualified()));
    if (i != m.primitives().end()) {
        is_opaque = false;
        return;
    }

    const auto j(m.enumerations().find(n.qualified()));
    if (j != m.enumerations().end()) {
        is_opaque = false;
        return;
    }

    const auto k(m.objects().find(n.qualified()));
    if (k == m.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << n.qualified();
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found + n.qualified()));
    }

    is_opaque = k->second.object_type() == object_types::smart_pointer;

    /* if the parent type is an associative container, the first child
     * type will represent the key of the associative container and
     * the second type will be its value. We need to remember the
     * keys.
     */
    bool is_first(true);
    for (const auto c : nt.children()) {
        const auto ac(object_types::associative_container);
        if (is_first && k->second.object_type() == ac)
            o.associative_container_keys().push_back(c.parent());

        walk_name_tree(m, o, c, is_opaque);
        is_first = false;
    }
}

void association_indexer::
index_object(const intermediate_model& m, object& o) const {
    BOOST_LOG_SEV(lg, debug) << "Indexing object: " << o.name().qualified();

    for (const auto& p : o.local_properties()) {
        const auto nt(p.type());
        bool is_opaque(nt.are_children_opaque());
        walk_name_tree(m, o, nt, is_opaque);
    }

    std::unordered_set<name> transparent_associations;
    if (!o.transparent_associations().empty()) {
        remove_duplicates(o.transparent_associations());
        for (const auto n : o.transparent_associations())
            transparent_associations.insert(n);
    }

    if (!o.opaque_associations().empty()) {
        /* Ensure we remove any items which are simultaneously regular
         * and weak associations.
         */
        remove_duplicates(o.opaque_associations(), transparent_associations);
    }

    if (!o.associative_container_keys().empty())
        remove_duplicates(o.associative_container_keys());
}

void association_indexer::index(intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Indexing objects. Total objects: "
                             << m.objects().size();

    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        index_object(m, o);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished indexing objects.";
}

} }
