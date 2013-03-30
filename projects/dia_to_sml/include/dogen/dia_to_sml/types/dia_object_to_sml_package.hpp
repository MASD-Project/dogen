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
#ifndef DOGEN_DIA_TO_SML_TYPES_DIA_OBJECT_TO_SML_PACKAGE_HPP
#define DOGEN_DIA_TO_SML_TYPES_DIA_OBJECT_TO_SML_PACKAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/dia/types/object.hpp"
#include "dogen/sml/types/package.hpp"

namespace dogen {
namespace dia_to_sml {

class dia_object_to_sml_package {
public:
    dia_object_to_sml_package() = default;
    dia_object_to_sml_package(const dia_object_to_sml_package&) = default;
    ~dia_object_to_sml_package() = default;
    dia_object_to_sml_package(dia_object_to_sml_package&&) = default;
    dia_object_to_sml_package& operator=(const dia_object_to_sml_package&) = default;

public:
    /**
     * @brief Initialises the transformer
     *
     * @param model_name name of the model represented by the diagram
     * @param external_package_path external packages which contain the
     * model to generate
     * @param verbose output debugging information for troubleshooting
     */
    dia_object_to_sml_package(const std::string& model_name,
        const std::list<std::string>& external_package_path, bool verbose);

public:
    /**
     * @brief Returns true if the dia object represents an object we
     * can process, false otherwise.
     */
    bool is_processable(const dia::object& o) const;

    /**
     * @brief Add object to transformer.
     *
     * @pre is_uml_package must be true for object
     */
    void add_object(const dia::object& o);

public:
    /**
     * @brief Transforms all the added dia objects into SML packages.
     *
     * Key of the map is the dia object ID.
     */
    std::unordered_map<std::string, sml::package> transform();

private:
    // graph of dependencies
    typedef boost::adjacency_list<
    boost::vecS, // outer edge list type
    boost::vecS, // vertex list type
    boost::directedS, // directed graph
    dia::object> graph_type;

    // type of the vertices
    typedef boost::graph_traits<graph_type>::vertex_descriptor
    vertex_descriptor_type;

    // map of Dia object ID to vertex
    typedef std::unordered_map<std::string, vertex_descriptor_type>
    id_to_vertex_type;

    const std::string model_name_;
    const std::list<std::string> external_package_path_;
    graph_type graph_;
    id_to_vertex_type id_to_vertex_;
    vertex_descriptor_type root_vertex_;
    const bool verbose_;
};

} }

#endif
