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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_WORKFLOW_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_WORKFLOW_HPP

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
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/cpp/types/project.hpp"

namespace dogen {
namespace cpp_formatters {

/**
 * @brief Given a C++ project, formats all of the C++ classes into a
 * file representation.
 */
class workflow final {
public:
    workflow() = delete;
    workflow(const workflow&) = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

public:
    workflow(const config::cpp_settings& settings);
    virtual ~workflow() noexcept {}

public:
    typedef std::map<boost::filesystem::path, std::string> result_type;
    typedef std::pair<boost::filesystem::path, std::string> result_entry_type;

private:
    /**
     * @brief Create the cmakelists makefiles.
     */
    result_type format_cmakelists_activity(const cpp::project& p) const;

    /**
     * @brief Creates the ODB compiler options file.
     */
    result_entry_type format_odb_options_activity(const cpp::project& p) const;

    /**
     * @brief Generate all C++ files.
     */
    result_type format_file_infos_activity(const cpp::project& p) const;

public:
    /**
     * @brief Execute the workflow.
     */
    result_type execute(const cpp::project& p);

private:
    const config::cpp_settings settings_;
};

} }

#endif
