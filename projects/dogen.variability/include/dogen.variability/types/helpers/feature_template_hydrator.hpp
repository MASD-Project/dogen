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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_FEATURE_TEMPLATE_HYDRATOR_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_FEATURE_TEMPLATE_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen.archetypes/types/location.hpp"
#include "dogen.variability/types/meta_model/name.hpp"
#include "dogen.variability/types/meta_model/value.hpp"
#include "dogen.variability/types/meta_model/value_type.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.variability/types/meta_model/binding_point.hpp"
#include "dogen.variability/types/meta_model/feature_template.hpp"

namespace dogen::variability::helpers {

/**
 * @brief Reads field definitions from a well-defined JSON
 * representation.
 */
class feature_template_hydrator final {
private:
    /**
     * @brief Converts a string to a scope type.
     */
    meta_model::binding_point to_binding_point(const std::string& s) const;

    /**
     * @brief Converts a string to a value type.
     */
    meta_model::value_type to_value_type(const std::string& s) const;

    /**
     * @brief Converts a string to a field definition type.
     */
    meta_model::template_kind to_template_kind(const std::string& s) const;

    /**
     * @brief Creates the field value.
     */
    boost::shared_ptr<meta_model::value>
    create_value(const meta_model::value_type vt, const std::string& v) const;

    /**
     * @brief Reads the annotation name from the property tree.
     */
    meta_model::name read_name(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the ownership hierarchy from the property tree.
     */
    archetypes::location
    read_archetype_location(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    std::list<meta_model::feature_template> read_stream(std::istream& s) const;

public:
    /**
     * @brief Hydrates the field definitions from the JSON stream.
     */
    std::list<meta_model::feature_template> hydrate(std::istream& s) const;

    /**
     * @brief Opens up the file at path and then hydrates the field
     * definitions from the JSON stream.
     */
    std::list<meta_model::feature_template>
    hydrate(const boost::filesystem::path& p) const;
};

}

#endif
