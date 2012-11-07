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
#ifndef DOGEN_GENERATOR_CONFIG_OUTPUT_SETTINGS_HPP
#define DOGEN_GENERATOR_CONFIG_OUTPUT_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace generator {
namespace config {

class output_settings {
public:
    output_settings(const output_settings&) = default;
    ~output_settings() = default;
    output_settings& operator=(const output_settings&) = default;
    output_settings(output_settings&&) = default;

public:
    output_settings() :
        verbose_(false),
        output_to_stdout_(false),
        output_to_file_(false),
        delete_extra_files_(false),
        force_write_(false) {}

public:
    /**
     * @brief Output generated code to standard output.
     */
    /**@{*/
    bool output_to_stdout() const { return output_to_stdout_; }
    output_settings& output_to_stdout(bool value) {
        output_to_stdout_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Output generated code to files.
     */
    /**@{*/
    bool output_to_file() const { return output_to_file_; }
    output_settings& output_to_file(bool value) {
        output_to_file_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Delete any extra files found in managed directories.
     */
    /**@{*/
    bool delete_extra_files() const { return delete_extra_files_; }
    output_settings& delete_extra_files(bool value) {
        delete_extra_files_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Always generate files even if there are no differences
     * with existing file.
     */
    /**@{*/
    bool force_write() const { return force_write_; }
    output_settings& force_write(bool value) {
        force_write_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Print additional diagnostic information to standard output.
     */
    /**@{*/
    bool verbose() const { return verbose_; }
    output_settings& verbose(bool value) {
        verbose_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief List of regular expressions to filter out files to ignore.
     */
    /**@{*/
    std::vector<std::string> ignore_patterns() const {
        return ignore_patterns_;
    }
    output_settings& ignore_patterns(std::vector<std::string> value) {
        ignore_patterns_ = value;
        return *this;
    }
    /**@}*/

private:
    bool verbose_;
    bool output_to_stdout_;
    bool output_to_file_;
    bool delete_extra_files_;
    bool force_write_;
    std::vector<std::string> ignore_patterns_;
};

std::ostream& operator<<(std::ostream& stream, output_settings value);

} } }

#endif
