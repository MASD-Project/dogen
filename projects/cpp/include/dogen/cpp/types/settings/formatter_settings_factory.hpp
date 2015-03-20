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
#ifndef DOGEN_CPP_TYPES_SETTINGS_FORMATTER_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_FORMATTER_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/cpp/types/settings/formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Produces the formatter settings for all formatters.
 */
class formatter_settings_factory {
public:
    /**
     * @brief Initialise the factory.
     *
     * @param field_definitions_by_formatter_name all available field
     * definitions for formatters, organised by formatter name.
     */
    explicit formatter_settings_factory(
        const std::unordered_map<
            std::string, std::forward_list<dynamic::schema::field_definition>
            >& field_definitions_by_formatter_name
        );

private:
    /**
     * @brief If the field has not been found, throws.
     */
    void ensure_field_is_present(
        const bool found, const std::string& name) const;

    /**
     * @brief Creates the formatter settings for a given formatter.
     */
    formatter_settings
    create_settings_for_formatter(
        const std::forward_list<dynamic::schema::field_definition>&
        formatter_fields, const dynamic::schema::object& o) const;

public:
    /**
     * @brief Produce the formatter settings.
     */
    std::unordered_map<std::string, formatter_settings>
    make(const dynamic::schema::object& o) const;

private:
    const std::unordered_map<
    std::string, std::forward_list<dynamic::schema::field_definition>
    >& field_definitions_by_formatter_name_;
};

} } }

#endif
