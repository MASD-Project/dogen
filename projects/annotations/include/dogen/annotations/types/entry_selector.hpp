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
#ifndef DOGEN_ANNOTATIONS_TYPES_ENTRY_SELECTOR_HPP
#define DOGEN_ANNOTATIONS_TYPES_ENTRY_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/value.hpp"
#include "dogen/annotations/types/annotation.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Performs a number of simple queries over the annotations
 * object.
 */
class entry_selector {
public:
    explicit entry_selector(const annotation& a);

private:
    /**
     * @brief Throws if the type has no default value.
     */
    void ensure_default_value(const type& t) const;

public:
    /**
     * @brief Returns true if an entry exists in the annotation for
     * the supplied entry type.
     */
    /**@{*/
    bool has_entry(const std::string& qualified_name) const;
    bool has_entry(const type& t) const;
    /**@}*/

    /**
     * @brief Returns true if at least one entry ends with @code s.
     */
    bool has_key_ending_with(const std::string& s) const;

private:
    /**
     * @brief Returns a value of an entry from an annotation.
     *
     * @pre has_entry must be true.
     */
    /**@{*/
    const value&
    get_entry_value(const std::string& qualified_name) const;
    const value& get_entry_value(const type& t) const;
    /**@}*/

public:
    /**
     * @brief Returns the value of the entry, assuming it is a text
     * value.
     *
     * @pre Entry value type must be text.
     */
    static std::string get_text_content(const value& v);

    /**
     * @brief Returns the value of the entry, assuming it is a text value.
     *
     * @pre has_entry must be true.
     * @pre Entry value type must be text.
     */
    /**@{*/
    std::string get_text_content(const std::string& qualified_name) const;
    std::string get_text_content(const type& t) const;
    /**@}*/

    /**
     * @brief Returns the value of the entry, assuming it is a text
     * value.
     *
     * If the entry type does not exist, returns its default value.
     *
     * @pre entry type must have a default value.
     */
    std::string get_text_content_or_default(const type& t) const;

public:
    /**
     * @brief Returns the value of the entry, assuming it is a text
     * collection value.
     *
     * @pre Entry type must be text collection.
     */
    static std::list<std::string> get_text_collection_content(const value& v);

    /**
     * @brief Returns the value of the entry, assuming it is a text
     * collection value.
     *
     * @pre has_entry must be true.
     * @pre Type's value must be text collection.
     */
    /**@{*/
    std::list<std::string>
    get_text_collection_content(const std::string& qualified_name) const;
    std::list<std::string>
    get_text_collection_content(const type& t) const;
    /**@}*/

    /**
     * @brief Returns the value of the entry, assuming it is a text
     * collection value.
     *
     * If the entry does not exist, returns the default value.
     *
     * @pre type must have a default value.
     */
    std::list<std::string>
    get_text_collection_content_or_default(const type& t) const;

public:
    /**
     * @brief Returns the content for the entry, assuming it is a
     * boolean value.
     *
     * @pre Entry's  value must be boolean.
     */
    static bool get_boolean_content(const value& v);

    /**
     * @brief Returns the value of the entry, assuming it is a boolean
     * value.
     *
     * @pre has_entry must be true.
     * @pre Type's value must be boolean.
     */
    /**@{*/
    bool get_boolean_content(const std::string& qualified_name) const;
    bool get_boolean_content(const type& t) const;
    /**@}*/

    /**
     * @brief Returns the value of the entry, assuming it is a boolean
     * value.
     *
     * If the entry does not exist, returns the default value.
     *
     * @pre Type must have a default value.
     */
    bool get_boolean_content_or_default(const type& t) const;

public:
    /**
     * @brief Returns the value of the entry, assuming it is a numeric
     * value.
     *
     * @pre Type's value must be numeric.
     */
    static int get_number_content(const value& v);

    /**
     * @brief Returns the value of the entry, assuming it is a numeric
     * value.
     *
     * @pre has_entry must be true.
     * @pre Type must be numeric.
     */
    /**@{*/
    int get_number_content(const std::string& qualified_name) const;
    int get_number_content(const type& t) const;
    /**@}*/

    /**
     * @brief Returns the value of the entry, assuming it is a numeric
     * value.
     *
     * If the entry does not exist, returns the default value.
     *
     * @pre Type must have a default value.
     */
    int get_number_content_or_default(const type& t) const;

public:
    /**
     * @brief Returns the value of the entry, assuming it is a kvp.
     *
     * @pre Type's value must be kvp.
     */
    static std::unordered_map<std::string, std::string>
    get_kvp_content(const value& v);

    /**
     * @brief Returns the value of the entry, assuming it is a kvp.
     *
     * @pre has_entry must be true.
     * @pre Type's value must be key-value-pair.
     */
    /**@{*/
    std::unordered_map<std::string, std::string>
    get_kvp_content(const std::string& qualified_name) const;
    std::unordered_map<std::string, std::string>
    get_kvp_content(const type& t) const;
    /**@}*/

private:
    const annotation& annotation_;
};

} }

#endif
