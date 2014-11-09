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
#ifndef DOGEN_CPP_TYPES_PATH_SPEC_DETAILS_HPP
#define DOGEN_CPP_TYPES_PATH_SPEC_DETAILS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/serialization/path_spec_details_fwd_ser.hpp"
#include "dogen/cpp/types/includes.hpp"

namespace dogen {
namespace cpp {

class path_spec_details final {
public:
    path_spec_details() = default;
    path_spec_details(const path_spec_details&) = default;
    ~path_spec_details() = default;

public:
    path_spec_details(path_spec_details&& rhs);

public:
    path_spec_details(
        const boost::filesystem::path& relative_path,
        const dogen::cpp::includes& includes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const path_spec_details& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, path_spec_details& v, unsigned int version);

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
    bool operator==(const path_spec_details& rhs) const;
    bool operator!=(const path_spec_details& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_spec_details& other) noexcept;
    path_spec_details& operator=(path_spec_details other);

private:
    boost::filesystem::path relative_path_;
    dogen::cpp::includes includes_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::path_spec_details& lhs,
    dogen::cpp::path_spec_details& rhs) {
    lhs.swap(rhs);
}

}

#endif
