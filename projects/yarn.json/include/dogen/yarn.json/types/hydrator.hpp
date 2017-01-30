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
#ifndef DOGEN_YARN_JSON_TYPES_HYDRATOR_HPP
#define DOGEN_YARN_JSON_TYPES_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {
namespace json {

/**
 * @brief Reads intermediate yarn models from a well-defined JSON
 * representation.
 */
class hydrator {
public:
    hydrator() = default;
    hydrator(const hydrator&) = default;
    hydrator(hydrator&&) = default;
    ~hydrator() noexcept = default;

private:
    /**
     * @brief Reads the key value pairs from the property tree.
     */
    std::list<std::pair<std::string, std::string>>
    read_kvps(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Inserts the scribbles into the model's indicies.
     */
    void insert_scribbles(const yarn::name& owner,
        const annotations::scope_types scope,
        const std::list<std::pair<std::string, std::string>>& kvps,
        intermediate_model& im) const;

    /**
     * @brief Read a name.
     */
    /**@{*/
    name read_name(const boost::property_tree::ptree& pt) const;
    name read_name(const boost::property_tree::ptree& pt,
        const name& model_name, const bool in_global_module = false) const;
    /**@}*/

    /**
     * @brief Reads a list of names.
     */
    std::list<name> read_names(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the stereotypes.
     */
    std::vector<std::string>
    read_stereotypes(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the documentation.
     */
    std::string read_documentation(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads all enumerators from the node.
     */
    std::vector<enumerator>
    read_enumerators(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads all attributes from the node.
     */
    std::list<attribute>
    read_attributes(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads all properties at the element level and inserts
     * its scribbles.
     */
    void populate_element(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im, yarn::element& e) const;

    /**
     * @brief Reads an object.
     */
    void read_object(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads a builtin.
     */
    void read_builtin(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads a module.
     */
    void read_module(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads an enumeration.
     */
    void read_enumeration(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads a primitive.
     */
    void read_primitive(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads an exception.
     */
    void read_exception(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads a concept.
     */
    void read_concept(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads the meta-type and dispatches to the correct read
     * functions.
     */
    void dispatch_meta_type(const boost::property_tree::ptree& pt,
        yarn::intermediate_model& im) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    intermediate_model read_stream(std::istream& s, const bool is_target) const;

    /**
     * @brief Converts a string to a value in the object types
     * enumeration.
     */
    object_types
    to_object_type(const boost::optional<std::string>& s) const;

public:
    /**
     * @brief Hydrates the model from the JSON stream.
     */
    intermediate_model hydrate(std::istream& s, const bool is_target) const;

    /**
     * @brief Opens up the file at path and then hydrates the model
     * from the JSON stream.
     */
    intermediate_model
    hydrate(const boost::filesystem::path& p, const bool is_target) const;
};

} } }

#endif
