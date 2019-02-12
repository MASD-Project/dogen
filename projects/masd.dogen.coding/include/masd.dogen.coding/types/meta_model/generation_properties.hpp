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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_GENERATION_PROPERTIES_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_GENERATION_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace masd::dogen::coding::meta_model {

/**
 * @brief Properties related to code generation.
 */
class generation_properties final {
public:
    generation_properties(const generation_properties&) = default;
    ~generation_properties() = default;

public:
    generation_properties();

public:
    generation_properties(generation_properties&& rhs);

public:
    generation_properties(
        const bool force_write,
        const bool compatibility_mode_enabled,
        const bool delete_extra_files,
        const std::vector<std::string>& ignore_files_matching_regex,
        const boost::filesystem::path& cpp_headers_output_directory);

public:
    /**
     * @brief Always write files, even when there are no differences.
     */
    /**@{*/
    bool force_write() const;
    void force_write(const bool v);
    /**@}*/

    /**
     * @brief If true, attempt to process inputs, ignoring certain types of errors.
     */
    /**@{*/
    bool compatibility_mode_enabled() const;
    void compatibility_mode_enabled(const bool v);
    /**@}*/

    /**
     * @brief If true, deletes any files that are not known to Dogen .
     */
    /**@{*/
    bool delete_extra_files() const;
    void delete_extra_files(const bool v);
    /**@}*/

    /**
     * @brief Files matching the supplied regular expressions will be ignored by Dogen.
     *
     * Only applicable when deleting extra files.
     */
    /**@{*/
    const std::vector<std::string>& ignore_files_matching_regex() const;
    std::vector<std::string>& ignore_files_matching_regex();
    void ignore_files_matching_regex(const std::vector<std::string>& v);
    void ignore_files_matching_regex(const std::vector<std::string>&& v);
    /**@}*/

    /**
     * @brief Directory in which to place C++ header files.
     */
    /**@{*/
    const boost::filesystem::path& cpp_headers_output_directory() const;
    boost::filesystem::path& cpp_headers_output_directory();
    void cpp_headers_output_directory(const boost::filesystem::path& v);
    void cpp_headers_output_directory(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const generation_properties& rhs) const;
    bool operator!=(const generation_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(generation_properties& other) noexcept;
    generation_properties& operator=(generation_properties other);

private:
    bool force_write_;
    bool compatibility_mode_enabled_;
    bool delete_extra_files_;
    std::vector<std::string> ignore_files_matching_regex_;
    boost::filesystem::path cpp_headers_output_directory_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::generation_properties& lhs,
    masd::dogen::coding::meta_model::generation_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
