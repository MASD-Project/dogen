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
#include "dogen/tack/types/object.hpp"
#include "dogen/tack/types/indexing_error.hpp"
#include "dogen/tack/io/name_io.hpp"
#include "dogen/tack/io/relationship_types_io.hpp"
#include "dogen/tack/types/generalization_indexer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tack.generalization_indexer"));

const std::string child_with_no_parents(
    "Object is child but has no parents. Child: ");
const std::string parent_not_found("Could not find parent: ");
const std::string object_not_found("Could not find object: ");
const std::string child_with_no_original_parent(
    "Object is child but has no original parent. Child: ");

}

namespace dogen {
namespace tack {

inline bool operator<(const location& lhs, const location& rhs) {
    return
        (lhs.original_model_name() < rhs.original_model_name() ||
            (lhs.original_model_name() == rhs.original_model_name() &&
                (lhs.external_module_path() < rhs.external_module_path())));
}

inline bool operator<(const name& lhs, const name& rhs) {
    return
        (lhs.location() < rhs.location() ||
            (lhs.location() == rhs.location() &&
                (lhs.simple() < rhs.simple())));
}

bool generalization_indexer::is_leaf(const object& o) const {
    // FIXME: massive hack. must not add leafs for services.
    const auto uds(object_types::user_defined_service);
    const bool is_service(o.object_type() == uds);
    if (o.is_parent() || !o.is_child() || is_service) {
        BOOST_LOG_SEV(lg, debug)
            << "Type is not in a generalization relationship."
            << " is parent: " << o.is_parent()
            << " is child: " << o.is_child()
            << " is service: " << is_service;
        return false;
    }
    return true;
}

std::list<name> generalization_indexer::
recurse_generalization(const model& m, const name& leaf,
    const object& o, generalization_details& d) const {

    if (!o.is_child())
        return std::list<name> { o.name() };

    const auto i(o.relationships().find(relationship_types::parents));
    if (i == o.relationships().end() || i->second.empty()) {
        const auto qn(o.name().qualified());
        BOOST_LOG_SEV(lg, error) << child_with_no_parents << qn;
        BOOST_THROW_EXCEPTION(indexing_error(child_with_no_parents + qn));
    }

    std::list<name> original_parents;
    for (const auto& parent : i->second) {
        auto j(m.objects().find(parent));
        if (j == m.objects().end()) {
            const auto qn(parent.qualified());
            BOOST_LOG_SEV(lg, error) << parent_not_found << qn;
            BOOST_THROW_EXCEPTION(indexing_error(parent_not_found + qn));
        }

        const auto op(recurse_generalization(m, leaf, j->second, d));
        if (op.empty()) {
            const auto qn(parent.qualified());
            BOOST_LOG_SEV(lg, error) << child_with_no_original_parent << qn;
            BOOST_THROW_EXCEPTION(
                indexing_error(child_with_no_original_parent + qn));
        }

        for (const auto qn : op)
            original_parents.push_back(qn);

        d.original_parents[parent] = op;
        BOOST_LOG_SEV(lg, debug) << "Type: "
                                 << parent.qualified()
                                 << " has original parents: " << op;

        d.leaves[parent].push_back(leaf);
        BOOST_LOG_SEV(lg, debug) << "Type is a leaf of: "
                                 << parent.qualified();
    }
    d.original_parents[o.name()] = original_parents;
    return original_parents;
}

generalization_indexer::generalization_details generalization_indexer::
obtain_details(const model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining leaves.";
    generalization_details r;
    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        BOOST_LOG_SEV(lg, debug) << "Processing type: "
                                 << o.name().qualified();

        if (!is_leaf(o))
            continue;

        recurse_generalization(m, o.name(), o, r);
    }

    BOOST_LOG_SEV(lg, debug) << "Leaves: " << r.leaves;
    BOOST_LOG_SEV(lg, debug) << "Original parents: " << r.original_parents;
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining details.";
    return r;
}

void generalization_indexer::
populate(const generalization_details& d, model& m) const {
    for (const auto& pair : d.leaves) {
        const auto& n(pair.first);
        auto i(m.objects().find(n));
        if (i == m.objects().end()) {
            const auto qn(n.qualified());
            BOOST_LOG_SEV(lg, error) << object_not_found << qn;
            BOOST_THROW_EXCEPTION(indexing_error(object_not_found + qn));
        }

        const auto rt(relationship_types::leaves);
        i->second.relationships()[rt] = pair.second;
        i->second.relationships()[rt].sort();

        const auto omn(m.name().location().original_model_name());
        for (const auto& l : pair.second) {
            if (l.location().original_model_name() == omn)
                m.leaves().insert(l);
        }
    }

    for (const auto& pair : d.original_parents) {
        const auto& n(pair.first);
        auto i(m.objects().find(n));
        if (i == m.objects().end()) {
            const auto qn(n.qualified());
            BOOST_LOG_SEV(lg, error) << object_not_found << qn;
            BOOST_THROW_EXCEPTION(indexing_error(object_not_found + qn));
        }

        auto& o(i->second);
        if (!o.is_child()) {
            // a bit of a hack, top-level types have themselves as the
            // original parent of the container just to make our life easier
            BOOST_LOG_SEV(lg, debug) << "Type has parents but is not a child: "
                                     << n.qualified();
            continue;
        }


        const auto rt(relationship_types::original_parents);
        o.relationships()[rt] = pair.second;
        for (const auto& opn : pair.second) {
            const auto j(m.objects().find(opn));
            if (j == m.objects().end()) {
                const auto qn(opn.qualified());
                BOOST_LOG_SEV(lg, error) << object_not_found << qn;
                BOOST_THROW_EXCEPTION(indexing_error(object_not_found + qn));
            }
            o.is_original_parent_visitable(j->second.is_visitable());
        }
    }
}

void generalization_indexer::index(model& m) const {
    const auto d(obtain_details(m));
    populate(d, m);
}

} }
