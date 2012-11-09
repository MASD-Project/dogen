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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_BACKEND_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <utility>
#include <string>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/domain/model.hpp"
#include "dogen/generator/config/cpp_settings.hpp"
#include "dogen/generator/backends/cpp/cpp_location_manager.hpp"
#include "dogen/generator/backends/cpp/view_models/cmakelists_view_model.hpp"
#include "dogen/generator/backends/cpp/view_models/file_view_model.hpp"
#include "dogen/generator/backends/backend.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

class cpp_backend : public backend {
public:
    cpp_backend() = delete;
    cpp_backend(const cpp_backend&) = default;
    cpp_backend(cpp_backend&&) = default;
    cpp_backend& operator=(const cpp_backend&) = default;

public:
    cpp_backend(const sml::model& model, const config::cpp_settings& settings);
    virtual ~cpp_backend() noexcept {}

public:
    static backend::ptr
    create(const sml::model& model, const config::cpp_settings& settings);

private:
    void log_formating_view(const std::string& view_name) const;
    void log_started() const;
    void log_finished() const;
    void log_cmakelists_disabled() const;
    void log_file_views(unsigned int how_many) const;

private:
    backend::value_entry_type
    generate_file_view_model(const view_models::file_view_model& vm) const;
    backend::value_type generate_file_view_models() const;
    backend::value_type generate_cmakelists() const;

public:
    backend::value_type generate() override;
    std::vector<boost::filesystem::path> managed_directories() const override;

private:
    const sml::model model_;
    const config::cpp_settings settings_;
    const cpp_location_manager location_manager_;
};

} } } }

#endif
