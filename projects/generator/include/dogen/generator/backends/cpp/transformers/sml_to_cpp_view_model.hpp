/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
    sml_to_cpp_view_model(cpp_location_manager location_manager,
        std::set<cpp_facet_types> facet_types,
        sml::model model, bool disable_facet_includers,
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
     * @brief Flattens all the SML namespace information stored in
     * qualified name into a list of strings with C++ namespaces.
     */
    std::list<std::string>
    join_namespaces(sml::qualified_name name) const;

    /**
     * @brief Returns the identifier to be used for this name on a
     * database context.
     */
    std::string database_name(sml::qualified_name name) const;

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
    to_header_guard_name(boost::filesystem::path relative_path) const;

    cpp_location_request location_request_factory(cpp_facet_types facet_type,
        cpp_file_types file_type, sml::qualified_name name,
        bool ignore_external_package_path = false) const;

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
     * @brief Transforms an SML pod into a C++ class view.
     */
    view_models::class_view_model transform_class(
        sml::pod pod, std::list<std::string> namespaces) const;

    /**
     * @brief Transforms a SML pod into a C++ file view.
     */
    view_models::file_view_model
    transform_file(cpp_facet_types facet_type, cpp_file_types file_type,
        sml::pod pod);

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
    const cpp_location_manager location_manager_;
    const std::set<cpp_facet_types> facet_types_;
    const sml::model model_;
    const bool disable_facet_includers_;
    const bool disable_keys_;
    cpp_dependency_manager dependency_manager_;
};

} } } } }

#endif
