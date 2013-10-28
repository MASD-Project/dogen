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
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/sml/types/property_cache.hpp"
#include "dogen/om/types/file.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/types/modeline_group.hpp"

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
    explicit
    workflow(const std::list<boost::filesystem::path>& data_files_directories);

private:
    class context;

    /**
     * @brief Throws if context is null.
     */
    void ensure_non_null_context() const;

private:
    /*
     * @brief Throws an exception due to a missing item.
     */
    void throw_missing_item(const std::string& msg, const std::string& n) const;

    /**
     * @brief Extracts a licence using meta-data in the Taggable.
     */
    licence extract_licence(const boost::property_tree::ptree& meta_data) const;

    /**
     * @brief Extracts a modeline using meta-data in the Taggable.
     */
    modeline extract_modeline(
        const boost::property_tree::ptree& meta_data) const;

    /**
     * @brief Extracts a code generation marker using meta-data in the
     * Taggable.
     */
    std::string extract_marker(
        const boost::property_tree::ptree& meta_data) const;

private:
    /**
     * @brief Creates the actual list of directories used by hydrators
     * to load data.
     */
    std::list<boost::filesystem::path>
    create_directories(const std::string for_whom) const;

    /**
     * @brief Hydrates all the modelines available in the library.
     */
    void hydrate_modelines_activity();

    /**
     * @brief Hydrates all the licences available in the library.
     */
    void hydrate_licences_activity();

    /**
     * @brief Creates the code generation marker.
     */
    void create_marker_activity(const sml::model& m);

    /**
     * @brief Loads all external data such as modelines, licences, etc
     * and sets up any required data structures.
     */
    void setup_reference_data_subworkflow(const sml::model& m);

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
    const std::list<boost::filesystem::path> data_files_directories_;
    mutable std::shared_ptr<context> context_;
};

} }

#endif
