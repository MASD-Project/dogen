/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_FILE_SETTINGS_HPP
#define DOGEN_CPP_TYPES_FILE_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/serialization/file_settings_fwd_ser.hpp"
#include "dogen/cpp/types/includes.hpp"

namespace dogen {
namespace cpp {

class file_settings final {
public:
    file_settings() = default;
    file_settings(const file_settings&) = default;
    ~file_settings() = default;

public:
    file_settings(file_settings&& rhs);

public:
    file_settings(
        const boost::filesystem::path& relative_path,
        const dogen::cpp::includes& includes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const file_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, file_settings& v, unsigned int version);

public:
    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);

    const dogen::cpp::includes& includes() const;
    dogen::cpp::includes& includes();
    void includes(const dogen::cpp::includes& v);
    void includes(const dogen::cpp::includes&& v);

public:
    bool operator==(const file_settings& rhs) const;
    bool operator!=(const file_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file_settings& other) noexcept;
    file_settings& operator=(file_settings other);

private:
    boost::filesystem::path relative_path_;
    dogen::cpp::includes includes_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::file_settings& lhs,
    dogen::cpp::file_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
