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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/modeline.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/helpers/name_factory.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/containment_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.containment_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string separator(".");
const std::string missing_container("Could not find containing element: ");
const std::string duplicate_modeline(
    "Found more than one modeline with the same id: ");

}

namespace masd::dogen::coding::transforms {

namespace {

/**
 * @brief Updates containment relationships in model.
 */
class updater {
public:
    updater(meta_model::model& m) : model_(m) { }

private:
    /**
     * @brief Creates the name of the containing element, derived from
     * the element's name.
     */
    boost::optional<meta_model::name>
    create_containing_element_name(const meta_model::name& n) const;

    /**
     * @brief Update the containing element with information about the
     * relationship.
     */
    void update_containing_element(const meta_model::name& container,
        const meta_model::name& containee);

    void update(meta_model::element& e);

public:
    void operator()(meta_model::element&) { }
    void operator()(meta_model::module& m) { update(m); }
    void operator()(meta_model::object_template& ot) { update(ot); }
    void operator()(meta_model::builtin& b) { update(b); }
    void operator()(meta_model::enumeration& e) { update(e); }
    void operator()(meta_model::primitive& p) { update(p); }
    void operator()(meta_model::object& o) { update(o); }
    void operator()(meta_model::exception& e) { update(e); }
    void operator()(meta_model::visitor& v) { update(v); }
    void operator()(meta_model::modeline& ml) { update(ml); }

public:
    meta_model::model& model_;
};

boost::optional<meta_model::name>
updater::create_containing_element_name(const meta_model::name& n) const {
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
        return boost::optional<meta_model::name>();
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
        return boost::optional<meta_model::name>();
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

void updater::update_containing_element(const meta_model::name& container,
    const meta_model::name& containee) {

    const auto container_id(container.qualified().dot());
    const auto containee_id(containee.qualified().dot());

    /*
     * First we check to see if the container is a module. If it is,
     * update the module membership list.
     */
    auto& mods(model_.modules());
    const auto i(mods.find(container_id));
    if (i != mods.end()) {
        BOOST_LOG_SEV(lg, debug) << "Adding type to module. Type: '"
                                 << containee_id
                                 << "' Module: '" << container_id;
        auto& module(*i->second);
        module.members().push_back( containee_id);
        return;
    } else {
        BOOST_LOG_SEV(lg, debug) << "Could not find module: '"
                                 << container_id << "'. "
                                 << "Trying as a modeline group.";
    }

    /*
     * Now we check to see if it is a modeline group.
     */
    auto& mgs(model_.modeline_groups());
    const auto j(mgs.find(container_id));
    if (j != mgs.end()) {
        BOOST_LOG_SEV(lg, debug) << "Adding type to modeline group. Type: '"
                                 << containee_id
                                 << "' Module: '" << container_id;

        auto& mg(*j->second);
        const bool inserted(mg.modeline_ids().insert(containee_id).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_modeline << containee_id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_modeline + containee_id));
        }
        return;
    }

    /*
     * If we could not find the containing elements, we need to throw.
     */
    BOOST_LOG_SEV(lg, error) << missing_container << container_id;
    BOOST_THROW_EXCEPTION(
        transformation_error(missing_container + container_id));
}

void updater::update(meta_model::element& e) {
    /*
     * First we must determine what the containing element should look
     * like - or if it should even exist at all.
     */
    const auto n(create_containing_element_name(e.name()));
    if (!n)
        return;

    /*
     * If we did find a containing element name, we need to update the
     * containment relationship with that element and also its
     * reciprocal.
     */
    update_containing_element(*n, e.name());
    e.contained_by(n);
}

}

void containment_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "containment transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    updater u(m);
    meta_model::elements_traversal(m, u);

    stp.end_transform(m);
}

}
