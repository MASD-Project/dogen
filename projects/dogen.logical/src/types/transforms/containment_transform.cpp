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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/helpers/name_builder.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/containment_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.containment_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string separator(".");
const std::string missing_container("Could not find containing element: ");
const std::string duplicate_element(
    "Found more than one element with the same id: ");

}

namespace dogen::logical::transforms {

namespace {

/**
 * @brief Updates containment relationships in model.
 */
class updater {
public:
    updater(entities::model& m) : model_(m) { }

private:
    /**
     * @brief Try to insert containee ID into the container, if one
     * can be located in the container map.
     */
    template<typename Container>
    bool try_insert(std::unordered_map<std::string, Container>& cm,
        const std::string& container_id, const std::string& containee_id) {
        const auto i(cm.find(container_id));
        if (i == cm.end()) {
            BOOST_LOG_SEV(lg, debug) << "Could not find container: '"
                                     << container_id << "'. ";
            return false;
        }

        BOOST_LOG_SEV(lg, debug) << "Adding element.  Containee: '"
                                 << containee_id
                                 << "' Container: '" << container_id;
        auto& container(*i->second);
        const bool inserted(container.contains().insert(containee_id).second);
        if (inserted)
            return true;

        BOOST_LOG_SEV(lg, error) << duplicate_element << containee_id;
        BOOST_THROW_EXCEPTION(
            transformation_error(duplicate_element + containee_id));
    }

    /**
     * @brief Creates the name of the containing element, derived from
     * the element's name.
     */
    boost::optional<entities::name>
    create_containing_element_name(const entities::name& n) const;

    /**
     * @brief Update the containing element with information about the
     * relationship.
     */
    void update_containing_element(const entities::name& container,
        const entities::name& containee);

    void update(entities::element& e);

public:
    void operator()(entities::element&) { }
    void operator()(entities::structural::module& m) { update(m); }
    void operator()(entities::structural::object_template& ot) { update(ot); }
    void operator()(entities::structural::builtin& b) { update(b); }
    void operator()(entities::structural::enumeration& e) { update(e); }
    void operator()(entities::structural::primitive& p) { update(p); }
    void operator()(entities::structural::object& o) { update(o); }
    void operator()(entities::structural::exception& e) { update(e); }
    void operator()(entities::structural::visitor& v) { update(v); }
    void operator()(entities::decoration::modeline& ml) { update(ml); }

public:
    entities::model& model_;
};

boost::optional<entities::name>
updater::create_containing_element_name(const entities::name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Creating containing element name for: "
                             << n.qualified().dot();

    /*
     * First we determine if the element is placed in the global
     * namespace. If it is, we will deal with it (much) later on, in
     * the global module transform.
     */
    const bool in_global_namespace(n.location().model_modules().empty());
    if (in_global_namespace) {
        BOOST_LOG_SEV(lg, debug) << "Element is in global module so, it has"
                                 << " no containing module yet. Type: "
                                 << n.qualified().dot();
        return boost::optional<entities::name>();
    }

    /*
     * Next, check to see if the element we are processing is the
     * model's module itself. If it is, we should not do anything and
     * again let the global module transform handle it.
     *
     * FIXME: this means we cannot have an element with the same name
     * as the model.
     */
    const bool at_model_level(n.location().internal_modules().empty());
    const auto mn(n.location().model_modules().back());
    if (at_model_level && n.simple() == mn) {
        BOOST_LOG_SEV(lg, debug) << "Type is a model module, so containing "
                                 << "module will be handled later. Type: "
                                 << n.qualified().dot();
        return boost::optional<entities::name>();
    }

    /*
     * Now, deal with the case where the element has been placed
     * inside another element - most likely a module. It is either:
     *
     * - the model module;
     * - some other internal module;
     * - another element capable of containment (e.g. modeline group).
     *
     * Regardless of the source of containment, we need to build the
     * name for the containing element.
     */
    helpers::name_builder b;

    /*
     * We can always take the external modules regardless because
     * these do not contribute to the modules in the model.
     */
    b.external_modules(n.location().external_modules());

    auto imp(n.location().internal_modules());
    if (imp.empty()) {
        /*
         * If there are no internal modules, we must be at the
         * top-level, so take the model name.
         */
        b.simple_name(mn);

        /*
         * The model name may be composite. If so, we need to make
         * sure we add the remaining components.
         */
        if (!n.location().model_modules().empty()) {
            auto remaining_model_modules(n.location().model_modules());
            remaining_model_modules.pop_back();
            b.model_modules(remaining_model_modules);
        }

        return b.build();
    }

    /*
     * If we are an internal element capable of containment
     * (e.g. module, modeline group, etc), we can take the element
     * name and use that as our simple name. We need to add the
     * remaining internal module names to our location.
     */
    b.model_modules(n.location().model_modules());
    b.simple_name(imp.back());
    imp.pop_back();
    b.internal_modules(imp);
    return b.build();
}

void updater::update_containing_element(const entities::name& container,
    const entities::name& containee) {

    const auto container_id(container.qualified().dot());
    const auto containee_id(containee.qualified().dot());

    /*
     * First we check to see if the container is a module. If it is,
     * update the module membership list.
     */
    bool inserted = try_insert(model_.structural_elements().modules(),
        container_id, containee_id);
    if (inserted)
        return;

    /*
     * Now we check to see if it is a modeline group.
     */
    BOOST_LOG_SEV(lg, trace) << "Could not find module: '"
                             << container_id << "'. "
                             << "Trying as a modeline group.";
    inserted = try_insert(model_.decoration_elements().modeline_groups(), container_id, containee_id);
    if (inserted)
        return;

    /*
     * If we could not find the containing element, we need to throw.
     */
    BOOST_LOG_SEV(lg, error) << missing_container << container_id;
    BOOST_THROW_EXCEPTION(
        transformation_error(missing_container + container_id));
}

void updater::update(entities::element& e) {
    BOOST_LOG_SEV(lg, trace) << "Processing element: "
                             << e.name().qualified().dot();

    /*
     * First we must determine what the containing element should look
     * like - or if it should even exist at all.
     */
    const auto n(create_containing_element_name(e.name()));
    if (!n) {
        BOOST_LOG_SEV(lg, trace) << "Element is not contained.";
        return;
    }

    /*
     * If we did find a containing element name, we need to update the
     * containment relationship with that element and also its
     * reciprocal.
     */
    const auto container_id(n->qualified().dot());
    update_containing_element(*n, e.name());
    e.contained_by(container_id);
    BOOST_LOG_SEV(lg, trace) << "Element is contained by: "
                             << container_id;
}

}

void containment_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "containment transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    updater u(m);
    entities::elements_traversal(m, u);

    stp.end_transform(m);
}

}
