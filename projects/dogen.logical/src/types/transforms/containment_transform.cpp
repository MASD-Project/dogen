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
     *
     * @return True if inserted, false otherwise.
     * @pre Element must not already exist in the container.
     */
    template<typename Container>
    bool try_insert(std::unordered_map<std::string, Container>& cm,
        const std::string& container_id, const std::string& containee_id) {
        /*
         * First we check to see if the container exists in the
         * supplied collection. It may not exist if it is of a
         * different logical type.
         */
        const auto i(cm.find(container_id));
        if (i == cm.end()) {
            BOOST_LOG_SEV(lg, debug) << "Could not find container: '"
                                     << container_id << "'. ";
            return false;
        }

        /*
         * If it does exist, we expect the insertion to work cleanly.
         */
        auto& container(*i->second);
        const bool inserted(container.contains().insert(containee_id).second);
        if (inserted) {
            BOOST_LOG_SEV(lg, debug) << "Added element. Containee: '"
                                     << containee_id
                                     << "' Container: '" << container_id;
            return true;
        }

        /*
         * It seems we already contained an element with that name.
         */
        BOOST_LOG_SEV(lg, error) << duplicate_element << containee_id;
        BOOST_THROW_EXCEPTION(
            transformation_error(duplicate_element + containee_id));
    }

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

void updater::update_containing_element(const entities::name& container,
    const entities::name& containee) {
    /*
     * First check to see if the container is a module (most obvious
     * case). If it is, update the module membership list.
     */
    BOOST_LOG_SEV(lg, debug) << "Trying module as the container.";
    const auto container_id(container.qualified().dot());
    const auto containee_id(containee.qualified().dot());
    auto& mods(model_.structural_elements().modules());
    bool inserted = try_insert(mods, container_id, containee_id);
    if (inserted)
        return;

    /*
     * Now we check to see if it is a modeline group.
     */
    BOOST_LOG_SEV(lg, debug) << "Trying as a modeline group.";
    auto& mgs(model_.decoration_elements().modeline_groups());
    inserted = try_insert(mgs, container_id, containee_id);
    if (inserted)
        return;

    /*
     * If we could not find the containing element in any of the
     * expected containers, we need to throw. The model has some kind
     * of logical inconsistency.
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
    helpers::name_factory nf;
    const auto n(nf.build_containing_element_name(e.name()));
    if (!n) {
        /*
         * The element does not appear to be contained anywhere. There
         * are only two special cases caught by this: global module
         * and model module. All other elements should have some form
         * of containment.
         */
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
    BOOST_LOG_SEV(lg, trace) << "Element is contained by: " << container_id;
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
