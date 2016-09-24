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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_LOCAL_ENABLEMENT_CONFIGURATION_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_LOCAL_ENABLEMENT_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/quilt.cpp/serialization/formattables/local_enablement_configuration_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class local_enablement_configuration final {
public:
    local_enablement_configuration(const local_enablement_configuration&) = default;
    ~local_enablement_configuration() = default;

public:
    local_enablement_configuration();

public:
    local_enablement_configuration(local_enablement_configuration&& rhs);

public:
    local_enablement_configuration(
        const boost::optional<bool>& enabled,
        const bool supported);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::local_enablement_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::local_enablement_configuration& v, unsigned int version);

public:
    const boost::optional<bool>& enabled() const;
    boost::optional<bool>& enabled();
    void enabled(const boost::optional<bool>& v);
    void enabled(const boost::optional<bool>&& v);

    bool supported() const;
    void supported(const bool v);

public:
    bool operator==(const local_enablement_configuration& rhs) const;
    bool operator!=(const local_enablement_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(local_enablement_configuration& other) noexcept;
    local_enablement_configuration& operator=(local_enablement_configuration other);

private:
    boost::optional<bool> enabled_;
    bool supported_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::local_enablement_configuration& lhs,
    dogen::quilt::cpp::formattables::local_enablement_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
