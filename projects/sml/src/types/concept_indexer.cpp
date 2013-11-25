/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/io/relationship_types_io.hpp"
#include "dogen/sml/types/concept_indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.concept_indexer"));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string concept_not_found("Concept not found in concept container: ");

}

namespace dogen {
namespace sml {

/**
 * @brief Add comparable support for qnames.
 *
 * This is required as part of the current (very sub-optimal)
 * implementation of concept processing.
 */
inline bool operator<(const qname& lhs, const qname& rhs) {
    return
        lhs.model_name() < rhs.model_name() ||
        (lhs.model_name() == rhs.model_name() &&
            (lhs.external_module_path() < rhs.external_module_path() ||
                (lhs.external_module_path() == rhs.external_module_path() &&
                    (lhs.simple_name() < rhs.simple_name()))));
}

abstract_object& concept_indexer::find_object(const qname& qn, model& m) {
    auto i(m.objects().find(qn));
    if (i == m.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << qn;
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found +
                boost::lexical_cast<std::string>(qn)));
    }
    return *(i->second);
}

std::list<qname>& concept_indexer::
find_relationships(const relationship_types rt, abstract_object& o) {
    auto i(o.relationships().find(rt));
    if (i == o.relationships().end() || i->second.empty()) {
        BOOST_LOG_SEV(lg, error) << relationship_not_found << o.name()
                                 << " relationship: " << rt;

        BOOST_THROW_EXCEPTION(indexing_error(relationship_not_found +
                boost::lexical_cast<std::string>(o.name())));
    }
    return i->second;
}

concept& concept_indexer::find_concept(const qname& qn, model& m) {
    auto i(m.concepts().find(qn));
    if (i == m.concepts().end()) {
        const auto& sn(qn.simple_name());
        BOOST_LOG_SEV(lg, error) << concept_not_found << sn;
        BOOST_THROW_EXCEPTION(indexing_error(concept_not_found + sn));
    }
    return i->second;
}

void concept_indexer::remove_duplicates(std::list<qname>& names) const {
    std::unordered_set<sml::qname> processed;

    BOOST_LOG_SEV(lg, debug) << "Removing duplicates from list. Original size: "
                             << names.size();

    for (auto i(names.begin()); i != names.end(); ++i) {
        if (processed.find(*i) != processed.end()) {
            names.erase(i); // iterator is ok after erase
            continue;
        }
        processed.insert(*i);
    }

    BOOST_LOG_SEV(lg, debug) << "Removed duplicates from list. final size: "
                             << names.size();

}

void concept_indexer::index_object(abstract_object& o, model& m,
    std::unordered_set<sml::qname>& processed_qnames) {

    if (processed_qnames.find(o.name()) != processed_qnames.end())
        return;

    const auto i(o.relationships().find(relationship_types::modeled_concepts));
    if (i == o.relationships().end() || !i->second.empty() || !o.is_child()) {
        processed_qnames.insert(o.name());
        return;
    }

    std::set<qname> our_concepts;
    for (const auto& qn : i->second) {
        const auto& c(find_concept(qn, m));
        our_concepts.insert(c.name());
        our_concepts.insert(c.refines().begin(), c.refines().end());
    }

    std::set<qname> their_concepts;
    for (const auto& qn : find_relationships(relationship_types::parents, o)) {
        auto& parent(find_object(qn, m));
        index_object(parent, m, processed_qnames);

        auto& pr(parent.relationships());
        const auto j(pr.find(relationship_types::modeled_concepts));
        if (j == pr.end() || j->second.empty())
            continue;

        their_concepts.insert(j->second.begin(), j->second.end());
    }

    /* we want to only model concepts which have not yet been modeled
     * by any of our parents.
     */
    std::set<qname> result;
    std::set_difference(our_concepts.begin(), our_concepts.end(),
        their_concepts.begin(), their_concepts.end(),
        std::inserter(result, result.end()));

    /* reinsert all of the modeled concepts which are part of the set
     * difference. we do this instead of just using the set difference
     * directly to preserve order.
     */
    auto tmp(i->second);
    i->second.clear();
    for (const auto& qn : tmp) {
        if (result.find(qn) != result.end())
            i->second.push_back(qn);
    }
}

void concept_indexer::index_objects(model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing objects: "
                             << m.objects().size();

    std::unordered_set<sml::qname> processed_qnames;
    for (auto& pair : m.objects()) {
        auto& o(*pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        index_object(o, m, processed_qnames);
    }
}

void concept_indexer::index_concept(concept& c, model& m,
    std::unordered_set<sml::qname>& processed_qnames) {
    if (processed_qnames.find(c.name()) != processed_qnames.end())
        return;

    if (c.refines().empty()) {
        processed_qnames.insert(c.name());
        return;
    }

    std::list<qname> expanded_refines;
    for (auto& qn : c.refines()) {
        auto& parent(find_concept(qn, m));
        index_concept(parent, m, processed_qnames);

        expanded_refines.push_back(qn);

        expanded_refines.insert(expanded_refines.end(),
            parent.refines().begin(), parent.refines().end());
    }

    remove_duplicates(expanded_refines);
    c.refines(expanded_refines);
    processed_qnames.insert(c.name());
}

void concept_indexer::index_concepts(model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing concepts: "
                             << m.concepts().size();

    std::unordered_set<sml::qname> processed_qnames;
    for (auto& pair : m.concepts()) {
        auto& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        index_concept(c, m, processed_qnames);
    }
}

void concept_indexer::index(model& m) {
    index_concepts(m);
    index_objects(m);
}

} }
