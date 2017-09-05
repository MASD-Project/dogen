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
#include <boost/throw_exception.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/types/helpers/resolver.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/concepts_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.concepts_transform"));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string concept_not_found(
    "Object template not found in object templates container: ");

}

namespace dogen {
namespace yarn {

namespace meta_model {

/**
 * @brief Add comparable support for names.
 *
 * This is required as part of the current (very sub-optimal)
 * implementation of concept processing. It is used in the set
 * difference.
 */
inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.id() < rhs.id();
}

}

namespace transforms {

meta_model::object& concepts_transform::
find_object(const meta_model::name& n, meta_model::endomodel& im) {
    auto i(im.objects().find(n.id()));
    if (i == im.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << n.id();
        BOOST_THROW_EXCEPTION(transformation_error(object_not_found +  n.id()));
    }
    return *i->second;
}

meta_model::object_template&
concepts_transform::resolve_concept(const meta_model::name& owner,
    const meta_model::name& concept_name, meta_model::endomodel& im) {
    using helpers::resolver;
    const auto oc(resolver::try_resolve_concept_name(owner, concept_name, im));
    if (!oc) {
        const auto id(concept_name.id());
        BOOST_LOG_SEV(lg, error) << concept_not_found << id;
        BOOST_THROW_EXCEPTION(transformation_error(concept_not_found + id));
    }

    auto i(im.object_templates().find(oc->id()));
    if (i == im.object_templates().end()) {
        const auto id(oc->id());
        BOOST_LOG_SEV(lg, error) << concept_not_found << id;
        BOOST_THROW_EXCEPTION(transformation_error(concept_not_found + id));
    }
    return *i->second;
}

void concepts_transform::remove_duplicates(std::list<meta_model::name>& names) {
    std::unordered_set<meta_model::name> processed;

    BOOST_LOG_SEV(lg, debug) << "Removing duplicates from list. Original size: "
                             << names.size();

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

void concepts_transform::
expand_object(meta_model::object& o, meta_model::endomodel& im,
    std::unordered_set<meta_model::name>& processed_names) {
    BOOST_LOG_SEV(lg, debug) << "Expanding object: " << o.name().id();

    if (processed_names.find(o.name()) != processed_names.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed.";
        return;
    }

    if (o.object_templates().empty()) {
        processed_names.insert(o.name());
        BOOST_LOG_SEV(lg, debug) << "Object models no concepts.";
        return;
    }

    /*
     * For each of the object templates that we model, perform an
     * expansion including their parents and so on. We can rely on the
     * concepts' @e parents container for this.
     */
    std::list<meta_model::name> expanded_parents;
    for (auto& otn : o.object_templates()) {
        auto& ot(resolve_concept(o.name(), otn, im));
        expanded_parents.push_back(ot.name());
        expanded_parents.insert(expanded_parents.end(),
            ot.parents().begin(), ot.parents().end());
    }

    /*
     * Since the expanded list may include duplicates, we must first
     * remove those.
     */
    remove_duplicates(expanded_parents);

    /*
     * First handle the simpler case of objects that do not have a
     * parent.
     */
    if (o.parents().empty()) {
        o.object_templates(expanded_parents);
        BOOST_LOG_SEV(lg, debug) << "Object has no parent, using reduced set.";
        return;
    }

    /*
     * If an object does have a parent, we must then find out all of
     * the concepts that our parents model.
     */
    BOOST_LOG_SEV(lg, debug) << "Object has a parent, computing set diff.";

    std::set<meta_model::name> our_concepts;
    our_concepts.insert(expanded_parents.begin(), expanded_parents.end());

    std::set<meta_model::name> their_concepts;
    const auto& n(o.parents().front());
    auto& parent(find_object(n, im));
    expand_object(parent, im, processed_names);

    const auto& ot(parent.object_templates());
    if (!ot.empty())
        their_concepts.insert(ot.begin(), ot.end());

    /*
     * We want to only model concepts which have not yet been modeled
     * by any of our parents.
     */
    std::set<meta_model::name> result;
    std::set_difference(our_concepts.begin(), our_concepts.end(),
        their_concepts.begin(), their_concepts.end(),
        std::inserter(result, result.end()));

    /*
     * Reinsert all of the modeled concepts which are part of the set
     * difference. We do this instead of just using the set difference
     * directly to preserve order.
     */
    o.object_templates().clear();
    for (const auto& n : expanded_parents) {
        if (result.find(n) != result.end())
            o.object_templates().push_back(n);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished indexing object.";
}

void concepts_transform::expand_objects(meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding objects: " << im.objects().size();

    std::unordered_set<meta_model::name> processed_names;
    for (auto& pair : im.objects()) {
        auto& o(*pair.second);
        expand_object(o, im, processed_names);
    }
}

void concepts_transform::expand_concept(meta_model::object_template& ot,
    meta_model::endomodel& im,
    std::unordered_set<meta_model::name>& processed_names) {
    BOOST_LOG_SEV(lg, debug) << "Expand concept: " << ot.name().id();

    if (processed_names.find(ot.name()) != processed_names.end()) {
        BOOST_LOG_SEV(lg, debug) << "Concept already processed.";
        return;
    }

    if (ot.parents().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Concept parents no concepts.";
        processed_names.insert(ot.name());
        return;
    }

    std::list<meta_model::name> expanded_parents;
    for (auto& n : ot.parents()) {
        auto& parent(resolve_concept(ot.name(), n, im));
        expand_concept(parent, im, processed_names);
        expanded_parents.push_back(parent.name());
        expanded_parents.insert(expanded_parents.end(),
            parent.parents().begin(), parent.parents().end());
    }

    BOOST_LOG_SEV(lg, debug) << "Computing reduced set for concept.";
    remove_duplicates(expanded_parents);
    ot.parents(expanded_parents);
    processed_names.insert(ot.name());
}

void concepts_transform::expand_concepts(meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Expading concepts: "
                             << im.object_templates().size();

    std::unordered_set<meta_model::name> processed_names;
    for (auto& pair : im.object_templates()) {
        auto& c(*pair.second);
        expand_concept(c, im, processed_names);
    }
}

void concepts_transform::transform(meta_model::endomodel& im) {
    /*
     * We must expand concepts before we expand objects as we rely on
     * the expanded attributes.
     */
    expand_concepts(im);
    expand_objects(im);
}

} } }
