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
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/attributes_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.attributes_transform"));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string concept_not_found(
    "Object template not found in object templates container: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

meta_model::object& attributes_transform::
find_object(const meta_model::name& n, meta_model::endomodel& im) {
    const auto id(n.id());
    auto i(im.objects().find(id));
    if (i == im.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << id;
        BOOST_THROW_EXCEPTION(transformation_error(object_not_found + id));
    }
    return *i->second;
}

meta_model::object_template& attributes_transform::
find_concept(const meta_model::name& n, meta_model::endomodel& im) {
    const auto& id(n.id());
    auto i(im.object_templates().find(id));
    if (i == im.object_templates().end()) {
        BOOST_LOG_SEV(lg, error) << concept_not_found << id;
        BOOST_THROW_EXCEPTION(transformation_error(concept_not_found + id));
    }
    return *i->second;
}

void attributes_transform::expand_object(meta_model::object& o,
    meta_model::endomodel& im,
    std::unordered_set<std::string>& processed_ids) {
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
     * Grab all of the concept attributes in one go, and them add them
     * to the local attributes at the beginning. The idea is to keep
     * changes from rippling through, but there is no evidence that
     * this order is more effective than other alternatives.
     */
    std::list<meta_model::attribute> concept_attributes;
    for (const auto& otn : o.object_templates()) {
        auto& ot(find_concept(otn, im));
        const auto& p(ot.local_attributes());
        concept_attributes.insert(concept_attributes.end(), p.begin(), p.end());
    }

    /*
     * If we are a fluent or an immutable object, we need to mark all
     * properties we've inherited via concepts - these have values
     * that are specific to the object modeling the concept. This is
     * actually a bit of a problem because this means we are modeling
     * different concepts.
     */
    if (o.is_fluent() || o.is_immutable()) {
        for(auto& attr : concept_attributes) {
            attr.is_fluent(o.is_fluent());
            attr.is_immutable(o.is_immutable());
        }
    }

    o.local_attributes().insert(o.local_attributes().begin(),
        concept_attributes.begin(), concept_attributes.end());

    /*
     * Expand all attribute names. At this point, we've only populated
     * attribute simple names. Note that we are doing this after
     * expanding concept attributes. This is because we want to ensure
     * the attributes are located correctly in element space: they are
     * no longer part of the concept but are now part of the object.
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
        auto& parent(find_object(pn, im));
        expand_object(parent, im, processed_ids);

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

void attributes_transform::expand_objects(meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding objects: " << im.objects().size();

    std::unordered_set<std::string> processed_ids;
    for (auto& pair : im.objects()) {
        auto& o(*pair.second);
        expand_object(o, im, processed_ids);
    }
}

void attributes_transform::expand_concept(meta_model::object_template& ot,
    meta_model::endomodel& im, std::unordered_set<std::string>& processed_ids) {
    const auto id(ot.name().id());
    BOOST_LOG_SEV(lg, debug) << "Expanding concept: " << id;

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
        auto& parent(find_concept(n, im));
        expand_concept(parent, im, processed_ids);

        ot.inherited_attributes().insert(
            std::make_pair(parent.name(), parent.local_attributes()));

        ot.all_attributes().insert(ot.all_attributes().end(),
            parent.local_attributes().begin(), parent.local_attributes().end());
    }
    processed_ids.insert(id);
}

void attributes_transform::expand_concepts(meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding object templates: "
                             << im.object_templates().size();

    std::unordered_set<std::string> processed_ids;
    for (auto& pair : im.object_templates()) {
        auto& c(*pair.second);
        expand_concept(c, im, processed_ids);
    }
}

void attributes_transform::transform(meta_model::endomodel& im) {
    expand_concepts(im);
    expand_objects(im);
}

} } }
