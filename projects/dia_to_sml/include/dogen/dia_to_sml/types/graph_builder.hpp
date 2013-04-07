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
#ifndef DOGEN_DIA_TO_SML_TYPES_GRAPH_BUILDER_HPP
#define DOGEN_DIA_TO_SML_TYPES_GRAPH_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/dia/types/object.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Graph of dependencies between dia objects.
 */
typedef boost::adjacency_list<
    boost::setS, boost::vecS, boost::directedS, dia::object
    > graph_type;

/**
 * @brief Builds a DAG of dia objects.
 */
class graph_builder {
private:
    typedef boost::graph_traits<graph_type>::vertex_descriptor
    vertex_descriptor_type;

    typedef std::unordered_map<std::string, vertex_descriptor_type>
    id_to_vertex_type;

public:
    graph_builder();

private:
    /**
     * @brief Given a dia object ID, return its associated vertex.
     *
     * If the vertex does not yet exist, creates it.
     *
     * @param id Object ID.
     */
    vertex_descriptor_type vertex_for_id(const std::string& id);

    /**
     * @brief Ensures the graph has not yet been built.
     */
    void ensure_not_built() const;

    /**
     * @brief Returns true if the object is relevant to the object
     * graph, false otherwise.
     */
    bool is_relevant(const dia::object& o) const;

public: // only for testing purposes
    static std::string root_id();

public:
    /**
     * @brief Adds an object to the graph.
     *
     * @pre The graph must not yet have been built.
     */
    void add(const dia::object& o);

    /**
     * @brief Generate a DAG of all objects that have been added.
     */
    const graph_type& build();

private:
    bool built_;
    graph_type graph_;
    id_to_vertex_type id_to_vertex_;
    vertex_descriptor_type root_vertex_;
};

} }

#endif
