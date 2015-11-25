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
#include "dogen/yarn/types/property_indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.property_indexer"));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string concept_not_found("Concept not found in concept container: ");

}

namespace dogen {
namespace yarn {

object& property_indexer::find_object(const name& n, intermediate_model& m) {
    const auto qn(n.qualified());
    auto i(m.objects().find(qn));
    if (i == m.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << qn;
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found + qn));
    }
    return i->second;
}

std::list<name>& property_indexer::
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

concept& property_indexer::find_concept(const name& n, intermediate_model& m) {
    const auto& qn(n.qualified());
    auto i(m.concepts().find(qn));
    if (i == m.concepts().end()) {
        BOOST_LOG_SEV(lg, error) << concept_not_found << qn;
        BOOST_THROW_EXCEPTION(indexing_error(concept_not_found + qn));
    }
    return i->second;
}

void property_indexer::index_object(object& o, intermediate_model& m,
    std::unordered_set<name>& processed_names) {
    BOOST_LOG_SEV(lg, debug) << "Indexing object: " << o.name().qualified();

    if (processed_names.find(o.name()) != processed_names.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed: "
                                 << o.name().qualified();
        return;
    }

    std::list<property> concept_properties;
    auto i(o.relationships().find(relationship_types::modeled_concepts));
    if (i != o.relationships().end()) {
        for (const auto& n : i->second) {
            auto& c(find_concept(n, m));
            concept_properties.insert(concept_properties.end(),
                c.local_properties().begin(), c.local_properties().end());
        }
    }

    o.local_properties().insert(o.local_properties().begin(),
        concept_properties.begin(), concept_properties.end());

    i = o.relationships().find(relationship_types::parents);
    if (i != o.relationships().end()) {
        for (const auto& n : i->second) {
            auto& parent(find_object(n, m));
            index_object(parent, m, processed_names);

            if (!parent.all_properties().empty())
                o.inherited_properties().insert(
                    std::make_pair(parent.name(), parent.all_properties()));

            o.all_properties().insert(o.all_properties().end(),
                parent.all_properties().begin(), parent.all_properties().end());
        }
    }

    o.all_properties().insert(o.all_properties().end(),
        o.local_properties().begin(), o.local_properties().end());

    processed_names.insert(o.name());
}

void property_indexer::index_objects(intermediate_model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing objects: " << m.objects().size();

    std::unordered_set<name> processed_names;
    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        index_object(o, m, processed_names);
    }
}

void property_indexer::index_concept(concept& c, intermediate_model& m,
    std::unordered_set<name>& processed_names) {
    BOOST_LOG_SEV(lg, debug) << "Indexing concept: " << c.name().qualified();

    if (processed_names.find(c.name()) != processed_names.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed:"
                                 << c.name().qualified();
        return;
    }

    c.all_properties().insert(c.all_properties().end(),
        c.local_properties().begin(), c.local_properties().end());

    for (const auto& n : c.refines()) {
        auto& parent(find_concept(n, m));
        index_concept(parent, m, processed_names);

        c.inherited_properties().insert(
            std::make_pair(parent.name(), parent.local_properties()));

        c.all_properties().insert(c.all_properties().end(),
            parent.local_properties().begin(), parent.local_properties().end());
    }
    processed_names.insert(c.name());
}

void property_indexer::index_concepts(intermediate_model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing concepts: " << m.concepts().size();

    std::unordered_set<name> processed_names;
    for (auto& pair : m.concepts()) {
        auto& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        index_concept(c, m, processed_names);
    }
}

void property_indexer::index(intermediate_model& m) {
    index_concepts(m);
    index_objects(m);
}

} }
