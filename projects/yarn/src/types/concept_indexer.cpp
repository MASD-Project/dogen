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
#include <unordered_map>
#include <unordered_set>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/indexing_error.hpp"
#include "dogen/yarn/io/relationship_types_io.hpp"
#include "dogen/yarn/types/concept_indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.concept_indexer"));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string concept_not_found("Concept not found in concept container: ");

}

namespace dogen {
namespace yarn {

/**
 * @brief Add comparable support for names.
 *
 * This is required as part of the current (very sub-optimal)
 * implementation of concept processing.
 */
inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.qualified() < rhs.qualified();
}

object& concept_indexer::find_object(const name& n, intermediate_model& m) {
    auto i(m.objects().find(n.qualified()));
    if (i == m.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << n.qualified();
        BOOST_THROW_EXCEPTION(
            indexing_error(object_not_found +  n.qualified()));
    }
    return i->second;
}

std::list<name>& concept_indexer::
find_relationships(const relationship_types rt, object& o) {
    auto i(o.relationships().find(rt));
    if (i == o.relationships().end() || i->second.empty()) {
        const auto qn(o.name().qualified());
        BOOST_LOG_SEV(lg, error) << relationship_not_found << qn
                                 << " relationship: " << rt;
        BOOST_THROW_EXCEPTION(indexing_error(relationship_not_found + qn));
    }
    return i->second;
}

concept& concept_indexer::find_concept(const name& n, intermediate_model& m) {
    auto i(m.concepts().find(n.qualified()));
    if (i == m.concepts().end()) {
        BOOST_LOG_SEV(lg, error) << concept_not_found << n.qualified();
        BOOST_THROW_EXCEPTION(
            indexing_error(concept_not_found + n.qualified()));
    }
    return i->second;
}

void concept_indexer::remove_duplicates(std::list<name>& names) const {
    std::unordered_set<name> processed;

    BOOST_LOG_SEV(lg, debug) << "Removing duplicates from list. Original size: "
                             << names.size();

    // FIXME: use std algorithm
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

void concept_indexer::index_object(object& o, intermediate_model& m,
    std::unordered_set<name>& processed_names) {
    BOOST_LOG_SEV(lg, debug) << "Indexing object: " << o.name().qualified();

    if (processed_names.find(o.name()) != processed_names.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed.";
        return;
    }

    const auto i(o.relationships().find(relationship_types::modeled_concepts));
    if (i == o.relationships().end() || i->second.empty()) {
        processed_names.insert(o.name());
        BOOST_LOG_SEV(lg, debug) << "Object models no concepts.";
        return;
    }

    std::list<name> expanded_refines;
    for (auto& n : i->second) {
        auto& c(find_concept(n, m));
        expanded_refines.push_back(n);
        expanded_refines.insert(expanded_refines.end(),
            c.refines().begin(), c.refines().end());
    }
    remove_duplicates(expanded_refines);

    if (!o.is_child()) {
        i->second = expanded_refines;
        BOOST_LOG_SEV(lg, debug) << "Object has no parents, using reduced set.";
        return;
    }

    std::set<name> our_concepts;
    our_concepts.insert(expanded_refines.begin(), expanded_refines.end());

    std::set<name> their_concepts;
    for (const auto& n : find_relationships(relationship_types::parents, o)) {
        auto& parent(find_object(n, m));
        index_object(parent, m, processed_names);

        auto& pr(parent.relationships());
        const auto j(pr.find(relationship_types::modeled_concepts));
        if (j == pr.end() || j->second.empty())
            continue;

        their_concepts.insert(j->second.begin(), j->second.end());
    }

    /* we want to only model concepts which have not yet been modeled
     * by any of our parents.
     */
    std::set<name> result;
    std::set_difference(our_concepts.begin(), our_concepts.end(),
        their_concepts.begin(), their_concepts.end(),
        std::inserter(result, result.end()));

    /* reinsert all of the modeled concepts which are part of the set
     * difference. we do this instead of just using the set difference
     * directly to preserve order.
     */
    BOOST_LOG_SEV(lg, debug) << "Object has parents, computing set difference.";
    i->second.clear();
    for (const auto& n : expanded_refines) {
        if (result.find(n) != result.end())
            i->second.push_back(n);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished indexing object.";
}

void concept_indexer::index_objects(intermediate_model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing objects: " << m.objects().size();

    std::unordered_set<name> processed_names;
    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        index_object(o, m, processed_names);
    }
}

void concept_indexer::index_concept(concept& c, intermediate_model& m,
    std::unordered_set<name>& processed_names) {
    BOOST_LOG_SEV(lg, debug) << "Indexing concept: " << c.name().qualified();

    if (processed_names.find(c.name()) != processed_names.end()) {
        BOOST_LOG_SEV(lg, debug) << "Concept already processed.";
        return;
    }

    if (c.refines().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Concept refines no concepts.";
        processed_names.insert(c.name());
        return;
    }

    std::list<name> expanded_refines;
    for (auto& n : c.refines()) {
        auto& parent(find_concept(n, m));
        index_concept(parent, m, processed_names);

        expanded_refines.push_back(n);

        expanded_refines.insert(expanded_refines.end(),
            parent.refines().begin(), parent.refines().end());
    }

    BOOST_LOG_SEV(lg, debug) << "Computing reduced set for concept.";
    remove_duplicates(expanded_refines);
    c.refines(expanded_refines);
    processed_names.insert(c.name());
}

void concept_indexer::index_concepts(intermediate_model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing concepts: " << m.concepts().size();

    std::unordered_set<name> processed_names;
    for (auto& pair : m.concepts()) {
        auto& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        index_concept(c, m, processed_names);
    }
}

void concept_indexer::index(intermediate_model& m) {
    index_concepts(m);
    index_objects(m);
}

} }
