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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_JSON_HYDRATOR_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_JSON_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/dynamic/schema/types/name.hpp"
#include "dogen/dynamic/schema/types/value.hpp"
#include "dogen/dynamic/schema/types/value_types.hpp"
#include "dogen/dynamic/schema/types/field_definition_types.hpp"
#include "dogen/dynamic/schema/types/ownership_hierarchy.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

/**
 * @brief Reads field definitions from a well-defined JSON
 * representation.
 */
class json_hydrator {
private:
    /**
     * @brief Converts a string to a scope type.
     */
    scope_types to_scope_type(const std::string& s) const;

    /**
     * @brief Converts a string to a value type.
     */
    value_types to_value_type(const std::string& s) const;

    /**
     * @brief Converts a string to a field definition type.
     */
    field_definition_types to_field_definition_type(const std::string& s) const;

    /**
     * @brief Creates the field value.
     */
    boost::shared_ptr<value> create_value(const value_types vt,
        const std::string& v) const;

    /**
     * @brief Reads the dynamic name from the property tree.
     */
    name read_name(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the ownership hierarchy from the property tree.
     */
    ownership_hierarchy
    read_ownership_hierarchy(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    std::list<field_definition> read_stream(std::istream& s) const;

public:
    /**
     * @brief Hydrates the field definitions from the JSON stream.
     */
    std::list<field_definition> hydrate(std::istream& s) const;

    /**
     * @brief Opens up the file at path and then hydrates the field
     * definitions from the JSON stream.
     */
    std::list<field_definition> hydrate(const boost::filesystem::path& p) const;
};

} } }

#endif
