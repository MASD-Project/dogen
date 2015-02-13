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
#ifndef DOGEN_CPP_TYPES_SETTINGS_LOCAL_FACET_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_LOCAL_FACET_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/cpp/serialization/settings/local_facet_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class local_facet_settings final {
public:
    local_facet_settings(const local_facet_settings&) = default;
    local_facet_settings(local_facet_settings&&) = default;
    ~local_facet_settings() = default;

public:
    local_facet_settings();

public:
    local_facet_settings(
        const bool enabled,
        const bool supported);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const local_facet_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, local_facet_settings& v, unsigned int version);

public:
    bool enabled() const;
    void enabled(const bool v);

    bool supported() const;
    void supported(const bool v);

public:
    bool operator==(const local_facet_settings& rhs) const;
    bool operator!=(const local_facet_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(local_facet_settings& other) noexcept;
    local_facet_settings& operator=(local_facet_settings other);

private:
    bool enabled_;
    bool supported_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::local_facet_settings& lhs,
    dogen::cpp::settings::local_facet_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
