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

#include <map>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
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
    explicit workflow(const boost::filesystem::path& data_files_directory);

private:
    /**
     * @brief Hydrates all the modelines available in the library.
     */
    void hydrate_modelines();

    /**
     * @brief Hydrates all the licences available in the library.
     */
    void hydrate_licences(const sml::model& m);

private:
    /**
     * @brief Loads all external data such as modelines, licences, etc.
     */
    void load_data_activity(const sml::model& m);

public:
    std::map<boost::filesystem::path, std::string> execute(const sml::model& m);

private:
    const boost::filesystem::path data_files_directory_;
    std::unordered_map<std::string, modeline_group> modeline_groups_;
    std::unordered_map<std::string, licence> licences_;
};

} }

#endif
