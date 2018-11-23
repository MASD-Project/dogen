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
#include "masd.dogen.utility/io/list_io.hpp"
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.coding/types/helpers/name_factory.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/attributes_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.attributes_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string object_template_not_found(
    "Object template not found in object templates container: ");

}

namespace masd::dogen::coding::transforms {

meta_model::object& attributes_transform::
find_object(const meta_model::name& n, meta_model::endomodel& em) {
    const auto id(n.id());
    auto i(em.objects().find(id));
    if (i == em.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << id;
        BOOST_THROW_EXCEPTION(transformation_error(object_not_found + id));
    }
    return *i->second;
}

meta_model::object_template& attributes_transform::
find_object_template(const meta_model::name& n, meta_model::endomodel& em) {
    const auto& id(n.id());
    auto i(em.object_templates().find(id));
    if (i == em.object_templates().end()) {
        BOOST_LOG_SEV(lg, error) << object_template_not_found << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(object_template_not_found + id));
    }
    return *i->second;
}

void attributes_transform::expand_object(meta_model::object& o,
    meta_model::endomodel& em, std::unordered_set<std::string>& processed_ids) {
    const auto id(o.name().id());
    BOOST_LOG_SEV(lg, debug) << "Expanding object: " << id;

    if (processed_ids.find(id) != processed_ids.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed: " << id;
        return;
    }

    /*
     * Setup fluency and immutability on all local attributes.
     */
    if (o.is_fluent() || o.is_immutable()) {
        for (auto& attr : o.local_attributes()) {
            attr.is_fluent(o.is_fluent());
            attr.is_immutable(o.is_immutable());
        }
    }

    /*
     * Grab all of the object template attributes in one go, and them
     * add them to the local attributes at the beginning. The idea is
     * to keep changes from rippling through, but there is no evidence
     * that this order is more effective than other alternatives.
     */
    std::list<meta_model::attribute> object_template_attributes;
    for (const auto& otn : o.object_templates()) {
        auto& ot(find_object_template(otn, em));
        const auto& p(ot.local_attributes());
        object_template_attributes.insert(object_template_attributes.end(),
            p.begin(), p.end());
    }

    /*
     * If we are a fluent or an immutable object, we need to mark all
     * properties we've inherited via object templates - these have
     * values that are specific to the object coding the object
     * template. This is actually a bit of a problem because this
     * means we are instantiating different object templates.
     */
    if (o.is_fluent() || o.is_immutable()) {
        for(auto& attr : object_template_attributes) {
            attr.is_fluent(o.is_fluent());
            attr.is_immutable(o.is_immutable());
        }
    }

    o.local_attributes().insert(o.local_attributes().begin(),
        object_template_attributes.begin(), object_template_attributes.end());

    /*
     * Expand all attribute names. At this point, we've only populated
     * attribute simple names. Note that we are doing this after
     * expanding object template attributes. This is because we want
     * to ensure the attributes are located correctly in element
     * space: they are no longer part of the object template but are
     * now part of the object.
     */
    helpers::name_factory f;
    for (auto& attr : o.local_attributes()) {
        const auto n(f.build_attribute_name(o.name(), attr.name().simple()));
        attr.name(n);
    }

    /*
     * Now handle all of the inherited properties. We insert our
     * parent's properties first on our all attributes container by
     * design; local attributes are last. This minimises changes when
     * new properties are added to the descendant.
     */
    for (const auto& pn : o.parents()) {
        auto& parent(find_object(pn, em));
        expand_object(parent, em, processed_ids);

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

void attributes_transform::expand_objects(meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Expanding objects: " << em.objects().size();

    std::unordered_set<std::string> processed_ids;
    for (auto& pair : em.objects()) {
        auto& o(*pair.second);
        expand_object(o, em, processed_ids);
    }
}

void attributes_transform::expand_object_template(
    meta_model::object_template& ot, meta_model::endomodel& em,
    std::unordered_set<std::string>& processed_ids) {
    const auto id(ot.name().id());
    BOOST_LOG_SEV(lg, debug) << "Expanding object template:" << id;

    if (processed_ids.find(ot.name().id()) != processed_ids.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed:" << id;
        return;
    }

    /*
     * Expand all attribute names. At this point, we've only populated
     * attribute simple names.
     */
    helpers::name_factory f;
    for (auto& attr : ot.local_attributes()) {
        const auto n(f.build_attribute_name(ot.name(), attr.name().simple()));
        attr.name(n);
    }

    /*
     * Setup the all attributes and inherited attributes containers.
     */
    ot.all_attributes().insert(ot.all_attributes().end(),
        ot.local_attributes().begin(), ot.local_attributes().end());

    for (const auto& n : ot.parents()) {
        auto& parent(find_object_template(n, em));
        expand_object_template(parent, em, processed_ids);

        ot.inherited_attributes().insert(
            std::make_pair(parent.name(), parent.local_attributes()));

        ot.all_attributes().insert(ot.all_attributes().end(),
            parent.local_attributes().begin(), parent.local_attributes().end());
    }
    processed_ids.insert(id);
}

void attributes_transform::expand_object_templates(meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Expanding object templates: "
                             << em.object_templates().size();

    std::unordered_set<std::string> processed_ids;
    for (auto& pair : em.object_templates()) {
        auto& otp(*pair.second);
        expand_object_template(otp, em, processed_ids);
    }
}

void attributes_transform::
transform(const context& ctx, meta_model::endomodel& em) {
    tracing::scoped_transform_tracer stp(lg, "attributes transform",
        transform_id, em.name().id(), ctx.tracer(), em);

    expand_object_templates(em);
    expand_objects(em);

    stp.end_transform(em);
}

}
