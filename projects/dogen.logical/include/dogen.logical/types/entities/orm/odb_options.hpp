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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ORM_ODB_OPTIONS_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ORM_ODB_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>

namespace dogen::logical::entities::orm {

class odb_options final {
public:
    odb_options() = default;
    odb_options(const odb_options&) = default;
    odb_options(odb_options&&) = default;
    ~odb_options() = default;

public:
    odb_options(
        const std::string& epilogue,
        const std::list<std::string>& include_regexes,
        const std::string& header_guard_prefix);

public:
    const std::string& epilogue() const;
    std::string& epilogue();
    void epilogue(const std::string& v);
    void epilogue(const std::string&& v);

    const std::list<std::string>& include_regexes() const;
    std::list<std::string>& include_regexes();
    void include_regexes(const std::list<std::string>& v);
    void include_regexes(const std::list<std::string>&& v);

    const std::string& header_guard_prefix() const;
    std::string& header_guard_prefix();
    void header_guard_prefix(const std::string& v);
    void header_guard_prefix(const std::string&& v);

public:
    bool operator==(const odb_options& rhs) const;
    bool operator!=(const odb_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(odb_options& other) noexcept;
    odb_options& operator=(odb_options other);

private:
    std::string epilogue_;
    std::list<std::string> include_regexes_;
    std::string header_guard_prefix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::orm::odb_options& lhs,
    dogen::logical::entities::orm::odb_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
