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
#ifndef DOGEN_CONFIG_TEST_MOCK_OPTIONS_FACTORY_HPP
#define DOGEN_CONFIG_TEST_MOCK_OPTIONS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/knitting_options.hpp"

namespace dogen {
namespace config {
namespace test {

/**
 * @brief Creates instances of setting classes for testing.
 */
class mock_options_factory {
public:
    mock_options_factory() = delete;
    mock_options_factory(const mock_options_factory&) = delete;
    ~mock_options_factory() = delete;
    mock_options_factory(mock_options_factory&&) = delete;
    mock_options_factory& operator=(const mock_options_factory&) = delete;

public:
    /**
     * @brief Returns the output options configured to output to
     * file.
     */
    static output_options make_output_options();

    /**
     * @brief Returns the C++ options with empty source and include
     * directories.
     *
     * All facets are enabled.
     */
    static cpp_options make_cpp_options();

    /**
     * @brief Returns the C++ options with source and include
     * directory populated.
     *
     * All facets are enabled.
     */
    static cpp_options make_cpp_options(
        const boost::filesystem::path& src_dir,
        const boost::filesystem::path& include_dir);

    /**
     * @brief Returns the C++ options with empty source and include
     * directories and a project directory populated.
     *
     * All facets are enabled.
     */
    static cpp_options make_cpp_options(
        const boost::filesystem::path& project_dir);

    /**
     * @brief Returns the input options with the target and module
     * path set.
     */
    static input_options make_input_options(
        const boost::filesystem::path& target,
        const std::string& module_path);

    static knitting_options make_knitting_options(
        const boost::filesystem::path& target,
        const boost::filesystem::path& src_dir,
        const boost::filesystem::path& include_dir,
        const std::string& module_path,
        const bool verbose = true);

    static knitting_options make_knitting_options(
        const boost::filesystem::path& target,
        const boost::filesystem::path& project_dir,
        const std::string& module_path,
        const bool verbose = true);
};

} } }

#endif
