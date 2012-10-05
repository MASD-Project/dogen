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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_GENERATOR_MODELING_DIA_TO_SML_HPP
#define DOGEN_GENERATOR_MODELING_DIA_TO_SML_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/dia/domain/diagram.hpp"
#include "dogen/sml/domain/package.hpp"
#include "dogen/sml/domain/pod.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/dia/domain/attribute.hpp"
#include "dogen/dia/domain/object.hpp"

namespace dogen {
namespace generator {
namespace modeling {

/**
 * @brief Transforms a Dia diagram from its object model into SML.
 */
class dia_to_sml {
public:
    dia_to_sml() = delete;
    dia_to_sml& operator=(const dia_to_sml&) = delete;
    dia_to_sml(const dia_to_sml&) = delete;
    dia_to_sml(dia_to_sml&&) = default;

public:
    /**
     * @brief Initialises the transformer
     *
     * @param diagram source of the transformation
     * @param model_name name of the model represented by the diagram
     * @param external_package_path external packages which contain the
     * model to generate
     * @param is_target true if this model is the code generation
     * target, false otherwise.
     * @param verbose output debugging information for troubleshooting
     */
    dia_to_sml(dia::diagram diagram, std::string model_name,
        std::string external_package_path, bool is_target, bool verbose);

private:
    /**
     * @brief Populates the graph with a directed acyclic graph of
     * dependencies between Dia objects.
     */
    void populate_graph(std::vector<dia::object> objects);

public:
    /**
     * @brief Execute the transformation from a Dia diagram into a SML model.
     */
    sml::model transform();

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

private:
    const dia::diagram diagram_;
    const std::string model_name_;
    const std::string external_package_path_;
    graph_type graph_;
    id_to_vertex_type id_to_vertex_;
    vertex_descriptor_type root_vertex_;
    const bool is_target_;
    const bool verbose_;
};

} } }

#endif
