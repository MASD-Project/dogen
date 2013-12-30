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
#ifndef DOGEN_OM_TYPES_WORKFLOW_HPP
#define DOGEN_OM_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/om/types/file.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/types/modeline_group.hpp"
#include "dogen/om/types/annotation_factory.hpp"
#include "dogen/om/types/type_formatter_interface.hpp"
#include "dogen/om/types/module_formatter_interface.hpp"
#include "dogen/om/types/concept_formatter_interface.hpp"


namespace dogen {
namespace om {

/**
 * @brief Executes a complete workflow for the output model.
 */
class workflow {
public:
    workflow(const workflow&) = default;
    workflow(workflow&&) = default;
    ~workflow() = default;

public:
    /**
     * @brief Initialise workflow.
     *
     * @param project_directory Top-level directory for the project
     * @param cpp_source_directory Directory under which the C++
     * source files will be placed.
     * @param cpp_include_directory Directory under which the include
     * files will be placed.
     * @param data_files_directories Additional directories to search
     * for data files.
     */
    workflow(const boost::filesystem::path& project_directory,
        const boost::filesystem::path& cpp_source_directory,
        const boost::filesystem::path& cpp_include_directory,
        const std::list<boost::filesystem::path>& data_files_directories);

private:
    class context;

    /**
     * @brief Throws if context is null.
     */
    void ensure_non_null_context() const;

public:
    /**
     * @brief Process types.
     */
    void operator()(const sml::type& t) const;

    /**
     * @brief Process modules.
     */
    void operator()(const sml::module& m) const;

    /**
     * @brief Process concepts.
     */
    void operator()(const sml::concept& c) const;

public:
    /**
     * @brief Handle the model itself as a module.
     *
     * @deprecated this is required only until we generate a module
     * for the model.
     */
    void model_file_subworkflow(const sml::model& model);

public:
    /**
     * @brief Run the entire output model workflow.
     */
    std::list<file> execute(const sml::model& m);

private:
    std::list<boost::shared_ptr<type_formatter_interface> >
    type_formatters_;
    std::list<boost::shared_ptr<module_formatter_interface> >
    module_formatters_;
    std::list<boost::shared_ptr<concept_formatter_interface> >
    concept_formatters_;
    annotation_factory annotation_factory_;
    std::shared_ptr<context> context_;
};

} }

#endif
