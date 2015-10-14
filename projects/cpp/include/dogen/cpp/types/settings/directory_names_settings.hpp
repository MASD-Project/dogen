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
#ifndef DOGEN_CPP_TYPES_SETTINGS_DIRECTORY_NAMES_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_DIRECTORY_NAMES_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/cpp/serialization/settings/directory_names_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class directory_names_settings final {
public:
    directory_names_settings() = default;
    directory_names_settings(const directory_names_settings&) = default;
    directory_names_settings(directory_names_settings&&) = default;
    ~directory_names_settings() = default;

public:
    directory_names_settings(
        const std::string& source_directory_name,
        const std::string& include_directory_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const directory_names_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, directory_names_settings& v, unsigned int version);

public:
    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    const std::string& include_directory_name() const;
    std::string& include_directory_name();
    void include_directory_name(const std::string& v);
    void include_directory_name(const std::string&& v);

public:
    bool operator==(const directory_names_settings& rhs) const;
    bool operator!=(const directory_names_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(directory_names_settings& other) noexcept;
    directory_names_settings& operator=(directory_names_settings other);

private:
    std::string source_directory_name_;
    std::string include_directory_name_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::directory_names_settings& lhs,
    dogen::cpp::settings::directory_names_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
