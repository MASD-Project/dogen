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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.coding/io/meta_model/name_io.hpp"
#include "dogen.coding/io/meta_model/model_io.hpp"
#include "dogen.coding/types/transforms/transformation_error.hpp"
#include "dogen.coding/types/transforms/associations_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.associations_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::coding::transforms {

void associations_transform::remove_duplicates(
    std::list<meta_model::name>& names,
    std::unordered_set<meta_model::name> processed) {
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

void associations_transform::
walk_name_tree(const meta_model::model& m, meta_model::structural::object& o,
    const meta_model::name_tree& nt,
    const bool inherit_opaqueness_from_parent) {

    const auto n(nt.current());
    if (inherit_opaqueness_from_parent)
        o.opaque_associations().push_back(n);
    else
        o.transparent_associations().push_back(n);

    /*
     * If the parent type is an associative container, the first child
     * type will represent the key of the associative container and
     * the second type will be its value. We need to remember the
     * keys.
     *
     * Note that we must still continue to walk the tree even if the
     * type is not an associative container, since there are other
     * properties to set (see above).
     */
    bool is_first(true);
    const auto i(m.structural_elements().objects().find(n.qualified().dot()));
    const auto is_associative_container(i != m.structural_elements().objects().end() &&
        i->second->is_associative_container());

    for (const auto c : nt.children()) {
        if (is_first && is_associative_container)
            o.associative_container_keys().push_back(c.current());

        walk_name_tree(m, o, c, nt.are_children_opaque());
        is_first = false;
    }
}

void associations_transform::
process_object(const meta_model::model& m, meta_model::structural::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Expand object: " << o.name().qualified().dot();

    for (const auto& p : o.local_attributes()) {
        const auto& nt(p.parsed_type());
        walk_name_tree(m, o, nt, false/*inherit_opaqueness_from_parent*/);
    }

    std::unordered_set<meta_model::name> transparent_associations;
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

void associations_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "associations transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    BOOST_LOG_SEV(lg, debug) << "Total objects: " << m.structural_elements().objects().size();

    for (auto& pair : m.structural_elements().objects())
        process_object(m, *pair.second);

    stp.end_transform(m);
}

}