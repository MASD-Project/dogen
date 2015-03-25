/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_FIELD_SELECTOR_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_FIELD_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/dynamic/schema/types/field_instance.hpp"
#include "dogen/dynamic/schema/types/object.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

/**
 * @brief Performs a number of simple queries over a dynamic object.
 */
class field_selector {
public:
    explicit field_selector(const object& o);

public:
    /**
     * @brief Returns true if a field exists in an object.
     */
    /**@{*/
    bool has_field(const std::string& qualified_field_name) const;
    bool has_field(const field_definition& fd) const;
    /**@}*/

    /**
     * @brief Returns a field from an object.
     *
     * @pre has_field must be true.
     */
    /**@{*/
    const field_instance&
    get_field(const std::string& qualified_field_name) const;
    const field_instance& get_field(const field_definition& fd) const;
    /**@}*/

public:
    /**
     * @brief Returns the content for the field, assuming it is a text field.
     *
     * @pre Field value type must be text.
     */
    static std::string get_text_content(const value& v);

    /**
     * @brief Returns the content for the field, assuming it is a text field.
     *
     * @pre has_field must be true.
     * @pre Field value type must be text.
     */
    /**@{*/
    std::string get_text_content(const std::string& qualified_field_name) const;
    std::string get_text_content(const field_definition& fd) const;
    /**@}*/

    /**
     * @brief Returns the content for the field, assuming it is a text
     * field.
     *
     * If the field does not exist, returns the default value.
     *
     * @pre field definition must have a default value.
     */
    std::string get_text_content_or_default(const field_definition& fd) const;

    /**
     * @brief Returns the content for the field, assuming it is a text
     * collection field.
     *
     * @pre Field value type must be text collection.
     */
    static std::list<std::string> get_text_collection_content(const value& v);

    /**
     * @brief Returns the content for the field, assuming it is a text
     * collection field.
     *
     * @pre has_field must be true.
     * @pre Field value type must be text collection.
     */
    /**@{*/
    std::list<std::string>
    get_text_collection_content(const std::string& qualified_field_name) const;
    std::list<std::string>
    get_text_collection_content(const field_definition& fd) const;
    /**@}*/

    /**
     * @brief Returns the content for the field, assuming it is a text
     * collection field.
     *
     * If the field does not exist, returns the default value.
     *
     * @pre field definition must have a default value.
     */
    std::list<std::string>
    get_text_collection_content_or_default(const field_definition& fd) const;

    /**
     * @brief Returns the content for the field, assuming it is a boolean
     * field.
     *
     * @pre Field value type must be boolean.
     */
    static bool get_boolean_content(const value& v);

    /**
     * @brief Returns the content for the field, assuming it is a boolean
     * field.
     *
     * @pre has_field must be true.
     * @pre Field value type must be boolean.
     */
    /**@{*/
    bool get_boolean_content(const std::string& qualified_field_name) const;
    bool get_boolean_content(const field_definition& fd) const;
    /**@}*/

    /**
     * @brief Returns the content for the field, assuming it is a boolean
     * field.
     *
     * If the field does not exist, returns the default value.
     *
     * @pre field definition must have a default value.
     */
    bool get_boolean_content_or_default(const field_definition& fd) const;


private:
    const object& object_;
};

} } }

#endif
