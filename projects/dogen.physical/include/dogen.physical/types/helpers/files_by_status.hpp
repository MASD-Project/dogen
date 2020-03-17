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
#ifndef DOGEN_PHYSICAL_TYPES_HELPERS_FILES_BY_STATUS_HPP
#define DOGEN_PHYSICAL_TYPES_HELPERS_FILES_BY_STATUS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen::physical::helpers {

class files_by_status final {
public:
    files_by_status() = default;
    files_by_status(const files_by_status&) = default;
    files_by_status(files_by_status&&) = default;
    ~files_by_status() = default;

public:
    files_by_status(
        const std::list<boost::filesystem::path>& unexpected,
        const std::list<boost::filesystem::path>& ignored);

public:
    const std::list<boost::filesystem::path>& unexpected() const;
    std::list<boost::filesystem::path>& unexpected();
    void unexpected(const std::list<boost::filesystem::path>& v);
    void unexpected(const std::list<boost::filesystem::path>&& v);

    const std::list<boost::filesystem::path>& ignored() const;
    std::list<boost::filesystem::path>& ignored();
    void ignored(const std::list<boost::filesystem::path>& v);
    void ignored(const std::list<boost::filesystem::path>&& v);

public:
    bool operator==(const files_by_status& rhs) const;
    bool operator!=(const files_by_status& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(files_by_status& other) noexcept;
    files_by_status& operator=(files_by_status other);

private:
    std::list<boost::filesystem::path> unexpected_;
    std::list<boost::filesystem::path> ignored_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::helpers::files_by_status& lhs,
    dogen::physical::helpers::files_by_status& rhs) {
    lhs.swap(rhs);
}

}

#endif
