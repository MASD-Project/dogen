/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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

private:
    bool verbose_;
    bool output_to_stdout_;
    bool output_to_file_;
    bool delete_extra_files_;
    bool force_write_;
};

std::ostream& operator<<(std::ostream& stream, output_settings value);

} } }

#endif
