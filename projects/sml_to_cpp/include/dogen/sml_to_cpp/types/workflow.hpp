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
#ifndef DOGEN_SML_TO_CPP_TYPES_WORKFLOW_HPP
#define DOGEN_SML_TO_CPP_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <utility>
#include <string>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/cpp/types/content_descriptor_factory.hpp"
#include "dogen/cpp/types/cmakelists_info.hpp"
#include "dogen/cpp/types/source_file.hpp"
#include "dogen/sml_to_cpp/types/includer.hpp"
#include "dogen/sml_to_cpp/types/locator.hpp"
#include "dogen/sml_to_cpp/types/transformer.hpp"
#include "dogen/sml_to_cpp/types/extractor.hpp"
#include "dogen/sml_to_cpp/types/context.hpp"
#include "dogen/sml_to_cpp/types/source_file_factory.hpp"
#include "dogen/cpp/types/project.hpp"

namespace dogen {
namespace sml_to_cpp {

/**
 * @brief Orchestrates all the classes in the C++ model to go from an
 * SML model into a set of C++ files representing that model.
 */
class workflow final {
public:
    workflow() = delete;
    workflow(const workflow&) = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

public:
    workflow(const sml::model& model, const config::cpp_settings& settings);
    virtual ~workflow() noexcept {}

private:
    /**
     * @brief Ensure the C++ settings are consistent.
     */
    void validate_settings() const;

private:
    /**
     * @brief Recursively generates C++ class objects.
     */
    void transform_object(const sml::object& ao);

    /**
     * @brief Transforms the module into a C++ namespace.
     */
    void transform_module(const sml::module& m);

    /**
     * @brief Transforms the model into a registrar.
     */
    void transform_registrar();

    /**
     * @brief Transforms the enumerator into a C++ enumeration..
     */
    void transform_enumeration(const sml::enumeration& e);

    /**
     * @brief Creates all C++ types in the context.
     */
    void transformation_sub_workflow();

private:

    /**
     * @brief Register the file with registrar, if it's a header file.
     */
    void register_header(const cpp::source_file& fi) const;

    /**
     * @brief Generate C++ files for classes.
     */
    std::list<cpp::source_file> generate_source_files_for_classes_activity() const;

    /**
     * @brief Generate C++ files for classes.
     */
    std::list<cpp::source_file>
        generate_source_files_for_namespaces_activity() const;

    /**
     * @brief Generate C++ files for registrars.
     */
    std::list<cpp::source_file> generate_registrars_activity() const;

    /**
     * @brief Generate C++ files for includers.
     */
    std::list<cpp::source_file> generate_includers_activity() const;

    /**
     * @brief Generate C++ files for visitors.
     */
    std::list<cpp::source_file> generate_visitors_activity() const;

    /**
     * @brief Generate C++ files for enumerations.
     */
    std::list<cpp::source_file> generate_enums_activity() const;

    /**
     * @brief Generate C++ files for exceptions.
     */
    std::list<cpp::source_file> generate_exceptions_activity() const;

    /**
     * @brief Create the cmakelists makefiles.
     */
    void generate_cmakelists_activity(cpp::project& p) const;

    /**
     * @brief Creates the ODB compiler options file.
     */
    void generate_odb_options_activity(cpp::project& p) const;

    /**
     * @brief Generate all C++ files.
     */
    void generate_source_files_activity(cpp::project& p) const;

    /**
     * @brief Perform the generation sub-workflow.
     */
    cpp::project generation_sub_workflow();

public:
    /**
     * @brief Execute the workflow.
     */
    cpp::project execute();

    /**
     * @brief Returns the directories managed by this workflow.
     *
     * This method is only exposed for testing purposes.
     */
    std::vector<boost::filesystem::path> managed_directories() const;

private:
    context context_;
    const sml::model& model_;
    const config::cpp_settings settings_;
    const locator locator_;
    mutable includer includer_;
    const source_file_factory source_file_factory_;
    transformer transformer_;
    const cpp::content_descriptor_factory descriptor_factory_;
    const extractor extractor_;
};

} }

#endif
