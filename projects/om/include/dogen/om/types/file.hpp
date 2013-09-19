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
#ifndef DOGEN_OM_TYPES_FILE_HPP
#define DOGEN_OM_TYPES_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <string>
#include "dogen/om/serialization/file_fwd_ser.hpp"

namespace dogen {
namespace om {

/**
 * @brief File produced by a formatter.
 */
class file final {
public:
    file() = default;
    file(const file&) = default;
    ~file() = default;

public:
    file(file&& rhs);

public:
    file(
        const boost::filesystem::path& full_path,
        const std::string& contents);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const file& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, file& v, unsigned int version);

public:
    const boost::filesystem::path& full_path() const;
    boost::filesystem::path& full_path();
    void full_path(const boost::filesystem::path& v);
    void full_path(const boost::filesystem::path&& v);

    const std::string& contents() const;
    std::string& contents();
    void contents(const std::string& v);
    void contents(const std::string&& v);

public:
    bool operator==(const file& rhs) const;
    bool operator!=(const file& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file& other) noexcept;
    file& operator=(file other);

private:
    boost::filesystem::path full_path_;
    std::string contents_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::file& lhs,
    dogen::om::file& rhs) {
    lhs.swap(rhs);
}

}

#endif
