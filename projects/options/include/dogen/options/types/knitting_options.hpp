/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_OPTIONS_TYPES_KNITTING_OPTIONS_HPP
#define DOGEN_OPTIONS_TYPES_KNITTING_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/options/serialization/knitting_options_fwd_ser.hpp"

namespace dogen {
namespace options {

/**
 * @brief Configuration options related to the knit library.
 */
class knitting_options final {
public:
    knitting_options(const knitting_options&) = default;
    ~knitting_options() = default;

public:
    knitting_options();

public:
    knitting_options(knitting_options&& rhs);

public:
    knitting_options(
        const std::string& log_level,
        const boost::filesystem::path& target,
        const bool delete_extra_files,
        const bool force_write,
        const std::vector<std::string>& ignore_patterns,
        const boost::filesystem::path& output_directory_path,
        const boost::filesystem::path& cpp_headers_output_directory_path,
        const boost::filesystem::path& log_directory);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::options::knitting_options& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::options::knitting_options& v, unsigned int version);

public:
    /**
     * @brief What level of logging to log at.
     */
    /**@{*/
    const std::string& log_level() const;
    std::string& log_level();
    void log_level(const std::string& v);
    void log_level(const std::string&& v);
    /**@}*/

    /**
     * @brief Path to the Dia diagram that contains the model to generate.
     */
    /**@{*/
    const boost::filesystem::path& target() const;
    boost::filesystem::path& target();
    void target(const boost::filesystem::path& v);
    void target(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Delete any extra files found in managed directories.
     */
    /**@{*/
    bool delete_extra_files() const;
    void delete_extra_files(const bool v);
    /**@}*/

    /**
     * @brief Always generate files even if there are no differences with existing file.
     */
    /**@{*/
    bool force_write() const;
    void force_write(const bool v);
    /**@}*/

    /**
     * @brief List of regular expressions to filter out files to ignore.
     */
    /**@{*/
    const std::vector<std::string>& ignore_patterns() const;
    std::vector<std::string>& ignore_patterns();
    void ignore_patterns(const std::vector<std::string>& v);
    void ignore_patterns(const std::vector<std::string>&& v);
    /**@}*/

    /**
     * @brief Full path to the directory in which to place the generated code.
     */
    /**@{*/
    const boost::filesystem::path& output_directory_path() const;
    boost::filesystem::path& output_directory_path();
    void output_directory_path(const boost::filesystem::path& v);
    void output_directory_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief If set, all c++ include files will be placed at this location.
     */
    /**@{*/
    const boost::filesystem::path& cpp_headers_output_directory_path() const;
    boost::filesystem::path& cpp_headers_output_directory_path();
    void cpp_headers_output_directory_path(const boost::filesystem::path& v);
    void cpp_headers_output_directory_path(const boost::filesystem::path&& v);
    /**@}*/

    const boost::filesystem::path& log_directory() const;
    boost::filesystem::path& log_directory();
    void log_directory(const boost::filesystem::path& v);
    void log_directory(const boost::filesystem::path&& v);

public:
    bool operator==(const knitting_options& rhs) const;
    bool operator!=(const knitting_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(knitting_options& other) noexcept;
    knitting_options& operator=(knitting_options other);

private:
    std::string log_level_;
    boost::filesystem::path target_;
    bool delete_extra_files_;
    bool force_write_;
    std::vector<std::string> ignore_patterns_;
    boost::filesystem::path output_directory_path_;
    boost::filesystem::path cpp_headers_output_directory_path_;
    boost::filesystem::path log_directory_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::options::knitting_options& lhs,
    dogen::options::knitting_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
