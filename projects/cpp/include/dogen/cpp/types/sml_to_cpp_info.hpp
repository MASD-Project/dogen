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
#ifndef DOGEN_CPP_TYPES_INFOS_SML_TO_CPP_INFO_HPP
#define DOGEN_CPP_TYPES_INFOS_SML_TO_CPP_INFO_HPP

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
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/cpp/types/locator.hpp"
#include "dogen//cpp/types/includer.hpp"
#include "dogen/cpp/types/aspect_types.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/sml/types/meta_types.hpp"
#include "dogen/sml/types/package.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/cpp/types/file_info.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Transformer responsible for converting an SML model instance
 * into the corresponding C++ view model.
 */
class sml_to_cpp_info {
public:
    sml_to_cpp_info() = delete;
    sml_to_cpp_info(const sml_to_cpp_info&) = delete;
    ~sml_to_cpp_info() = default;
    sml_to_cpp_info(sml_to_cpp_info&&) = delete;
    sml_to_cpp_info& operator=(const sml_to_cpp_info&) = delete;

public:
    sml_to_cpp_info(const locator& locator,
        const includer& includer,
        const config::cpp_settings& settings,
        const sml::model& model);

private:
    void log_started() const;
    void log_finished(unsigned int count) const;
    void log_keys() const;
    void log_includers() const;
    void log_generating_file(config::cpp_facet_types facet,
        aspect_types aspect, file_types file, std::string name,
        sml::meta_types mt) const;

private:
    /**
     * @brief Returns true if the facet requires a C++ source file,
     * false otherwise.
     */
    bool has_implementation(const config::cpp_facet_types ft,
        const dogen::sml::meta_types mt) const;

    /**
     * @brief Returns true if facet has forward declarations, false otherwise.
     */
    bool has_forward_decls(const config::cpp_facet_types ft,
        const dogen::sml::meta_types mt) const;

    /**
     * @brief Transforms a relative path to a header file into a C++
     * header guard name.
     */
    std::string
    to_header_guard_name(const boost::filesystem::path& relative_path) const;

    location_request location_request_factory(config::cpp_facet_types ft,
        file_types flt, aspect_types at, const sml::qname& n) const;

    /**
     * @brief Generate a class view model for a given key type.
     *
     * @param is_versioned if true, generates the versioned key view
     * model, if false the unversioned key.
     */
    class_info create_key_class_info(bool is_versioned) const;

    /**
     * @brief Generate a file view model for a given key type.
     *
     * @param is_versioned if true, generates the versioned key view
     * model, if false the unversioned key.
     */
    file_info create_key_file_info(
        config::cpp_facet_types facet_type, file_types file_type,
        aspect_types aspect_type);

private:
    /**
     * @brief Performs the initial setup of the file view model.
     */
    file_info create_file(config::cpp_facet_types ft, file_types flt,
        aspect_types at, const sml::qname& name);

    /**
     * @brief Transforms a SML pod into a C++ file view.
     */
    file_info transform_file(config::cpp_facet_types ft,
        file_types flt, aspect_types at, const sml::pod& p);

    /**
     * @brief Transforms a SML service into a C++ file view.
     */
    file_info transform_file(config::cpp_facet_types ft,
        file_types flt, aspect_types at, const sml::service& p);

    /**
     * @brief Transforms a SML enumeration into a C++ file view.
     */
    file_info
    transform_file(config::cpp_facet_types ft, file_types flt,
        aspect_types at, const sml::enumeration& e);

    /**
     * @brief Transforms a SML exception into a C++ file view.
     */
    file_info
    transform_file(config::cpp_facet_types ft, file_types flt,
        aspect_types at, const sml::exception& e);

    /**
     * @brief Transforms all versioned and unversioned keys.
     */
    std::vector<file_info> transform_keys();

    /**
     * @brief Transforms all facet includers
     */
    std::vector<file_info> transform_facet_includers() const;

    /**
     * @brief Transforms the serialisation registrar
     */
    std::vector<file_info> transform_registrar() const;

    /**
     * @brief Creates all the class view models
     */
    void create_class_infos();

    /**
     * @brief Creates all the enumeration view models
     */
    void create_enumeration_infos();

    /**
     * @brief Creates all the exception view models
     */
    void create_exception_infos();

    /**
     * @brief Returns the available facets for the given inputs.
     *
     * @param mt Meta-type which we want to process.
     * @param pt Pod type to process; must be set to invalid if the
     * meta-type is not a pod.
     */
    std::set<config::cpp_facet_types> enabled_facet_types(
        const sml::meta_types mt,
        const sml::pod_types pt = sml::pod_types::invalid) const;

    /**
     * @brief Transforms pods into file view models.
     */
    std::vector<file_info> transform_pods();

    /**
     * @brief Transforms services into file view models.
     */
    std::vector<file_info> transform_services();

    /**
     * @brief Transforms enumerations into view models.
     */
    std::vector<file_info> transform_enumerations();

    /**
     * @brief Transforms exceptions into view models.
     */
    std::vector<file_info> transform_exceptions();

    /**
     * @brief Transforms packages into view models.
     */
    std::vector<file_info> transform_packages();

    /**
     * @brief Transforms visitors into view models.
     */
    std::vector<file_info> transform_visitors();

public:
    /**
     * @brief Transforms the SML model instance into the corresponding
     * C++ view model.
     */
    std::vector<file_info> transform();

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
    typedef std::unordered_map<sml::qname, vertex_descriptor_type>
    qname_to_vertex_type;

private:
    const locator locator_;
    includer includer_;
    const config::cpp_settings settings_;
    const sml::model model_;
    std::unordered_map<sml::qname, class_info> qname_to_class_;
    std::unordered_map<sml::qname, enumeration_info>
    qname_to_enumeration_;
    std::unordered_map<sml::qname, exception_info>
    qname_to_exception_;
    std::unordered_map<sml::qname, visitor_info> qname_to_visitor_;
    graph_type graph_;
    qname_to_vertex_type qname_to_vertex_;
    vertex_descriptor_type root_vertex_;
};

} }

#endif
