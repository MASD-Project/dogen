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
#ifndef MASD_DOGEN_TYPES_GENERATION_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_GENERATION_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace masd::dogen {

/**
 * @brief Configuration related to code generation.
 */
class generation_configuration final {
public:
    generation_configuration(const generation_configuration&) = default;
    ~generation_configuration() = default;

public:
    generation_configuration();

public:
    generation_configuration(generation_configuration&& rhs);

public:
    generation_configuration(
        const boost::filesystem::path& output_directory,
        const std::vector<boost::filesystem::path>& reference_model_directories,
        const bool force_write,
        const bool compatibility_mode_enabled,
        const boost::filesystem::path& target,
        const bool delete_extra_files,
        const std::vector<std::string>& ignore_files_matching_regex,
        const boost::filesystem::path& cpp_headers_output_directory);

public:
    /**
     * @brief Directory in which to place the output.
     */
    /**@{*/
    const boost::filesystem::path& output_directory() const;
    boost::filesystem::path& output_directory();
    generation_configuration& output_directory(const boost::filesystem::path& v);
    generation_configuration& output_directory(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Directories to search for reference models.
     */
    /**@{*/
    const std::vector<boost::filesystem::path>& reference_model_directories() const;
    std::vector<boost::filesystem::path>& reference_model_directories();
    generation_configuration& reference_model_directories(const std::vector<boost::filesystem::path>& v);
    generation_configuration& reference_model_directories(const std::vector<boost::filesystem::path>&& v);
    /**@}*/

    /**
     * @brief Always write files, even when there are no differences.
     */
    /**@{*/
    bool force_write() const;
    generation_configuration& force_write(const bool v);
    /**@}*/

    /**
     * @brief If true, attempt to process inputs, ignoring certain types of errors.
     */
    /**@{*/
    bool compatibility_mode_enabled() const;
    generation_configuration& compatibility_mode_enabled(const bool v);
    /**@}*/

    /**
     * @brief Target model for generation.
     */
    /**@{*/
    const boost::filesystem::path& target() const;
    boost::filesystem::path& target();
    generation_configuration& target(const boost::filesystem::path& v);
    generation_configuration& target(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief If true, deletes any files that are not known to Dogen .
     */
    /**@{*/
    bool delete_extra_files() const;
    generation_configuration& delete_extra_files(const bool v);
    /**@}*/

    /**
     * @brief Files matching the supplied regular expressions will be ignored by Dogen.
     *
     * Only applicable when deleting extra files.
     */
    /**@{*/
    const std::vector<std::string>& ignore_files_matching_regex() const;
    std::vector<std::string>& ignore_files_matching_regex();
    generation_configuration& ignore_files_matching_regex(const std::vector<std::string>& v);
    generation_configuration& ignore_files_matching_regex(const std::vector<std::string>&& v);
    /**@}*/

    /**
     * @brief Directory in which to place C++ header files.
     */
    /**@{*/
    const boost::filesystem::path& cpp_headers_output_directory() const;
    boost::filesystem::path& cpp_headers_output_directory();
    generation_configuration& cpp_headers_output_directory(const boost::filesystem::path& v);
    generation_configuration& cpp_headers_output_directory(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const generation_configuration& rhs) const;
    bool operator!=(const generation_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(generation_configuration& other) noexcept;
    generation_configuration& operator=(generation_configuration other);

private:
    boost::filesystem::path output_directory_;
    std::vector<boost::filesystem::path> reference_model_directories_;
    bool force_write_;
    bool compatibility_mode_enabled_;
    boost::filesystem::path target_;
    bool delete_extra_files_;
    std::vector<std::string> ignore_files_matching_regex_;
    boost::filesystem::path cpp_headers_output_directory_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation_configuration& lhs,
    masd::dogen::generation_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
