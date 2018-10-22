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
#ifndef DOGEN_MODELING_TYPES_TRANSFORMS_OPTIONS_HPP
#define DOGEN_MODELING_TYPES_TRANSFORMS_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace modeling {
namespace transforms {

class options final {
public:
    options(const options&) = default;
    ~options() = default;

public:
    options();

public:
    options(options&& rhs);

public:
    options(
        const boost::filesystem::path& log_file,
        const std::string& log_level,
        const boost::filesystem::path& target,
        const bool delete_extra_files,
        const bool force_write,
        const std::vector<std::string>& ignore_patterns,
        const boost::filesystem::path& output_directory_path,
        const boost::filesystem::path& cpp_headers_output_directory_path,
        const bool compatibility_mode,
        const bool probe_stats,
        const bool probe_stats_disable_guids,
        const bool probe_stats_org_mode,
        const bool probe_all,
        const boost::filesystem::path& probe_directory,
        const bool probe_use_short_names);

public:
    /**
     * @brief Full path to the log file.
     */
    /**@{*/
    const boost::filesystem::path& log_file() const;
    boost::filesystem::path& log_file();
    void log_file(const boost::filesystem::path& v);
    void log_file(const boost::filesystem::path&& v);
    /**@}*/

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
     * @brief Full path to the model to generate.
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

    /**
     * @brief Try to process diagram even if there are errors.
     *
     * Only a certain class of errors are allowed, believed to be caused by backwards or
     * forwards compatibility problems: missing types or types that do not exist.
     */
    /**@{*/
    bool compatibility_mode() const;
    void compatibility_mode(const bool v);
    /**@}*/

    /**
     * @brief Enable probing for statistics around transforms.
     */
    /**@{*/
    bool probe_stats() const;
    void probe_stats(const bool v);
    /**@}*/

    /**
     * @brief Disable guids in probe stats, to make comparisons easier.
     */
    /**@{*/
    bool probe_stats_disable_guids() const;
    void probe_stats_disable_guids(const bool v);
    /**@}*/

    /**
     * @brief Output the stats as an org-mode document.
     */
    /**@{*/
    bool probe_stats_org_mode() const;
    void probe_stats_org_mode(const bool v);
    /**@}*/

    /**
     * @brief Enable all probing.
     */
    /**@{*/
    bool probe_all() const;
    void probe_all(const bool v);
    /**@}*/

    /**
     * @brief Full path to the directory in which to place probe information.
     */
    /**@{*/
    const boost::filesystem::path& probe_directory() const;
    boost::filesystem::path& probe_directory();
    void probe_directory(const boost::filesystem::path& v);
    void probe_directory(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Use short directory and file names. Useful mainly on windows due to path
     * size limitations.
     */
    /**@{*/
    bool probe_use_short_names() const;
    void probe_use_short_names(const bool v);
    /**@}*/

public:
    bool operator==(const options& rhs) const;
    bool operator!=(const options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(options& other) noexcept;
    options& operator=(options other);

private:
    boost::filesystem::path log_file_;
    std::string log_level_;
    boost::filesystem::path target_;
    bool delete_extra_files_;
    bool force_write_;
    std::vector<std::string> ignore_patterns_;
    boost::filesystem::path output_directory_path_;
    boost::filesystem::path cpp_headers_output_directory_path_;
    bool compatibility_mode_;
    bool probe_stats_;
    bool probe_stats_disable_guids_;
    bool probe_stats_org_mode_;
    bool probe_all_;
    boost::filesystem::path probe_directory_;
    bool probe_use_short_names_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::modeling::transforms::options& lhs,
    dogen::modeling::transforms::options& rhs) {
    lhs.swap(rhs);
}

}

#endif
