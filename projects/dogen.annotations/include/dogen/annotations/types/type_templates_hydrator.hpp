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
#ifndef DOGEN_ANNOTATIONS_TYPES_TYPE_TEMPLATES_HYDRATOR_HPP
#define DOGEN_ANNOTATIONS_TYPES_TYPE_TEMPLATES_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/annotations/types/name.hpp"
#include "dogen/annotations/types/value.hpp"
#include "dogen/annotations/types/value_types.hpp"
#include "dogen/annotations/types/template_kinds.hpp"
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/annotations/types/type_template.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Reads field definitions from a well-defined JSON
 * representation.
 */
class type_templates_hydrator {
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
    template_kinds to_template_kind(const std::string& s) const;

    /**
     * @brief Creates the field value.
     */
    boost::shared_ptr<value> create_value(const value_types vt,
        const std::string& v) const;

    /**
     * @brief Reads the annotation name from the property tree.
     */
    name read_name(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the ownership hierarchy from the property tree.
     */
    archetype_location
    read_archetype_location(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    std::list<type_template> read_stream(std::istream& s) const;

public:
    /**
     * @brief Hydrates the field definitions from the JSON stream.
     */
    std::list<type_template> hydrate(std::istream& s) const;

    /**
     * @brief Opens up the file at path and then hydrates the field
     * definitions from the JSON stream.
     */
    std::list<type_template> hydrate(const boost::filesystem::path& p) const;
};

} }

#endif
