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
#ifndef DOGEN_CPP_TYPES_SETTINGS_INCLUSION_HPP
#define DOGEN_CPP_TYPES_SETTINGS_INCLUSION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/serialization/settings/inclusion_fwd_ser.hpp"
#include "dogen/cpp/types/settings/inclusion_delimiter_types.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class inclusion final {
public:
    inclusion(const inclusion&) = default;
    ~inclusion() = default;

public:
    inclusion();

public:
    inclusion(inclusion&& rhs);

public:
    inclusion(
        const boost::filesystem::path& inclusion_path,
        const dogen::cpp::settings::inclusion_delimiter_types& inclusion_delimiter_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const inclusion& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, inclusion& v, unsigned int version);

public:
    const boost::filesystem::path& inclusion_path() const;
    boost::filesystem::path& inclusion_path();
    void inclusion_path(const boost::filesystem::path& v);
    void inclusion_path(const boost::filesystem::path&& v);

    dogen::cpp::settings::inclusion_delimiter_types inclusion_delimiter_type() const;
    void inclusion_delimiter_type(const dogen::cpp::settings::inclusion_delimiter_types& v);

public:
    bool operator==(const inclusion& rhs) const;
    bool operator!=(const inclusion& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion& other) noexcept;
    inclusion& operator=(inclusion other);

private:
    boost::filesystem::path inclusion_path_;
    dogen::cpp::settings::inclusion_delimiter_types inclusion_delimiter_type_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::inclusion& lhs,
    dogen::cpp::settings::inclusion& rhs) {
    lhs.swap(rhs);
}

}

#endif
