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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_TRANSFORMERS_SML_TO_CPP_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_TRANSFORMERS_SML_TO_CPP_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/generator/backends/cpp/cpp_location_manager.hpp"
#include "dogen/generator/backends/cpp/cpp_dependency_manager.hpp"
#include "dogen/generator/backends/cpp/cpp_aspect_types.hpp"
#include "dogen/generator/backends/cpp/cpp_file_types.hpp"
#include "dogen/generator/backends/cpp/cpp_facet_types.hpp"
#include "dogen/sml/domain/package.hpp"
#include "dogen/sml/domain/pod.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/generator/backends/cpp/view_models/file_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace transformers {

/**
 * @brief Transformer responsible for converting an SML model instance
 * into the corresponding C++ view model.
 */
class sml_to_cpp_view_model {
public:
    sml_to_cpp_view_model() = delete;
    sml_to_cpp_view_model(const sml_to_cpp_view_model&) = delete;
    ~sml_to_cpp_view_model() = default;
    sml_to_cpp_view_model(sml_to_cpp_view_model&&) = delete;
    sml_to_cpp_view_model& operator=(const sml_to_cpp_view_model&) = delete;

public:
    sml_to_cpp_view_model(const cpp_location_manager& location_manager,
        const std::set<cpp_facet_types>& facet_types,
        const sml::model& model, bool disable_facet_includers,
        bool disable_keys, bool use_integrated_io,
        bool disable_io);

private:
    void log_started() const;
    void log_finished(unsigned int count) const;
    void log_keys() const;
    void log_includers() const;
    void log_generating_file(cpp_facet_types facet, cpp_aspect_types aspect,
        cpp_file_types file, std::string name) const;

private:
    /**
     * @brief Returns true if the facet requires a C++ source file,
     * false otherwise.
     */
    bool has_implementation(cpp_facet_types facet_type) const;

    /**
     * @brief Transforms a relative path to a header file into a C++
     * header guard name.
     */
    std::string
    to_header_guard_name(const boost::filesystem::path& relative_path) const;

    cpp_location_request location_request_factory(cpp_facet_types facet_type,
        cpp_file_types file_type, sml::qualified_name name) const;

    /**
     * @brief Generate a class view model for a given key type.
     *
     * @param is_versioned if true, generates the versioned key view
     * model, if false the unversioned key.
     */
    view_models::class_view_model
    create_key_class_view_model(bool is_versioned) const;

    /**
     * @brief Generate a file view model for a given key type.
     *
     * @param is_versioned if true, generates the versioned key view
     * model, if false the unversioned key.
     */
    view_models::file_view_model
    create_key_file_view_model(cpp_facet_types facet_type,
        cpp_file_types file_type, cpp_aspect_types aspect_type);

private:
    /**
     * @brief Transforms a SML pod into a C++ file view.
     */
    view_models::file_view_model
    transform_file(cpp_facet_types facet_type, cpp_file_types file_type,
        const sml::pod& pod);

    /**
     * @brief Transforms all versioned and unversioned keys.
     */
    std::vector<view_models::file_view_model> transform_keys();

    /**
     * @brief Transforms all facet includers
     */
    std::vector<view_models::file_view_model> transform_facet_includers() const;

    /**
     * @brief Transforms all pods
     */
    std::vector<view_models::file_view_model> transform_pods();

public:
    /**
     * @brief Transforms the SML model instance into the corresponding
     * C++ view model.
     */
    std::vector<view_models::file_view_model> transform();

private:
    // graph of dependencies
    typedef boost::adjacency_list<
    boost::vecS, // outer edge list type
    boost::vecS, // vertex list type
    boost::directedS, // directed graph
    sml::pod> graph_type;

    // type of the vertices
    typedef boost::graph_traits<graph_type>::vertex_descriptor
    vertex_descriptor_type;

    // map of qname to vertex
    typedef std::unordered_map<sml::qualified_name, vertex_descriptor_type>
    qname_to_vertex_type;

private:
    const cpp_location_manager location_manager_;
    const std::set<cpp_facet_types> facet_types_;
    const sml::model model_;
    const bool disable_facet_includers_;
    const bool disable_keys_;
    cpp_dependency_manager dependency_manager_;
    std::unordered_map<sml::qualified_name, view_models::class_view_model>
    qname_to_class_;
    graph_type graph_;
    qname_to_vertex_type qname_to_vertex_;
    vertex_descriptor_type root_vertex_;
};

} } } } }

#endif
