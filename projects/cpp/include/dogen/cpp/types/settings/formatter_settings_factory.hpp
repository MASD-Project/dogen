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

#include <list>
#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/cpp/types/settings/inclusion_delimiter_types.hpp"
#include "dogen/cpp/types/settings/formatter_settings.hpp"
#include "dogen/cpp/types/formatters/formatter_interface.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Produces the formatter settings for all formatters.
 */
class formatter_settings_factory {
public:
    explicit formatter_settings_factory(const dynamic::schema::repository& rp);

private:
    /**
     * @brief Converts string into an inclusion delimiter type.
     *
     * @pre v must be a valid delimiter type.
     */
    inclusion_delimiter_types
    inclusion_delimiter_type_from_string(const std::string& v) const;

private:
    /**
     * @brief All relevant properties we need to remember for each formatter.
     */
    struct formatter_properties {
        dynamic::schema::field_definition enabled;
        dynamic::schema::field_definition file_path;
        boost::optional<dynamic::schema::field_definition> inclusion_path;
        boost::optional<dynamic::schema::field_definition> inclusion_dependency;
        boost::optional<dynamic::schema::field_definition> integrated_facet;
    };

    /**
     * @brief Creates the set of formatter properties for a given
     * formatter.
     */
    formatter_properties make_formatter_properties(
        const dynamic::schema::repository& rp,
        const std::string& formatter_name) const;

    /**
     * @brief Generates all of the formatter properties, using the
     * repository data and the registered formatters.
     */
    std::unordered_map<std::string, formatter_properties>
    make_formatter_properties(const dynamic::schema::repository& rp) const;

private:
    /**
     * @brief Creates the formatter settings for a given formatter.
     */
    formatter_settings
    create_settings_for_formatter(
        const formatter_properties& fp, const dynamic::schema::object& o) const;

public:
    /**
     * @brief Produce the formatter settings.
     */
    std::unordered_map<std::string, formatter_settings>
    make(const dynamic::schema::object& o) const;

private:
    const std::unordered_map<std::string, formatter_properties>
    formatter_properties_;
};

} } }

#endif
