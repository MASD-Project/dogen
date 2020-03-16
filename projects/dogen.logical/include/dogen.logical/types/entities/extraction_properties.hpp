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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_EXTRACTION_PROPERTIES_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_EXTRACTION_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_set>
#include <boost/filesystem/path.hpp>

namespace dogen::logical::entities {

/**
 * @brief Properties related to extraction.
 */
class extraction_properties final {
public:
    extraction_properties(const extraction_properties&) = default;
    ~extraction_properties() = default;

public:
    extraction_properties();

public:
    extraction_properties(extraction_properties&& rhs);

public:
    extraction_properties(
        const boost::filesystem::path& cpp_headers_output_directory,
        const std::unordered_set<std::string>& enabled_backends,
        const bool enable_backend_directories);

public:
    /**
     * @brief Directory in which to place C++ header files. Must be a relative path.
     */
    /**@{*/
    const boost::filesystem::path& cpp_headers_output_directory() const;
    boost::filesystem::path& cpp_headers_output_directory();
    void cpp_headers_output_directory(const boost::filesystem::path& v);
    void cpp_headers_output_directory(const boost::filesystem::path&& v);
    /**@}*/

    const std::unordered_set<std::string>& enabled_backends() const;
    std::unordered_set<std::string>& enabled_backends();
    void enabled_backends(const std::unordered_set<std::string>& v);
    void enabled_backends(const std::unordered_set<std::string>&& v);

    bool enable_backend_directories() const;
    void enable_backend_directories(const bool v);

public:
    bool operator==(const extraction_properties& rhs) const;
    bool operator!=(const extraction_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(extraction_properties& other) noexcept;
    extraction_properties& operator=(extraction_properties other);

private:
    boost::filesystem::path cpp_headers_output_directory_;
    std::unordered_set<std::string> enabled_backends_;
    bool enable_backend_directories_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::extraction_properties& lhs,
    dogen::logical::entities::extraction_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
