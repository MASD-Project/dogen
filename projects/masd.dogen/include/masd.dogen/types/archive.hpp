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
#ifndef MASD_DOGEN_TYPES_ARCHIVE_HPP
#define MASD_DOGEN_TYPES_ARCHIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "masd.dogen/types/archive_type.hpp"

namespace masd::dogen {

class archive final {
public:
    archive(const archive&) = default;
    archive(archive&&) = default;
    ~archive() = default;

public:
    archive();

public:
    archive(
        const std::string& content,
        const masd::dogen::archive_type type);

public:
    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);

    masd::dogen::archive_type type() const;
    void type(const masd::dogen::archive_type v);

public:
    bool operator==(const archive& rhs) const;
    bool operator!=(const archive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archive& other) noexcept;
    archive& operator=(archive other);

private:
    std::string content_;
    masd::dogen::archive_type type_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::archive& lhs,
    masd::dogen::archive& rhs) {
    lhs.swap(rhs);
}

}

#endif
