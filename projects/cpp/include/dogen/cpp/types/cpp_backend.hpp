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
#ifndef DOGEN_CPP_BACKEND_HPP
#define DOGEN_CPP_BACKEND_HPP

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
#include "dogen/cpp/types/location_manager.hpp"
#include "dogen/cpp/types/view_models/cmakelists_view_model.hpp"
#include "dogen/cpp/types/view_models/file_view_model.hpp"

namespace dogen {
namespace cpp {

class cpp_backend final {
public:
    cpp_backend() = delete;
    cpp_backend(const cpp_backend&) = default;
    cpp_backend(cpp_backend&&) = default;
    cpp_backend& operator=(const cpp_backend&) = default;

public:
    cpp_backend(const sml::model& model, const config::cpp_settings& settings);
    virtual ~cpp_backend() noexcept {}

public:
    typedef std::map<boost::filesystem::path, std::string> value_type;
    typedef std::pair<boost::filesystem::path, std::string> value_entry_type;

private:
    void log_formating_view(const std::string& view_name) const;
    void log_started() const;
    void log_finished() const;
    void log_cmakelists_disabled() const;
    void log_file_views(unsigned int how_many) const;

private:
    value_entry_type
    generate_file_view_model(const view_models::file_view_model& vm) const;
    value_type generate_file_view_models() const;
    value_type generate_cmakelists() const;

public:
    value_type generate();
    std::vector<boost::filesystem::path> managed_directories() const;

private:
    const sml::model model_;
    const config::cpp_settings settings_;
    const location_manager location_manager_;
};

} }

#endif
