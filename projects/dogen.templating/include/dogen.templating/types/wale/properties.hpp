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
#ifndef DOGEN_TEMPLATING_TYPES_WALE_PROPERTIES_HPP
#define DOGEN_TEMPLATING_TYPES_WALE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/filesystem/path.hpp>

namespace dogen::templating::wale {

class properties final {
public:
    properties() = default;
    properties(const properties&) = default;
    ~properties() = default;

public:
    properties(properties&& rhs);

public:
    properties(
        const boost::filesystem::path& template_path,
        const std::unordered_set<std::string>& expected_keys,
        const std::unordered_map<std::string, std::string>& supplied_kvps);

public:
    const boost::filesystem::path& template_path() const;
    boost::filesystem::path& template_path();
    void template_path(const boost::filesystem::path& v);
    void template_path(const boost::filesystem::path&& v);

    const std::unordered_set<std::string>& expected_keys() const;
    std::unordered_set<std::string>& expected_keys();
    void expected_keys(const std::unordered_set<std::string>& v);
    void expected_keys(const std::unordered_set<std::string>&& v);

    const std::unordered_map<std::string, std::string>& supplied_kvps() const;
    std::unordered_map<std::string, std::string>& supplied_kvps();
    void supplied_kvps(const std::unordered_map<std::string, std::string>& v);
    void supplied_kvps(const std::unordered_map<std::string, std::string>&& v);

public:
    bool operator==(const properties& rhs) const;
    bool operator!=(const properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(properties& other) noexcept;
    properties& operator=(properties other);

private:
    boost::filesystem::path template_path_;
    std::unordered_set<std::string> expected_keys_;
    std::unordered_map<std::string, std::string> supplied_kvps_;
};

}

namespace std {

template<>
inline void swap(
    dogen::templating::wale::properties& lhs,
    dogen::templating::wale::properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
