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
#ifndef DOGEN_CPP_TYPES_SETTINGS_LOCAL_FORMATTER_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_LOCAL_FORMATTER_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/serialization/settings/local_formatter_settings_fwd_ser.hpp"
#include "dogen/cpp/types/formattables/inclusion_delimiter_types.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class local_formatter_settings final {
public:
    local_formatter_settings(const local_formatter_settings&) = default;
    ~local_formatter_settings() = default;

public:
    local_formatter_settings();

public:
    local_formatter_settings(local_formatter_settings&& rhs);

public:
    local_formatter_settings(
        const bool enabled,
        const boost::filesystem::path& inclusion_path,
        const dogen::cpp::formattables::inclusion_delimiter_types& inclusion_delimiter_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const local_formatter_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, local_formatter_settings& v, unsigned int version);

public:
    bool enabled() const;
    void enabled(const bool v);

    const boost::filesystem::path& inclusion_path() const;
    boost::filesystem::path& inclusion_path();
    void inclusion_path(const boost::filesystem::path& v);
    void inclusion_path(const boost::filesystem::path&& v);

    dogen::cpp::formattables::inclusion_delimiter_types inclusion_delimiter_type() const;
    void inclusion_delimiter_type(const dogen::cpp::formattables::inclusion_delimiter_types& v);

public:
    bool operator==(const local_formatter_settings& rhs) const;
    bool operator!=(const local_formatter_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(local_formatter_settings& other) noexcept;
    local_formatter_settings& operator=(local_formatter_settings other);

private:
    bool enabled_;
    boost::filesystem::path inclusion_path_;
    dogen::cpp::formattables::inclusion_delimiter_types inclusion_delimiter_type_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::local_formatter_settings& lhs,
    dogen::cpp::settings::local_formatter_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
