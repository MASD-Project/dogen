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
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/io/relationship_types_io.hpp"
#include "dogen/sml/types/indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.indexer"));

const std::string orphan_object("Object's parent could not be located: ");
const std::string orphan_concept("Refined concept could not be located: ");
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

abstract_object& indexer::find_object(const qname& qn, model& m) {
    auto i(m.objects().find(qn));
    if (i == m.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << qn;
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found +
                boost::lexical_cast<std::string>(qn)));
    }
    return *(i->second);
}

std::list<qname>& indexer::
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

void indexer::properties_for_concept(const sml::qname& qn,
    std::list<sml::property>& properties,
    std::unordered_set<sml::qname>& processed_qnames,
    const model& m) const {

    if (processed_qnames.find(qn) != processed_qnames.end())
        return;

    processed_qnames.insert(qn);
    const auto i(m.concepts().find(qn));
    if (i == m.concepts().end()) {
        const auto& sn(qn.simple_name());
        BOOST_LOG_SEV(lg, error) << concept_not_found << sn;
        BOOST_THROW_EXCEPTION(indexing_error(concept_not_found + sn));
    }

    const auto& concept(i->second);
    const auto& cp(concept.local_properties());
    properties.insert(properties.end(), cp.begin(), cp.end());
}

void indexer::expand_concept_hierarchy(const model& m, const qname& qn,
    std::list<qname>& concepts) const {
    const auto i(m.concepts().find(qn));
    if (i == m.concepts().end()) {
        std::ostringstream s;
        s << orphan_concept << ". concept: "
          << qn.simple_name() << " could not be found.";

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(indexing_error(s.str()));
    }

    for (const auto& c : i->second.refines())
        expand_concept_hierarchy(m, c, concepts);

    concepts.push_back(qn);
}

void indexer::populate_all_properties(abstract_object& o, const model& m) {
    for (const auto& pair : o.inherited_properties()) {
        o.all_properties().insert(o.all_properties().end(),
            pair.second.begin(), pair.second.end());
    }

    o.all_properties().insert(o.all_properties().end(),
        o.local_properties().begin(), o.local_properties().end());

    const auto rt(relationship_types::modeled_concepts);
    const auto i(o.relationships().find(rt));
    if (i == o.relationships().end())
        return;

    std::unordered_set<sml::qname> processed_qnames;
    for (const auto& qn : i->second)
        properties_for_concept(qn, o.all_properties(), processed_qnames, m);
}

void indexer::
index_inheritance(abstract_object& parent, abstract_object& leaf, model& m) {
    const bool is_root(!parent.is_child());

    if (is_root) {
        auto& op(leaf.relationships()[relationship_types::original_parents]);
        op.push_back(parent.name());

        auto& l(parent.relationships()[relationship_types::leaves]);
        l.push_back(leaf.name());

        populate_all_properties(parent, m);

        return;
    }

    const auto parents(find_relationships(relationship_types::parents, parent));
    for (auto& qn : parents) {
        auto& grand_parent(find_object(qn, m));
        index_inheritance(grand_parent, leaf, m);
        parent.inherited_properties().insert(
            std::make_pair(grand_parent.name(), grand_parent.all_properties()));
    }

    populate_all_properties(parent, m);
}

void indexer::index_inheritance(model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing inheritance. Objects: "
                             << m.objects().size();

    for (auto& pair : m.objects()) {
        auto& o(*pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        const bool in_inheritance_relationship(o.is_parent() || o.is_child());
        if (!in_inheritance_relationship) {
            populate_all_properties(o, m);
            continue;
        }

        const bool is_leaf(o.is_parent() && !o.is_child());
        if (!is_leaf)
            continue;

        const auto parents(find_relationships(relationship_types::parents, o));
        for (auto& qn : parents) {
            auto& parent(find_object(qn, m));
            index_inheritance(parent, o, m);
        }
    }
}

void indexer::index_modeled_concepts(model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing modeled concepts. Objects: "
                             << m.objects().size();

    for (auto& pair : m.objects()) {
        auto& o(*pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        BOOST_LOG_SEV(lg, debug) << "Indexing concepts for type " << o.name();
        const auto rt(relationship_types::modeled_concepts);
        const auto i(o.relationships().find(rt));
        if (i == o.relationships().end() || i->second.empty())
            continue;

        /*
         * first pass to expand concepts. we basically want to find
         * out the complete set of concepts this type models, taking
         * into account all the refinement relationships they may have
         * with other concepts.
         */
        std::list<qname> expanded_modeled_concepts;
        for (const auto& qn : i->second)
            expand_concept_hierarchy(m, qn, expanded_modeled_concepts);

        i->second.clear();
        for (const auto& qn : expanded_modeled_concepts)
            i->second.push_back(qn);
    }

    /*
     * second pass to expand concepts. we now look at all of the
     * inheritance relationships and remove any concepts which have
     * already been modeled by the type's parent.
     */
    for (auto& pair : m.objects()) {
        auto& o(*pair.second);

        const auto rt(relationship_types::modeled_concepts);
        const auto i(o.relationships().find(rt));
        if (i == o.relationships().end() || i->second.empty())
            continue;

        BOOST_LOG_SEV(lg, debug) << "Resolving concepts for type: " << o.name();
        std::set<qname> mc;
        for (const auto& qn : i->second)
            mc.insert(qn);

        std::set<qname> pmc;
        const auto j(o.relationships().find(relationship_types::parents));
        if (j == o.relationships().end() || j->second.empty())
            continue;

        for (const auto& pqn : j->second) {
            const auto k(m.objects().find(pqn));
            if (k == m.objects().end()) {
                std::ostringstream s;
                s << orphan_object << ": " << o.name().simple_name()
                  << ". parent: " << pqn.simple_name();

                BOOST_LOG_SEV(lg, error) << s.str();
                BOOST_THROW_EXCEPTION(indexing_error(s.str()));
            }

            const auto m(o.relationships().find(rt));
            if (m == o.relationships().end())
                continue;

            for (const auto& qn : m->second)
                pmc.insert(qn);
        }

        std::set<qname> result;
        std::set_difference(mc.begin(), mc.end(), pmc.begin(), pmc.end(),
            std::inserter(result, result.end()));

        // FIXME: can we not just push the result of the set difference?
        auto tmp(i->second);
        i->second.clear();
        o.modeled_concepts().clear();
        for (const auto& qn : tmp) {
            if (result.find(qn) != result.end()) {
                i->second.push_back(qn);
                o.modeled_concepts().push_back(qn);
            }
        }
    }
}

void indexer::index(abstract_object& /*o*/) {
}

void indexer::index(model& m) {
    index_modeled_concepts(m);
    index_inheritance(m);
}

} }
