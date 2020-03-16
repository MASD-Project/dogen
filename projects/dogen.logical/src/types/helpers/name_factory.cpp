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
#include "dogen.logical/types/helpers/building_error.hpp"
#include "dogen.logical/types/helpers/name_builder.hpp"
#include "dogen.logical/types/helpers/name_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("assets.helpers.name_factory"));

const std::string empty_internal_modules("Internal modules cannot be empty.");

}

namespace dogen::logical::helpers {

meta_model::name name_factory::build_model_name(const std::string& model_name,
    const std::string& external_modules) const {
    name_builder b(true/*model_name_mode*/);
    b.model_name(model_name);
    b.external_modules(external_modules);
    return b.build();
}

meta_model::name name_factory::build_element_name(
    const std::string& simple_name) const {
    name_builder b;
    b.simple_name(simple_name);
    return b.build();
}

meta_model::name name_factory::build_element_name(const std::string& model_name,
    const std::string& simple_name) const {
    name_builder b;
    b.simple_name(simple_name);
    b.model_name(model_name);

    return b.build();
}

meta_model::name name_factory::build_element_name(
    const std::string& simple_name,
    const std::list<std::string>& internal_modules) const {

    name_builder b;
    b.simple_name(simple_name);
    b.internal_modules(internal_modules);

    return b.build();
}

meta_model::name name_factory::build_element_in_model(
    const meta_model::name& model_name,
    const std::string& simple_name) const {

    name_builder b;
    const auto& l(model_name.location());
    b.simple_name(simple_name);
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());

    return b.build();
}

meta_model::name name_factory::build_element_in_model(
    const meta_model::name& model_name,
    const std::string& simple_name,
    const std::list<std::string>& internal_modules) const {

    name_builder b;
    b.simple_name(simple_name);

    const auto& l(model_name.location());
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());
    b.internal_modules(internal_modules);

    return b.build();
}

meta_model::name name_factory::build_element_in_module(
    const meta_model::name& module_name,
    const std::string& simple_name) const {
    name_builder b;
    b.simple_name(simple_name);

    const auto& l(module_name.location());
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());

    auto pp(l.internal_modules());
    pp.push_back(module_name.simple());
    b.internal_modules(pp);

    return b.build();
}

meta_model::name name_factory::build_module_name(
    const meta_model::name& model_name,
    const std::list<std::string>& internal_modules) const {

    if (internal_modules.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_internal_modules;
        BOOST_THROW_EXCEPTION(building_error(empty_internal_modules));
    }

    name_builder b;
    b.simple_name(internal_modules.back());

    const auto& l(model_name.location());
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());

    auto ipp(internal_modules);
    ipp.pop_back();
    b.internal_modules(ipp);

    return b.build();
}

meta_model::name name_factory::build_module_name(
    const meta_model::name& model_name,
    const std::string& module_name,
    const std::list<std::string>& internal_modules) const {

    name_builder b;
    b.simple_name(module_name);

    const auto& l(model_name.location());
    b.model_modules(l.model_modules());
    b.external_modules(l.external_modules());
    b.internal_modules(internal_modules);

    return b.build();
}

meta_model::name name_factory::build_combined_element_name(
    const meta_model::name& model_name,
    const meta_model::name& partial_element_name,
    const bool populate_model_modules_if_blank,
    const bool populate_internal_modules_if_blank,
    const bool combine_internal_modules) const {

    name_builder b;
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
        for (const auto m : partial_element_name.location().internal_modules())
            im.push_back(m);
        b.internal_modules(im);
    } else
        b.internal_modules(partial_element_name.location().internal_modules());

    b.external_modules(l.external_modules());

    return b.build();
}

meta_model::name name_factory::build_hacked_combined_element_name(
    const meta_model::name& model_name,
    const meta_model::name& partial_element_name) const {

    name_builder b;
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

meta_model::name name_factory::
build_promoted_module_name(const meta_model::name& element_name) const {
    name_builder b;
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

meta_model::name name_factory::build_promoted_module_name(
    const meta_model::name& model_name,
    const meta_model::name& element_name) const {
    name_builder b;
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

meta_model::name name_factory::build_attribute_name(
    const meta_model::name& owner_name,
    const std::string& simple_name) const {

    name_builder b;
    auto l(owner_name.location());
    l.element(owner_name.simple());

    b.location(l);
    b.simple_name(simple_name);

    return b.build();
}

}
