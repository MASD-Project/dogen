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
#ifndef DOGEN_QUILT_CPP_TYPES_SETTINGS_ELEMENT_SETTINGS_HPP
#define DOGEN_QUILT_CPP_TYPES_SETTINGS_ELEMENT_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/quilt.cpp/serialization/settings/element_settings_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

class element_settings final {
public:
    element_settings(const element_settings&) = default;
    element_settings(element_settings&&) = default;
    ~element_settings() = default;

public:
    element_settings();

public:
    element_settings(
        const bool disable_complete_constructor,
        const bool disable_xml_serialization);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const element_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, element_settings& v, unsigned int version);

public:
    bool disable_complete_constructor() const;
    void disable_complete_constructor(const bool v);

    bool disable_xml_serialization() const;
    void disable_xml_serialization(const bool v);

public:
    bool operator==(const element_settings& rhs) const;
    bool operator!=(const element_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_settings& other) noexcept;
    element_settings& operator=(element_settings other);

private:
    bool disable_complete_constructor_;
    bool disable_xml_serialization_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::settings::element_settings& lhs,
    dogen::quilt::cpp::settings::element_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
