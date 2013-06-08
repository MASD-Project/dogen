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
#ifndef DOGEN_CONFIG_TEST_MOCK_SETTINGS_FACTORY_HPP
#define DOGEN_CONFIG_TEST_MOCK_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/settings.hpp"

namespace dogen {
namespace config {
namespace test {

class mock_settings_factory {
public:
    mock_settings_factory() = delete;
    mock_settings_factory(const mock_settings_factory&) = delete;
    ~mock_settings_factory() = delete;
    mock_settings_factory(mock_settings_factory&&) = delete;
    mock_settings_factory& operator=(const mock_settings_factory&) = delete;

public:
    static config::output_settings build_output_settings(bool verbose = true);

    static config::troubleshooting_settings
    build_troubleshooting_settings(bool verbose = true);

    static config::cpp_settings build_cpp_settings();

    static config::cpp_settings build_cpp_settings(
        boost::filesystem::path src_dir,
        boost::filesystem::path include_dir,
        bool verbose = true);

    static config::cpp_settings build_cpp_settings(
        boost::filesystem::path project_dir,
        bool verbose = true);

    static config::modeling_settings build_modeling_settings(
        boost::filesystem::path target,
        std::string module_path,
        bool verbose = true);

    static config::settings build_settings(boost::filesystem::path target,
        boost::filesystem::path src_dir,
        boost::filesystem::path include_dir,
        std::string module_path,
        bool verbose = true);

    static config::settings build_settings(boost::filesystem::path target,
        boost::filesystem::path project_dir,
        std::string module_path,
        bool verbose = true);
};

} } }

#endif
