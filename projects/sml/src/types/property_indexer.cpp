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
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/io/relationship_types_io.hpp"
#include "dogen/sml/types/property_indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.property_indexer"));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string concept_not_found("Concept not found in concept container: ");

}

namespace dogen {
namespace sml {

object& property_indexer::find_object(const qname& qn, model& m) {
    auto i(m.objects().find(qn));
    if (i == m.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << qn;
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found +
                boost::lexical_cast<std::string>(qn)));
    }
    return i->second;
}

std::list<qname>& property_indexer::
find_relationships(const relationship_types rt, object& o) {
    auto i(o.relationships().find(rt));
    if (i == o.relationships().end() || i->second.empty()) {
        BOOST_LOG_SEV(lg, error) << relationship_not_found << o.name()
                                 << " relationship: " << rt;

        BOOST_THROW_EXCEPTION(indexing_error(relationship_not_found +
                boost::lexical_cast<std::string>(o.name())));
    }
    return i->second;
}

concept& property_indexer::find_concept(const qname& qn, model& m) {
    auto i(m.concepts().find(qn));
    if (i == m.concepts().end()) {
        const auto& sn(qn.simple_name());
        BOOST_LOG_SEV(lg, error) << concept_not_found << sn;
        BOOST_THROW_EXCEPTION(indexing_error(concept_not_found + sn));
    }
    return i->second;
}

void property_indexer::index_object(object& o, model& m,
    std::unordered_set<sml::qname>& processed_qnames) {
    BOOST_LOG_SEV(lg, debug) << "Indexing object: " << o.name().simple_name();

    if (processed_qnames.find(o.name()) != processed_qnames.end()) {
        BOOST_LOG_SEV(lg, debug) << "Already processed.";
        return;
    }

    std::list<property> concept_properties;
    auto i(o.relationships().find(relationship_types::modeled_concepts));
    if (i != o.relationships().end()) {
        for (const auto& qn : i->second) {
            auto& c(find_concept(qn, m));
            concept_properties.insert(concept_properties.end(),
                c.local_properties().begin(), c.local_properties().end());
        }
    }

    o.local_properties().insert(o.local_properties().begin(),
        concept_properties.begin(), concept_properties.end());

    i = o.relationships().find(relationship_types::parents);
    if (i != o.relationships().end()) {
        for (const auto& qn : i->second) {
            auto& parent(find_object(qn, m));
            index_object(parent, m, processed_qnames);

            if (!parent.all_properties().empty())
                o.inherited_properties().insert(
                    std::make_pair(parent.name(), parent.all_properties()));

            o.all_properties().insert(o.all_properties().end(),
                parent.all_properties().begin(), parent.all_properties().end());
        }
    }

    o.all_properties().insert(o.all_properties().end(),
        o.local_properties().begin(), o.local_properties().end());

    processed_qnames.insert(o.name());
}

void property_indexer::index_objects(model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing objects: " << m.objects().size();

    std::unordered_set<sml::qname> processed_qnames;
    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        index_object(o, m, processed_qnames);
    }
}

void property_indexer::index_concept(concept& c, model& m,
    std::unordered_set<sml::qname>& processed_qnames) {
    BOOST_LOG_SEV(lg, debug) << "Indexing concept: " << c.name().simple_name();

    if (processed_qnames.find(c.name()) != processed_qnames.end()) {
        BOOST_LOG_SEV(lg, debug) << "Already processed.";
        return;
    }

    c.all_properties().insert(c.all_properties().end(),
        c.local_properties().begin(), c.local_properties().end());

    for (const auto& qn : c.refines()) {
        auto& parent(find_concept(qn, m));
        index_concept(parent, m, processed_qnames);

        c.inherited_properties().insert(
            std::make_pair(parent.name(), parent.local_properties()));

        c.all_properties().insert(c.all_properties().end(),
            parent.local_properties().begin(), parent.local_properties().end());
    }
    processed_qnames.insert(c.name());
}

void property_indexer::index_concepts(model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing concepts: " << m.concepts().size();

    std::unordered_set<sml::qname> processed_qnames;
    for (auto& pair : m.concepts()) {
        auto& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        index_concept(c, m, processed_qnames);
    }
}

void property_indexer::index(model& m) {
    index_concepts(m);
    index_objects(m);
}

} }
