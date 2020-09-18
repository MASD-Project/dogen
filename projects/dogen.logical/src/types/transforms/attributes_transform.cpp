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
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.identification/types/helpers/logical_name_factory.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/attributes_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.attributes_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string object_template_not_found(
    "Object template not found in object templates container: ");

}

namespace dogen::logical::transforms {

entities::structural::object& attributes_transform::
find_object(const identification::entities::logical_name& n,
    entities::model& m) {
    auto i(m.structural_elements().objects().find(n.id()));
    if (i == m.structural_elements().objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << n.id();
        BOOST_THROW_EXCEPTION(
            transformation_error(object_not_found + n.id().value()));
    }
    return *i->second;
}

entities::structural::object_template& attributes_transform::
find_object_template(const identification::entities::logical_name& n,
    entities::model& m) {
    auto i(m.structural_elements().object_templates().find(n.id()));
    if (i == m.structural_elements().object_templates().end()) {
        BOOST_LOG_SEV(lg, error) << object_template_not_found << n.id();
        BOOST_THROW_EXCEPTION(
            transformation_error(object_template_not_found + n.id().value()));
    }
    return *i->second;
}

void attributes_transform::expand_object(entities::structural::object& o,
    entities::model& m, std::unordered_set<std::string>& processed_ids) {
    const auto id(o.name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Expanding object: " << id;

    if (processed_ids.find(id) != processed_ids.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed: " << id;
        return;
    }

    /*
     * Grab all attributes from all of the object templates this
     * object is associated with, in one go.
     */
    std::list<entities::attribute> object_template_attributes;
    for (const auto& otn : o.object_templates()) {
        auto& ot(find_object_template(otn, m));
        const auto& p(ot.local_attributes());
        object_template_attributes.insert(object_template_attributes.end(),
            p.begin(), p.end());
    }

    /*
     * Repopulate the names of attribute sourced from object
     * templates. These have originally been populated by the adaptor
     * at the engine level. However, as we copied these across, we
     * need to ensure they are located correctly in logical space:
     * i.e. their qualified name should indicate that their are no
     * longer part of the object template and are now part of the
     * object.
     */
    identification::helpers::logical_name_factory f;
    for (auto& attr : object_template_attributes) {
        const auto n(f.build_attribute_name(o.name(), attr.name().simple()));
        attr.name(n);
    }

    /*
     * Now, copy across the object template attributes into the object
     * itself, and add them to the local attributes at the
     * beginning. The idea is to keep changes from rippling through,
     * but we haven't yet collected evidence to prove this order is
     * more effective than other alternatives.
     */
    o.local_attributes().insert(o.local_attributes().begin(),
        object_template_attributes.begin(), object_template_attributes.end());

    /*
     * Setup fluency and immutability on all local attributes. Values
     * for these two properties are inherited from the object
     * itself. Note that this is done *after* we've merged the object
     * template's attributes. The logic is as follows: if we are a
     * fluent or an immutable object, we also need to mark all
     * properties we've inherited via object templates as these have
     * values that are specific to the _object_ rather than the object
     * template. This may actually a bit of a problem because it means
     * we are instantiating different object templates, some of which
     * could have been marked as immutable/mutable,
     * fluent/non-fluent. In effect, it means these properties have no
     * meaning in the context of object templates. This consistency
     * problem also applies to parent/descendants.
     */
    if (o.is_fluent() || o.is_immutable()) {
        for (auto& attr : o.local_attributes()) {
            attr.is_fluent(o.is_fluent());
            attr.is_immutable(o.is_immutable());
        }
    }

    /*
     * Now handle all of the inherited properties. We insert our
     * parent's properties first on our all attributes container by
     * design; local attributes are last. This minimises changes when
     * new properties are added to the descendant.
     */
    for (const auto& pn : o.parents()) {
        auto& parent(find_object(pn, m));
        expand_object(parent, m, processed_ids);

        /*
         * Note that we insert the parent and its attributes
         * _regardless_ of whether it has any attributes or not into
         * the inherited attributes container.
         */
        const auto& pattrs(parent.all_attributes());
        o.inherited_attributes().insert(std::make_pair(pn, pattrs));

        if (!pattrs.empty()) {
            auto& attrs(o.all_attributes());
            attrs.insert(attrs.end(), pattrs.begin(), pattrs.end());
        }
    }

    o.all_attributes().insert(o.all_attributes().end(),
        o.local_attributes().begin(), o.local_attributes().end());

    processed_ids.insert(id);
}

void attributes_transform::expand_objects(entities::model& m) {
    auto& objs(m.structural_elements().objects());
    BOOST_LOG_SEV(lg, debug) << "Expanding objects. Count: "
                             << objs.size();

    std::unordered_set<std::string> processed_ids;
    for (auto& pair : objs) {
        auto& o(*pair.second);
        expand_object(o, m, processed_ids);
    }
}

void attributes_transform::expand_object_template(
    entities::structural::object_template& ot, entities::model& m,
    std::unordered_set<std::string>& processed_ids) {
    const auto id(ot.name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Expanding object template:" << id;

    if (processed_ids.find(id) != processed_ids.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed:" << id;
        return;
    }

    /*
     * Setup the all attributes and inherited attributes containers.
     */
    ot.all_attributes().insert(ot.all_attributes().end(),
        ot.local_attributes().begin(), ot.local_attributes().end());

    for (const auto& n : ot.parents()) {
        auto& parent(find_object_template(n, m));
        expand_object_template(parent, m, processed_ids);

        ot.inherited_attributes().insert(
            std::make_pair(parent.name(), parent.local_attributes()));

        ot.all_attributes().insert(ot.all_attributes().end(),
            parent.local_attributes().begin(), parent.local_attributes().end());
    }
    processed_ids.insert(id);
}

void attributes_transform::expand_object_templates(entities::model& m) {
    auto& tpl(m.structural_elements().object_templates());
    BOOST_LOG_SEV(lg, debug) << "Expanding object templates. Count: "
                             << tpl.size();

    std::unordered_set<std::string> processed_ids;
    for (auto& pair : tpl) {
        auto& otp(*pair.second);
        expand_object_template(otp, m, processed_ids);
    }
}

void attributes_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "attributes",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    expand_object_templates(m);
    expand_objects(m);

    stp.end_transform(m);
}

}
