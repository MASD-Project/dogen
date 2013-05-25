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
#ifndef DOGEN_CPP_TYPES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_WORKFLOW_HPP

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
#include "dogen/cpp/types/includer.hpp"
#include "dogen/cpp/types/locator.hpp"
#include "dogen/cpp/types/transformer.hpp"
#include "dogen/cpp/types/content_descriptor_factory.hpp"
#include "dogen/cpp/types/cmakelists_info.hpp"
#include "dogen/cpp/types/file_info.hpp"
#include "dogen/cpp/types/file_info_factory.hpp"

namespace dogen {
namespace cpp {

class workflow final {
public:
    workflow() = delete;
    workflow(const workflow&) = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

public:
    workflow(const sml::model& model, const config::cpp_settings& settings);
    virtual ~workflow() noexcept {}

public:
    typedef std::map<boost::filesystem::path, std::string> result_type;
    typedef std::pair<boost::filesystem::path, std::string> result_entry_type;

private:
    void log_formating_view(const std::string& view_name) const;
    void log_started() const;
    void log_finished() const;
    void log_cmakelists_disabled() const;
    void log_file_views(unsigned int how_many) const;

private:
    /**
     * @brief Ensure the C++ settings are consistent.
     */
    void validate_settings() const;

private:
    /**
     * @brief Creates all C++ files for enums in the model.
     */
    result_type generate_enums_activity();

    /**
     * @brief Creates all C++ files for exceptions in the model.
     */
    result_type generate_exceptions_activity();

    /**
     * @brief Creates all C++ files for classes in the model.
     */
    result_type generate_classes_activity();

    /**
     * @brief Creates all C++ files for namespaces in the model.
     */
    result_type generate_namespaces_activity();

    /**
     * @brief Creates all C++ files for registrars in the model.
     */
    result_type generate_registrars_activity();

    /**
     * @brief Creates all C++ files for includers in the model.
     */
    result_type generate_includers_activity();

    /**
     * @brief Composite activity that generates all C++ files.
     */
    result_type generate_file_infos_activity();

private:
    result_entry_type
    generate_file_info(const file_info& fi) const;
    result_type old_generate_file_infos() const;
    result_type generate_cmakelists() const;
    result_entry_type generate_odb_options() const;

public:
    result_type execute();
    std::vector<boost::filesystem::path> managed_directories() const;

private:
    const sml::model model_;
    const config::cpp_settings settings_;
    const locator locator_;
    includer includer_;
    file_info_factory file_info_factory_;
    const transformer transformer_;
    const content_descriptor_factory descriptor_factory_;
};

} }

#endif
