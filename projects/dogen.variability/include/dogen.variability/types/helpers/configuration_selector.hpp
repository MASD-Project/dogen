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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_SELECTOR_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include "dogen.variability/types/meta_model/value.hpp"
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"


namespace dogen::variability::helpers {

/**
 * @brief Performs a number of simple queries over the configuration
 * object.
 */
class configuration_selector final {
public:
    explicit configuration_selector(const meta_model::configuration& c);

private:
    /**
     * @brief Throws if the feature has no default value.
     */
    void ensure_default_value(const meta_model::feature& f) const;

public:
    /**
     * @brief Returns true if a configuration point exists in the
     * configuration for the supplied qualified name or feature.
     */
    /**@{*/
    bool has_configuration_point(const std::string& qn) const;
    bool has_configuration_point(const meta_model::feature& f) const;
    /**@}*/

    /**
     * @brief Returns true if at least one configuration point name
     * ends with @code s.
     */
    bool has_configuration_point_ending_with(const std::string& s) const;

private:
    /**
     * @brief Returns a value of a configuration point from a
     * configuration for the supplied qualified name or feature.
     *
     * @pre @e has_configuration_point must be true.
     */
    /**@{*/
    const meta_model::value&
    get_configuration_point_value(const std::string& qn) const;
    const meta_model::value&
    get_configuration_point_value(const meta_model::feature& f) const;
    /**@}*/

public:
    /**
     * @brief Returns the content of the supplied value as text.
     *
     * @pre @v must be of text type.
     */
    static std::string get_text_content(const meta_model::value& v);

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied qualified name or feature, and returns the contents of
     * its value as text.
     *
     * @pre @e has_configuration_point must be true.
     * @pre Configuration point for qualified name or feature must
     * exist.
     * @pre The type of its value must be text.
     */
    /**@{*/
    std::string get_text_content(const std::string& qn) const;
    std::string get_text_content(const meta_model::feature& f) const;
    /**@}*/

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied feature, and returns either the contents of its value
     * as text, or, if no configuration point exists, the default
     * value for the feature.
     *
     * @pre feature must have a default value.
     * @pre default value must be of type text.
     */
    std::string get_text_content_or_default(const meta_model::feature& f) const;

public:
    /**
     * @brief Returns the content of the supplied value as a text
     * collection.
     *
     * @pre @v must be of text collection type.
     */
    static std::list<std::string>
    get_text_collection_content(const meta_model::value& v);

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied qualified name or feature, and returns the contents of
     * its value as a text collection.
     *
     * @pre has_configuration_point must be true.
     * @pre Configuration point for qualified name or feature must
     * exist.
     * @pre The type of its value must be text collection.
     */
    /**@{*/
    std::list<std::string>
    get_text_collection_content(const std::string& qn) const;
    std::list<std::string>
    get_text_collection_content(const meta_model::feature& f) const;
    /**@}*/

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied feature, and returns either the contents of its value
     * as text collection, or, if no configuration point exists, the
     * default value for the feature.
     *
     * @pre feature must have a default value.
     * @pre default value must be of type text collection.
     */
    std::list<std::string>
    get_text_collection_content_or_default(const meta_model::feature& f) const;

public:
    /**
     * @brief Returns the content of the supplied value as boolean.
     *
     * @pre @v must be of boolean type.
     */
    static bool get_boolean_content(const meta_model::value& v);

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied qualified name or feature, and returns the contents of
     * its value as a boolean.
     *
     * @pre has_configuration_point must be true.
     * @pre Configuration point for qualified name or feature must
     * exist.
     * @pre The type of its value must be boolean.
     */
    /**@{*/
    bool get_boolean_content(const std::string& qn) const;
    bool get_boolean_content(const meta_model::feature& f) const;
    /**@}*/

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied feature, and returns either the contents of its value
     * as boolean, or, if no configuration point exists, the default
     * value for the feature.
     *
     * @pre feature must have a default value.
     * @pre default value must be of type boolean.
     */
    bool get_boolean_content_or_default(const meta_model::feature& f) const;

public:
    /**
     * @brief Returns the content of the supplied value as number.
     *
     * @pre @v must have a type of number.
     */
    static int get_number_content(const meta_model::value& v);

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied qualified name or feature, and returns the contents of
     * its value as a number.
     *
     * @pre has_configuration_point must be true.
     * @pre Configuration point for qualified name or feature must
     * exist.
     * @pre The type of its value must be number.
     */
    /**@{*/
    int get_number_content(const std::string& qn) const;
    int get_number_content(const meta_model::feature& f) const;
    /**@}*/

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied feature, and returns either the contents of its value
     * as number, or, if no configuration point exists, the default
     * value for the feature.
     *
     * @pre feature must have a default value.
     * @pre default value must be of type number.
     */
    int get_number_content_or_default(const meta_model::feature& f) const;

public:
    /**
     * @brief Returns the content of the supplied value as a
     * key/value pair.
     *
     * @pre @v must have a type of key/value pair.
     */
    static const std::list<std::pair<std::string, std::string>>&
    get_key_value_pair_content(const meta_model::value& v);

    /**
     * @brief Retrieves the configuration point associated with the
     * supplied qualified name or feature, and returns the contents of
     * its value as a key/value pair.
     *
     * @pre has_configuration_point must be true.
     * @pre Configuration point for qualified name or feature must
     * exist.
     * @pre The type of its value must be key/value pair.
     */
    /**@{*/
    const std::list<std::pair<std::string, std::string>>&
    get_key_value_pair_content(const std::string& qn) const;
    const std::list<std::pair<std::string, std::string>>&
    get_key_value_pair_content(const meta_model::feature& f) const;
    /**@}*/

private:
    const meta_model::configuration& configuration_;
};

}

#endif
