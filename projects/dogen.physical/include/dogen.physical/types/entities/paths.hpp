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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_PATHS_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_PATHS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/filesystem/path.hpp>

namespace dogen::physical::entities {

/**
 * @brief Path information for a given element.
 */
class paths final {
public:
    paths() = default;
    paths(const paths&) = default;
    ~paths() = default;

public:
    paths(paths&& rhs);

public:
    paths(
        const boost::filesystem::path& absolute,
        const std::unordered_map<std::string, boost::filesystem::path>& relative);

public:
    /**
     * @brief Absolute path to the file, indicating the location in the filesystem where it will be
     *  written.
     */
    /**@{*/
    const boost::filesystem::path& absolute() const;
    boost::filesystem::path& absolute();
    void absolute(const boost::filesystem::path& v);
    void absolute(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Path relative to parts, which required it.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::filesystem::path>& relative() const;
    std::unordered_map<std::string, boost::filesystem::path>& relative();
    void relative(const std::unordered_map<std::string, boost::filesystem::path>& v);
    void relative(const std::unordered_map<std::string, boost::filesystem::path>&& v);
    /**@}*/

public:
    bool operator==(const paths& rhs) const;
    bool operator!=(const paths& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(paths& other) noexcept;
    paths& operator=(paths other);

private:
    boost::filesystem::path absolute_;
    std::unordered_map<std::string, boost::filesystem::path> relative_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::paths& lhs,
    dogen::physical::entities::paths& rhs) {
    lhs.swap(rhs);
}

}

#endif
