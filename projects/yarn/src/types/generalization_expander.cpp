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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/generalization_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.generalization_expander"));

const std::string child_with_no_parents(
    "Object is child but has no parents. Child: ");
const std::string parent_not_found("Could not find parent: ");
const std::string object_not_found("Could not find object: ");
const std::string child_with_no_root_parent(
    "Object is child but has no root parent. Child: ");

}

namespace dogen {
namespace yarn {

inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.id() < rhs.id();
}

bool generalization_expander::is_leaf(const object& o) const {
    // FIXME: massive hack. must not add leafs for services.
    const auto uds(object_types::user_defined_service);
    const bool is_service(o.object_type() == uds);
    if (o.is_parent() || !o.is_child() || is_service) {
        BOOST_LOG_SEV(lg, debug)
            << "Type is not a generalisation leaf. "
            << " is parent: " << o.is_parent()
            << " is child: " << o.is_child()
            << " is service: " << is_service;
        return false;
    }
    return true;
}

std::list<name> generalization_expander::
recurse_generalization(const intermediate_model& im, const name& leaf,
    const object& o, generalization_details& d) const {

    if (!o.is_child())
        return std::list<name> { o.name() };

    if (o.parents().empty()) {
        const auto id(o.name().id());
        BOOST_LOG_SEV(lg, error) << child_with_no_parents << id;
        BOOST_THROW_EXCEPTION(expansion_error(child_with_no_parents + id));
    }

    std::list<name> root_parents;
    for (const auto& parent : o.parents()) {
        auto j(im.objects().find(parent.id()));
        if (j == im.objects().end()) {
            const auto id(parent.id());
            BOOST_LOG_SEV(lg, error) << parent_not_found << id;
            BOOST_THROW_EXCEPTION(expansion_error(parent_not_found + id));
        }

        const auto op(recurse_generalization(im, leaf, j->second, d));
        if (op.empty()) {
            const auto id(parent.id());
            BOOST_LOG_SEV(lg, error) << child_with_no_root_parent << id;
            BOOST_THROW_EXCEPTION(
                expansion_error(child_with_no_root_parent + id));
        }

        for (const auto n : op)
            root_parents.push_back(n);

        d.root_parents[parent.id()] = op;
        BOOST_LOG_SEV(lg, debug) << "Type: " << parent.id()
                                 << " has original parents: " << op;

        d.leaves[parent.id()].push_back(leaf);
        BOOST_LOG_SEV(lg, debug) << "Type is a leaf of: " << parent.id();
    }
    d.root_parents[o.name().id()] = root_parents;
    return root_parents;
}

generalization_expander::generalization_details generalization_expander::
obtain_details(const intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining leaves.";
    generalization_details r;
    for (auto& pair : m.objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

        auto& o(pair.second);
        if (!is_leaf(o))
            continue;

        recurse_generalization(m, o.name(), o, r);
    }

    BOOST_LOG_SEV(lg, debug) << "Leaves: " << r.leaves;
    BOOST_LOG_SEV(lg, debug) << "Original parents: " << r.root_parents;
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining details.";
    return r;
}

void generalization_expander::
populate(const generalization_details& d, intermediate_model& m) const {
    for (const auto& pair : d.leaves) {
        const auto& id(pair.first);
        auto i(m.objects().find(id));
        if (i == m.objects().end()) {
            BOOST_LOG_SEV(lg, error) << object_not_found << id;
            BOOST_THROW_EXCEPTION(expansion_error(object_not_found + id));
        }

        auto& o(i->second);
        o.leaves(pair.second);

        /*
         * Sort the leaves to ensure stability.
         */
        o.leaves().sort();

        for (const auto& leaf : pair.second) {
            /*
             * If the leaf name belongs to the target model, add it to
             * the model's list of leaves. Ignore non-target leaves.
             */
            const auto& ll(leaf.location());
            const auto& ml(m.name().location());
            if (ll.model_modules() == ml.model_modules())
                m.leaves().insert(leaf);
        }
    }

    for (const auto& pair : d.root_parents) {
        const auto& id(pair.first);
        auto i(m.objects().find(id));
        if (i == m.objects().end()) {
            BOOST_LOG_SEV(lg, error) << object_not_found << id;
            BOOST_THROW_EXCEPTION(expansion_error(object_not_found + id));
        }

        auto& o(i->second);

        /*
         * Mark all types that are in an inheritance relationship,
         * either as a parent or as a child.
         */
        o.in_inheritance_relationship(o.is_parent() || o.is_child());

        if (!o.is_child()) {
            /*
             * All types that are in an inheritance relationship have
             * a root parent in the details container, including the
             * root parent itself. If we have a parent but we are not
             * a child, we must be the root parent. Do not propagate
             * the recursive relationship between the root parent and
             * itself.
             */
            BOOST_LOG_SEV(lg, debug) << "Type has parents but is not a child: "
                                     << id;
            continue;
        }

        o.root_parents(pair.second);
        for (const auto& opn : pair.second) {
            const auto j(m.objects().find(opn.id()));
            if (j == m.objects().end()) {
                const auto id(opn.id());
                BOOST_LOG_SEV(lg, error) << object_not_found << id;
                BOOST_THROW_EXCEPTION(expansion_error(object_not_found + id));
            }

            // FIXME: we are assuming a single parent here.
            o.is_root_parent_visitable(j->second.is_visitable());
        }
    }
}

void generalization_expander::expand(intermediate_model& im) const {
    const auto d(obtain_details(im));
    populate(d, im);
}

} }
