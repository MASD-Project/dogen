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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_SML_TO_CPP_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_SML_TO_CPP_VIEW_MODEL_HPP

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
#include "dogen/generator/config/cpp_settings.hpp"
#include "dogen/generator/backends/cpp/cpp_location_manager.hpp"
#include "dogen/generator/backends/cpp/cpp_inclusion_manager.hpp"
#include "dogen/generator/backends/cpp/cpp_aspect_types.hpp"
#include "dogen/generator/backends/cpp/cpp_file_types.hpp"
#include "dogen/generator/backends/cpp/cpp_facet_types.hpp"
#include "dogen/sml/domain/meta_types.hpp"
#include "dogen/sml/domain/package.hpp"
#include "dogen/sml/domain/pod.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/generator/backends/cpp/view_models/file_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

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
        const cpp_inclusion_manager& inclusion_manager,
        const config::cpp_settings& settings,
        const sml::model& model);

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
    bool has_implementation(const cpp_facet_types ft,
        const dogen::sml::meta_types mt) const;

    /**
     * @brief Returns true if facet has forward declarations, false otherwise.
     */
    bool has_forward_decls(const cpp_facet_types ft,
        const dogen::sml::meta_types mt) const;

    /**
     * @brief Transforms a relative path to a header file into a C++
     * header guard name.
     */
    std::string
    to_header_guard_name(const boost::filesystem::path& relative_path) const;

    cpp_location_request location_request_factory(cpp_facet_types ft,
        cpp_file_types flt, cpp_aspect_types at,
        const sml::qualified_name& n) const;

    /**
     * @brief Generate a class view model for a given key type.
     *
     * @param is_versioned if true, generates the versioned key view
     * model, if false the unversioned key.
     */
    class_view_model create_key_class_view_model(bool is_versioned) const;

    /**
     * @brief Generate a file view model for a given key type.
     *
     * @param is_versioned if true, generates the versioned key view
     * model, if false the unversioned key.
     */
    file_view_model create_key_file_view_model(cpp_facet_types facet_type,
        cpp_file_types file_type, cpp_aspect_types aspect_type);

private:
    /**
     * @brief Performs the initial setup of the file view model.
     */
    file_view_model create_file(cpp_facet_types ft, cpp_file_types flt,
        cpp_aspect_types at, const sml::qualified_name& name);

    /**
     * @brief Transforms a SML pod into a C++ file view.
     */
    file_view_model transform_file(cpp_facet_types ft, cpp_file_types flt,
        cpp_aspect_types at, const sml::pod& p);

    /**
     * @brief Transforms a SML enumeration into a C++ file view.
     */
    file_view_model
    transform_file(cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at,
        const sml::enumeration& e);

    /**
     * @brief Transforms all versioned and unversioned keys.
     */
    std::vector<file_view_model> transform_keys();

    /**
     * @brief Transforms all facet includers
     */
    std::vector<file_view_model> transform_facet_includers() const;

    /**
     * @brief Creates all the class view models
     */
    void create_class_view_models();

    /**
     * @brief Creates all the enumeration view models
     */
    void create_enumeration_view_models();

    /**
     * @brief Transforms pods into file view models.
     */
    std::vector<file_view_model> transform_pods();

    /**
     * @brief Transforms enumerations into view models.
     */
    std::vector<file_view_model> transform_enumerations();

public:
    /**
     * @brief Transforms the SML model instance into the corresponding
     * C++ view model.
     */
    std::vector<file_view_model> transform();

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
    cpp_inclusion_manager inclusion_manager_;
    const config::cpp_settings settings_;
    const sml::model model_;
    std::unordered_map<sml::qualified_name, class_view_model> qname_to_class_;
    std::unordered_map<sml::qualified_name, enumeration_view_model>
    qname_to_enumeration_;
    graph_type graph_;
    qname_to_vertex_type qname_to_vertex_;
    vertex_descriptor_type root_vertex_;
};

} } } } }

#endif
