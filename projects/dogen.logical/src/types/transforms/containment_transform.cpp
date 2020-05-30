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
         * If it does exist, add the containee to the container.
         */
        auto& container(*i->second);
        container.contains().push_back(containee_id);
        BOOST_LOG_SEV(lg, debug) << "Added element. Containee: '"
                                 << containee_id
                                 << "' Container: '" << container_id << "'";
        return true;
    }

    /**
     * @brief Update the containing element with information about the
     * relationship.
     */
    void update_containing_element(const entities::name& container,
        const entities::name& containee);

    void update(entities::element& e);

public:
    void operator()(entities::element& v) { update(v); }

public:
    entities::model& model_;
};

void updater::update_containing_element(const entities::name& container,
    const entities::name& containee) {
    /*
     * Check all of the elements which can contain other elements to
     * see if they are the designated container. If it is, we update
     * the membership list.
     */
    const auto container_id(container.qualified().dot());
    const auto containee_id(containee.qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Looking for container: " << container_id;

    /*
     * Modules.
     */
    BOOST_LOG_SEV(lg, debug) << "Trying module as the container.";
    auto& mods(model_.structural_elements().modules());
    bool inserted = try_insert(mods, container_id, containee_id);
    if (inserted)
        return;

    /*
     * Modeline groups.
     */
    BOOST_LOG_SEV(lg, debug) << "Trying modeline group as the container.";
    auto& mgs(model_.decoration_elements().modeline_groups());
    inserted = try_insert(mgs, container_id, containee_id);
    if (inserted)
        return;

    /*
     * Backends.
     */
    BOOST_LOG_SEV(lg, debug) << "Trying backend as the container.";
    auto& bs(model_.physical_elements().backends());
    inserted = try_insert(bs, container_id, containee_id);
    if (inserted)
        return;

    /*
     * Facets.
     */
    BOOST_LOG_SEV(lg, debug) << "Trying facets as the container.";
    auto& fcts(model_.physical_elements().facets());
    inserted = try_insert(fcts, container_id, containee_id);
    if (inserted)
        return;

    /*
     * We could not find the containing element in any of the expected
     * containers, so we need to throw. The model has some kind of
     * logical inconsistency.
     */
    BOOST_LOG_SEV(lg, error) << missing_container << container_id;
    BOOST_THROW_EXCEPTION(
        transformation_error(missing_container + container_id));
}

void updater::update(entities::element& e) {
    const auto id(e.name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

    /*
     * First we must determine what the containing element should look
     * like - or if it should even exist at all.
     */
    helpers::name_factory nf;
    const auto container_name(nf.build_containing_element_name(e.name()));
    if (!container_name) {
        /*
         * The element does not appear to be contained anywhere. There
         * are only two special cases caught by this: global module
         * and model module. All other elements should have some form
         * of containment.
         */
        BOOST_LOG_SEV(lg, debug) << "Element is not contained.";
        return;
    }

    /*
     * If we did find a containing element name, we need to update the
     * containment relationship with that element and also its
     * reciprocal.
     */
    const auto container_id(container_name->qualified().dot());
    update_containing_element(*container_name, e.name());
    e.contained_by(container_id);
    BOOST_LOG_SEV(lg, debug) << "Element added to container: " << container_id;
}

class sort_containers {
private:
    template<typename Container>
    void sort(Container& /*c*/) {
        // using logical::entities::name;
        // c.contains().sort(
        //     [](const name& lhs, const name& rhs) {
        //         return lhs.qualified().dot() < rhs.qualified().dot();
        //     });

        /*
         * It seems we already contained an element with that name.
         */
        // BOOST_LOG_SEV(lg, error) << duplicate_element << containee_id;
        // BOOST_THROW_EXCEPTION(
        //     transformation_error(duplicate_element + containee_id));
    }

public:
    void operator()(logical::entities::structural::module& v) { sort(v); }

    //
    // modeline_group
    // logical::entities::physical::backend
    // logical::entities::physical::facet
};

}

void containment_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "containment transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    updater u(m);
    entities::elements_traversal(m, u);

    stp.end_transform(m);
}

}
