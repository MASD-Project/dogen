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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/building_error.hpp"
#include "dogen.identification/types/helpers/logical_name_builder.hpp"
#include "dogen.identification/types/helpers/logical_name_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("identification.helpers.logical_name_factory"));

const std::string empty_internal_modules("Internal modules cannot be empty.");

}

namespace dogen::identification::helpers {

entities::logical_name
logical_name_factory::build_model_name(const std::string& model_name,
    const std::string& external_modules) const {
    logical_name_builder b(true/*model_name_mode*/);
    b.model_name(model_name);
    b.external_modules(external_modules);
    return b.build();
}

entities::logical_name logical_name_factory::build_element_name(
    const std::string& simple_name) const {
    logical_name_builder b;
    b.simple_name(simple_name);
    return b.build();
}

entities::logical_name logical_name_factory::
build_element_name(const std::string& model_name,
    const std::string& simple_name) const {
    logical_name_builder b;
    b.simple_name(simple_name);
    b.model_name(model_name);

    return b.build();
}

entities::logical_name logical_name_factory::build_element_name(
    const std::string& simple_name,
    const std::list<std::string>& internal_modules) const {

    logical_name_builder b;
    b.simple_name(simple_name);
    b.internal_modules(internal_modules);

    return b.build();
}

entities::logical_name logical_name_factory::build_element_in_model(
    const entities::logical_name& model_name,
    const std::string& simple_name) const {

    logical_name_builder b;
    const auto& l(model_name.location());
    b.simple_name(simple_name);
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());

    return b.build();
}

entities::logical_name logical_name_factory::build_element_in_model(
    const entities::logical_name& model_name,
    const std::string& simple_name,
    const std::list<std::string>& internal_modules) const {

    logical_name_builder b;
    b.simple_name(simple_name);

    const auto& l(model_name.location());
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());
    b.internal_modules(internal_modules);

    return b.build();
}

entities::logical_name logical_name_factory::build_element_in_module(
    const entities::logical_name& module_name,
    const std::string& simple_name) const {
    logical_name_builder b;
    b.simple_name(simple_name);

    const auto& l(module_name.location());
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());

    auto pp(l.internal_modules());
    pp.push_back(module_name.simple());
    b.internal_modules(pp);

    return b.build();
}

entities::logical_name logical_name_factory::build_module_name(
    const entities::logical_name& model_name,
    const std::list<std::string>& internal_modules) const {

    if (internal_modules.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_internal_modules;
        BOOST_THROW_EXCEPTION(building_error(empty_internal_modules));
    }

    logical_name_builder b;
    b.simple_name(internal_modules.back());

    const auto& l(model_name.location());
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());

    auto ipp(internal_modules);
    ipp.pop_back();
    b.internal_modules(ipp);

    return b.build();
}

entities::logical_name logical_name_factory::build_module_name(
    const entities::logical_name& model_name,
    const std::string& module_name,
    const std::list<std::string>& internal_modules) const {

    logical_name_builder b;
    b.simple_name(module_name);

    const auto& l(model_name.location());
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());
    b.internal_modules(internal_modules);

    return b.build();
}

entities::logical_name logical_name_factory::build_combined_element_name(
    const entities::logical_name& model_name,
    const entities::logical_name& partial_element_name,
    const bool populate_model_modules_if_blank,
    const bool populate_internal_modules_if_blank,
    const bool combine_internal_modules) const {

    logical_name_builder b;
    b.simple_name(partial_element_name.simple());

    const auto& l(model_name.location());
    if (populate_model_modules_if_blank &&
        partial_element_name.location().model_modules().empty()) {
        b.model_modules(l.model_modules());
    } else
        b.model_modules(partial_element_name.location().model_modules());

    if (populate_internal_modules_if_blank &&
        partial_element_name.location().internal_modules().empty()) {
        b.internal_modules(l.internal_modules());
    } else if (combine_internal_modules) {
        auto im(model_name.location().internal_modules());
        for (const auto& m : partial_element_name.location().internal_modules())
            im.push_back(m);
        b.internal_modules(im);
    } else
        b.internal_modules(partial_element_name.location().internal_modules());

    b.external_modules(l.external_modules());

    return b.build();
}

entities::logical_name logical_name_factory::build_hacked_combined_element_name(
    const entities::logical_name& model_name,
    const entities::logical_name& partial_element_name) const {

    logical_name_builder b;
    b.simple_name(partial_element_name.simple());

    const auto& l(model_name.location());
    if (!l.model_modules().empty()) {
        /*
         * We start with all of the model modules of the model
         * name. Of these we discard the last one - the actual model
         * name.
         */
        auto mm(l.model_modules());
        mm.pop_back();
        if (mm.size() == 2)
            mm.pop_back();

        b.model_modules(mm);
    } else
        b.model_modules(partial_element_name.location().model_modules());

    b.internal_modules(partial_element_name.location().internal_modules());
    b.external_modules(l.external_modules());

    return b.build();
}

entities::logical_name logical_name_factory::
build_promoted_module_name(const entities::logical_name& element_name) const {
    logical_name_builder b;
    b.simple_name(element_name.simple());

    /*
     * We can only promote the internal module to model name if the
     * name does not have any internal modules already.
     */
    const auto& l(element_name.location());
    if (!l.internal_modules().empty()) {
        auto im(l.internal_modules());
        b.model_modules(im.front());
        im.pop_front();
        b.internal_modules(im);
    }

    return b.build();
}

entities::logical_name logical_name_factory::build_promoted_module_name(
    const entities::logical_name& model_name,
    const entities::logical_name& element_name) const {
    logical_name_builder b;
    b.simple_name(element_name.simple());

    const auto& l(element_name.location());
    if (!l.internal_modules().empty()) {
        auto im(l.internal_modules());
        b.model_modules(im.front());
        im.pop_front();
        b.internal_modules(im);
    }

    b.external_modules(model_name.location().external_modules());

    return b.build();
}

entities::logical_name logical_name_factory::build_attribute_name(
    const entities::logical_name& owner_name,
    const std::string& simple_name) const {

    logical_name_builder b;
    auto l(owner_name.location());
    l.element(owner_name.simple());

    b.location(l);
    b.simple_name(simple_name);

    return b.build();
}

boost::optional<entities::logical_name> logical_name_factory::
build_containing_element_name(const entities::logical_name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Creating containing element name for: "
                             << n.representations().dot();

    /*
     * First we determine if the element is placed in the global
     * namespace. If it is, we will deal with it (much) later on, in
     * the global module transform.
     */
    const bool in_global_namespace(n.location().model_modules().empty());
    if (in_global_namespace) {
        BOOST_LOG_SEV(lg, debug) << "Element is in global module so, it has"
                                 << " no containing module yet. Type: "
                                 << n.representations().dot();
        return boost::optional<entities::logical_name>();
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
                                 << n.representations().dot();
        return boost::optional<entities::logical_name>();
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
    helpers::logical_name_builder b;

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

}
