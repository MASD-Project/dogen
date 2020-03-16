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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/helpers/resolver.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/object_templates_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.object_templates_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string object_template_not_found(
    "Object template not found in object templates container: ");

}

namespace dogen::logical::entities {

/**
 * @brief Add comparable support for names.
 *
 * This is required as part of the current (very sub-optimal)
 * implementation of object templates processing. It is used in the
 * set difference.
 */
inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.qualified().dot() < rhs.qualified().dot();
}

}

namespace dogen::logical::transforms {

entities::structural::object& object_templates_transform::
find_object(const entities::name& n, entities::model& m) {
    auto i(m.structural_elements().objects().find(n.qualified().dot()));
    if (i == m.structural_elements().objects().end()) {
        const auto id(n.qualified().dot());
        BOOST_LOG_SEV(lg, error) << object_not_found << id;
        BOOST_THROW_EXCEPTION(transformation_error(object_not_found +  id));
    }
    return *i->second;
}

entities::structural::object_template& object_templates_transform::
resolve_object_template(const entities::name& owner,
    const entities::name& object_template_name, entities::model& m) {
    using helpers::resolver;
    const auto& n(object_template_name);
    const auto on(resolver::try_resolve_object_template_name(owner, n, m));
    if (!on) {
        const auto id(n.qualified().dot());
        BOOST_LOG_SEV(lg, error) << object_template_not_found << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(object_template_not_found + id));
    }

    auto i(m.structural_elements().object_templates().find(
            on->qualified().dot()));
    if (i == m.structural_elements().object_templates().end()) {
        const auto id(on->qualified().dot());
        BOOST_LOG_SEV(lg, error) << object_template_not_found << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(object_template_not_found + id));
    }
    return *i->second;
}

void object_templates_transform::
remove_duplicates(std::list<entities::name>& names) {
    std::unordered_set<entities::name> processed;

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

void object_templates_transform::
expand_object(entities::structural::object& o, entities::model& m,
    std::unordered_set<entities::name>& processed_names) {
    BOOST_LOG_SEV(lg, debug) << "Expanding object: "
                             << o.name().qualified().dot();

    if (processed_names.find(o.name()) != processed_names.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed.";
        return;
    }

    if (o.object_templates().empty()) {
        processed_names.insert(o.name());
        BOOST_LOG_SEV(lg, debug) << "Object instantiates no object templates.";
        return;
    }

    /*
     * For each of the object templates that we model, perform an
     * expansion including their parents and so on. We can rely on the
     * object templates'' @e parents container for this.
     */
    std::list<entities::name> expanded_parents;
    for (auto& otn : o.object_templates()) {
        auto& ot(resolve_object_template(o.name(), otn, m));
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
     * the object templates our parents model.
     */
    BOOST_LOG_SEV(lg, debug) << "Object has a parent, computing set diff.";

    std::set<entities::name> ours;
    ours.insert(expanded_parents.begin(), expanded_parents.end());

    std::set<entities::name> theirs;
    const auto& n(o.parents().front());
    auto& parent(find_object(n, m));
    expand_object(parent, m, processed_names);

    const auto& ot(parent.object_templates());
    if (!ot.empty())
        theirs.insert(ot.begin(), ot.end());

    /*
     * We want to only instantiate object templates which have not yet
     * been instantiated by any of our parents.
     */
    std::set<entities::name> diff;
    std::set_difference(ours.begin(), ours.end(), theirs.begin(), theirs.end(),
        std::inserter(diff, diff.end()));

    /*
     * Reinsert all of the instantiated object templates which are
     * part of the set difference. We do this instead of just using
     * the set difference directly to preserve order.
     */
    o.object_templates().clear();
    for (const auto& n : expanded_parents) {
        if (diff.find(n) != diff.end())
            o.object_templates().push_back(n);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished indexing object.";
}

void object_templates_transform::expand_objects(entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Expanding objects: " << m.structural_elements().objects().size();

    std::unordered_set<entities::name> processed_names;
    for (auto& pair : m.structural_elements().objects()) {
        auto& o(*pair.second);
        expand_object(o, m, processed_names);
    }
}

void object_templates_transform::
expand_object_template(entities::structural::object_template& otp,
    entities::model& m,
    std::unordered_set<entities::name>& processed_names) {
    BOOST_LOG_SEV(lg, debug) << "Expand object template: "
                             << otp.name().qualified().dot();

    if (processed_names.find(otp.name()) != processed_names.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object template already processed.";
        return;
    }

    if (otp.parents().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Object template has no parents.";
        processed_names.insert(otp.name());
        return;
    }

    std::list<entities::name> expanded_parents;
    for (auto& n : otp.parents()) {
        auto& parent(resolve_object_template(otp.name(), n, m));
        expand_object_template(parent, m, processed_names);
        expanded_parents.push_back(parent.name());
        expanded_parents.insert(expanded_parents.end(),
            parent.parents().begin(), parent.parents().end());
    }

    BOOST_LOG_SEV(lg, debug) << "Computing reduced set for object template.";
    remove_duplicates(expanded_parents);
    otp.parents(expanded_parents);
    processed_names.insert(otp.name());
}

void object_templates_transform::expand_object_templates(entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Expading object templates: "
                             << m.structural_elements().object_templates().size();

    std::unordered_set<entities::name> processed_names;
    for (auto& pair : m.structural_elements().object_templates()) {
        auto& otp(*pair.second);
        expand_object_template(otp, m, processed_names);
    }
}

void object_templates_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "object templates transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * We must expand object templates before we expand objects as we
     * rely on the expanded attributes.
     */
    expand_object_templates(m);
    expand_objects(m);

    stp.end_transform(m);
}

}
