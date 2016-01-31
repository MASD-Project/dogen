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
#ifndef DOGEN_QUILT_CPP_TYPES_SETTINGS_HELPER_SETTINGS_REPOSITORY_HPP
#define DOGEN_QUILT_CPP_TYPES_SETTINGS_HELPER_SETTINGS_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/quilt.cpp/types/settings/helper_settings.hpp"
#include "dogen/quilt.cpp/serialization/settings/helper_settings_repository_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

class helper_settings_repository final {
public:
    helper_settings_repository() = default;
    helper_settings_repository(const helper_settings_repository&) = default;
    helper_settings_repository(helper_settings_repository&&) = default;
    ~helper_settings_repository() = default;

public:
    explicit helper_settings_repository(const std::unordered_map<std::string, dogen::quilt::cpp::settings::helper_settings>& helper_settings_by_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const helper_settings_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, helper_settings_repository& v, unsigned int version);

public:
    const std::unordered_map<std::string, dogen::quilt::cpp::settings::helper_settings>& helper_settings_by_name() const;
    std::unordered_map<std::string, dogen::quilt::cpp::settings::helper_settings>& helper_settings_by_name();
    void helper_settings_by_name(const std::unordered_map<std::string, dogen::quilt::cpp::settings::helper_settings>& v);
    void helper_settings_by_name(const std::unordered_map<std::string, dogen::quilt::cpp::settings::helper_settings>&& v);

public:
    bool operator==(const helper_settings_repository& rhs) const;
    bool operator!=(const helper_settings_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_settings_repository& other) noexcept;
    helper_settings_repository& operator=(helper_settings_repository other);

private:
    std::unordered_map<std::string, dogen::quilt::cpp::settings::helper_settings> helper_settings_by_name_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::settings::helper_settings_repository& lhs,
    dogen::quilt::cpp::settings::helper_settings_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
