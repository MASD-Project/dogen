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
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/attribute.hpp"
#include "dogen/yarn/types/meta_model/enumerator.hpp"
#include "dogen/yarn/types/meta_model/object_types.hpp"
#include "dogen/yarn/types/meta_model/exomodel.hpp"

namespace dogen {
namespace yarn {
namespace json {

/**
 * @brief Reads intermediate yarn models from a well-defined JSON
 * representation.
 */
class hydrator {
public:
    hydrator();

private:
    /**
     * @brief Converts a string to a value in the object types
     * enumeration.
     */
    meta_model::object_types
    to_object_type(const boost::optional<std::string>& s) const;

private:
    /**
     * @brief Reads the key value pairs from the property tree.
     */
    std::list<std::pair<std::string, std::string>>
    read_kvps(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the scribble group.
     */
    annotations::scribble_group read_scribble_group(
        const boost::property_tree::ptree& pt,
        const annotations::scope_types st) const;

    /**
     * @brief Read and inserts the scribble into the scribble group.
     */
    void read_and_insert_scribble(const meta_model::name& owner,
        const annotations::scope_types st,
        const boost::property_tree::ptree& pt,
        annotations::scribble_group& sg) const;

private:
    /**
     * @brief Read a name.
     */
    /**@{*/
    meta_model::name read_name(const boost::property_tree::ptree& pt) const;
    /**@}*/

    /**
     * @brief Reads a list of names.
     */
    std::list<meta_model::name>
    read_names(const boost::property_tree::ptree& pt) const;

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
    std::vector<meta_model::enumerator>
    read_enumerators(const boost::property_tree::ptree& pt,
        annotations::scribble_group& sg) const;

    /**
     * @brief Reads all attributes from the node.
     */
    std::list<meta_model::attribute>
    read_attributes(const boost::property_tree::ptree& pt,
        annotations::scribble_group& sg) const;

    /**
     * @brief Reads all properties at the element level and inserts
     * its scribbles.
     */
    void populate_element(const boost::property_tree::ptree& pt,
        meta_model::element& e) const;

private:
    /**
     * @brief Sets up the root module.
     */
    std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::module>>
    read_root_module(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads an object.
     */
    std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::object>>
    read_object(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads a builtin.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::builtin>>
    read_builtin(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads a module.
     */
    std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::module>>
    read_module(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads an enumeration.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::enumeration>>
    read_enumeration(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads a primitive.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::primitive>>
    read_primitive(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads an exception.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::exception>>
    read_exception(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads a concept.
     */
    std::pair<annotations::scribble_group,
              boost::shared_ptr<meta_model::concept>>
    read_concept(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads an element according to its meta-type by
     * dispatching to the correct read functions.
     */
    void read_element(const boost::property_tree::ptree& pt,
        meta_model::exomodel& em) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    meta_model::exomodel read_stream(std::istream& s) const;

public:
    /**
     * @brief Hydrates the model from the JSON stream.
     */
    meta_model::exomodel hydrate(std::istream& s) const;

    /**
     * @brief Opens up the file at path and then hydrates the model
     * from the JSON stream.
     */
    meta_model::exomodel
    hydrate(const boost::filesystem::path& p) const;

private:
    meta_model::name meta_name_object_;
    meta_model::name meta_name_builtin_;
    meta_model::name meta_name_module_;
    meta_model::name meta_name_enumeration_;
    meta_model::name meta_name_primitive_;
    meta_model::name meta_name_exception_;
    meta_model::name meta_name_concept_;
};

} } }

#endif
