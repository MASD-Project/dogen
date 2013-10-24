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
#include "dogen/sml/types/model.hpp"
#include "dogen/om/types/file.hpp"

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
    explicit workflow(const boost::filesystem::path& data_files_directory);

private:
    class context;

    /**
     * @brief Throws if context is null.
     */
    void ensure_non_null_context() const;

private:
    /**
     * @brief Hydrates all the modelines available in the library.
     */
    void hydrate_modelines_activity();

    /**
     * @brief Hydrates all the licences available in the library.
     */
    void hydrate_licences_activity(const sml::model& m);

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
    std::list<file> execute(const sml::model& m);

private:
    const boost::filesystem::path data_files_directory_;
    mutable std::shared_ptr<context> context_;
};

} }

#endif
