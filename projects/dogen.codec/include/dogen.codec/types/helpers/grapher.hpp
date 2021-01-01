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
#ifndef DOGEN_CODEC_TYPES_HELPERS_GRAPHER_HPP
#define DOGEN_CODEC_TYPES_HELPERS_GRAPHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>
#include "dogen.codec/types/entities/object.hpp"

namespace dogen::codec::helpers {

/**
 * @brief Graph of dependencies between objects.
 */
typedef boost::adjacency_list<
    boost::setS, boost::vecS, boost::directedS, entities::object
    > graph_type;

/**
 * @brief Generates a DAG of  objects.
 */
class grapher {
private:
    typedef boost::graph_traits<graph_type>::vertex_descriptor
    vertex_descriptor_type;

    typedef std::unordered_map<std::string, vertex_descriptor_type>
    id_to_vertex_type;

public:
    grapher();

private:
    /**
     * @brief Given an object ID, return its associated vertex.
     *
     * If the vertex does not yet exist, creates it.
     *
     * @param id Object ID.
     */
    vertex_descriptor_type vertex_for_id(const std::string& id);

    /**
     * @brief Ensures the graph has not yet been generated.
     */
    void require_not_generated() const;

    /**
     * @brief Ensures the graph has been generated.
     */
    void require_generated() const;

    /**
     * @brief Handle relationships derived from child node.
     */
    void process_child_node(const vertex_descriptor_type& v,
        const entities::object& po);

    /**
     * @brief Handle relationships derived from connections.
     */
    void process_connections(const entities::object& po);

public:
    /**
     * @brief Returns the dia object ID of the root object.
     *
     * @note only for testing purposes
     */
    static std::string root_id();

public:
    /**
     * @brief Adds an object to the graph.
     *
     * @pre The graph must not yet have been generated.
     * @pre The object must be relevant to the graph.
     */
    void add(const entities::object& o);

    /**
     * @brief Adds a container of objects to the graph.
     *
     * @pre The graph must not yet have been generated.
     *
     * @note Couldn't find a way to constrain the container to
     * non-associative containers of object. On the plus side, if you
     * try to pass in some weird container (or a non-container), you
     * should get a suitably puzzling error message.
     */
    template<typename Container>
    void add(const Container& c) {
        for (const auto& o : c)
            add(o);
    }

    /**
     * @brief Returns true if the graph has been generated, false
     * otherwise.
     */
    bool is_generated() const { return generated_; }

    /**
     * @brief Generate a DAG of all objects that have been added.
     *
     * @pre Graph must not yet have been generated.
     */
    /**@{*/
    void generate();

    template<typename Container>
    void generate(const Container& c) {
        add(c);
        generate();
    }
    /**@}*/

public:
    /**
     * @brief Returns the generated graph.
     *
     * @pre The graph must have already been generated.
     */
    const graph_type& graph() const;

    /**
     * @brief Returns the parent to child relationships.
     *
     * @pre The graph must have already been generated.
     */
    const std::unordered_map<std::string, std::list<std::string>>&
    parent_id_to_child_ids() const;

private:
    bool generated_;
    graph_type graph_;
    id_to_vertex_type id_to_vertex_;
    id_to_vertex_type orphanage_;
    vertex_descriptor_type root_vertex_;
    std::unordered_map<std::string, std::list<std::string>>
    parent_id_to_child_ids_;
    std::unordered_set<std::string> connected_ids_;
};

}

#endif
