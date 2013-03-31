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
#ifndef DOGEN_DIA_TO_SML_TYPES_OBJECT_TO_POD_HPP
#define DOGEN_DIA_TO_SML_TYPES_OBJECT_TO_POD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/dia/types/object.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/package.hpp"
#include "dogen/sml/types/pod.hpp"

namespace dogen {
namespace dia_to_sml {

class object_to_pod {
public:
    object_to_pod() = delete;
    object_to_pod(const object_to_pod&) = default;
    ~object_to_pod() = default;
    object_to_pod(object_to_pod&&) = default;
    object_to_pod& operator=(const object_to_pod&) = default;

public:
    object_to_pod(const std::string& model_name,
        const std::list<std::string>& external_package_path,
        bool is_target, bool verbose);

private:
    bool is_relationship_processable(const dia::object& o) const;
    void process_relationship(const dia::object& o);
    void setup_graph();

public:
    bool is_processable(const dia::object& o) const;
    void add_object(const dia::object& o);

    std::unordered_map<sml::qname, sml::pod>
    transform(std::unordered_map<std::string, sml::package> packages,
        std::unordered_set<std::string>& dependencies,
        std::unordered_set<dogen::sml::qname>& leaves);

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
    const std::string model_name_;
    const std::list<std::string> external_package_path_;
    graph_type graph_;
    id_to_vertex_type id_to_vertex_;
    vertex_descriptor_type root_vertex_;
    const bool is_target_;
    const bool verbose_;
    std::unordered_map<std::string, std::string> child_to_parent_dia_ids_;
    std::unordered_set<std::string> parent_dia_ids_;
    std::unordered_map<std::string, vertex_descriptor_type> orphans_;
    std::vector<dogen::dia::object> relationships_;
};

} }

#endif
