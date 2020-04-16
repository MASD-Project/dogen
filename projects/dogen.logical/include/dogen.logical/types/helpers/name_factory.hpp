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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_NAME_FACTORY_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_NAME_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/name.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Creates names with all the fields filled in.
 */
class name_factory {
public:
    /*
     * @brief Given a string with a model name, possibly using a
     * separator, and a string with an external module path, also
     * possibly using a separator; parses both strings and generates a
     * combined name.
     *
     * @pre @e model_name must not be empty.
     */
    entities::name build_model_name(const std::string& model_name,
        const std::string& external_modules = std::string()) const;

    /**
     * @brief Given the components of a name for an element, creates
     * the element name.
     */
    /**@{*/
    entities::name build_element_name(const std::string& simple_name) const;
    entities::name build_element_name(const std::string& model_name,
        const std::string& simple_name) const;
    entities::name build_element_name(const std::string& simple_name,
        const std::list<std::string>& internal_modules) const;
    /**@}*/

    /**
     * @brief Given a simple name for an element and the name of the
     * model it is located in, creates the element name.
     */
    /**@{*/
    entities::name build_element_in_model(const entities::name& model_name,
        const std::string& simple_name) const;
    entities::name build_element_in_model(const entities::name& model_name,
        const std::string& simple_name,
        const std::list<std::string>& internal_modules) const;
    /**@}*/

    /**
     * @brief Given a simple name for an element and the name of the
     * module it is located in, creates the element name.
     */
    entities::name build_element_in_module(
        const entities::name& module_name,
        const std::string& simple_name) const;

    /**
     * @brief Builds a module name, given the model name and an
     * internal module path. Uses the back of the module path to name
     * the module.
     */
    /**@{*/
    entities::name build_module_name(const entities::name& model_name,
        const std::list<std::string>& internal_modules) const;
    entities::name build_module_name(const entities::name& model_name,
        const std::string& module_name,
        const std::list<std::string>& internal_modules) const;
    /**@}*/

    /**
     * @brief Combines element name with model name.
     */
    entities::name build_combined_element_name(
        const entities::name& model_name,
        const entities::name& partial_element_name,
        const bool populate_model_modules_if_blank = false,
        const bool populate_internal_modules_if_blank = false,
        const bool combine_internal_modules = false) const;

    entities::name build_hacked_combined_element_name(
        const entities::name& model_name,
        const entities::name& partial_element_name) const;

    /**
     * @brief Promotes the first name of the internal module path to
     * become the model name.
     */
    /**@{*/
    entities::name build_promoted_module_name(
        const entities::name& element_name) const;
    entities::name build_promoted_module_name(
        const entities::name& model_name,
        const entities::name& element_name) const;
    /**@}*/

    /**
     * @brief Builds an attribute name.
     */
    entities::name build_attribute_name(const entities::name& owner_name,
        const std::string& simple_name) const;

    /**
     * @brief Creates the name of the containing element, derived from
     * the element's name.
     *
     * A containing name is the name of an element that is able to
     * contain other elements. This is typically a module, but not
     * always.
     *
     * If the supplying name does not represent a valid containment,
     * returns null. At present there are two cases of "invalid"
     * containment: the global module and the model's module.
     */
    boost::optional<entities::name>
    build_containing_element_name(const entities::name& n) const;
};

}

#endif
