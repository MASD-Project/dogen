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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_NAME_FACTORY_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_LOGICAL_NAME_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/optional.hpp>
#include "dogen.identification/types/entities/logical_name.hpp"

namespace dogen::identification::helpers {

/**
 * @brief Creates logical names with all the fields filled in.
 */
class logical_name_factory final {
public:
    /*
     * @brief Given a string with a model name, possibly using a
     * separator, and a string with an external module path, also
     * possibly using a separator; parses both strings and generates a
     * combined name.
     *
     * @pre @e model_name must not be empty.
     */
    entities::logical_name build_model_name(const std::string& model_name,
        const std::string& external_modules = std::string()) const;

    /**
     * @brief Given the components of a name for an element, creates
     * the element name.
     */
    /**@{*/
    entities::logical_name
    build_element_name(const std::string& simple_name) const;
    entities::logical_name build_element_name(const std::string& model_name,
        const std::string& simple_name) const;
    entities::logical_name build_element_name(const std::string& simple_name,
        const std::list<std::string>& internal_modules) const;
    /**@}*/

    /**
     * @brief Given a simple name for an element and the name of the
     * model it is located in, creates the element name.
     */
    /**@{*/
    entities::logical_name
    build_element_in_model(const entities::logical_name& model_name,
        const std::string& simple_name) const;
    entities::logical_name
    build_element_in_model(const entities::logical_name& model_name,
        const std::string& simple_name,
        const std::list<std::string>& internal_modules) const;
    /**@}*/

    /**
     * @brief Given a simple name for an element and the name of the
     * module it is located in, creates the element name.
     */
    entities::logical_name build_element_in_module(
        const entities::logical_name& module_name,
        const std::string& simple_name) const;

    /**
     * @brief Builds a module name, given the model name and an
     * internal module path. Uses the back of the module path to name
     * the module.
     */
    /**@{*/
    entities::logical_name
    build_module_name(const entities::logical_name& model_name,
        const std::list<std::string>& internal_modules) const;
    entities::logical_name
    build_module_name(const entities::logical_name& model_name,
        const std::string& module_name,
        const std::list<std::string>& internal_modules) const;
    /**@}*/

    /**
     * @brief Combines element name with model name.
     */
    entities::logical_name build_combined_element_name(
        const entities::logical_name& model_name,
        const entities::logical_name& partial_element_name,
        const bool populate_model_modules_if_blank = false,
        const bool populate_internal_modules_if_blank = false,
        const bool combine_internal_modules = false) const;

    entities::logical_name build_hacked_combined_element_name(
        const entities::logical_name& model_name,
        const entities::logical_name& partial_element_name) const;

    /**
     * @brief Promotes the first name of the internal module path to
     * become the model name.
     */
    /**@{*/
    entities::logical_name build_promoted_module_name(
        const entities::logical_name& element_name) const;
    entities::logical_name build_promoted_module_name(
        const entities::logical_name& model_name,
        const entities::logical_name& element_name) const;
    /**@}*/

    /**
     * @brief Builds an attribute name.
     */
    entities::logical_name
    build_attribute_name(const entities::logical_name& owner_name,
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
    boost::optional<entities::logical_name>
    build_containing_element_name(const entities::logical_name& n) const;
};

}

#endif
