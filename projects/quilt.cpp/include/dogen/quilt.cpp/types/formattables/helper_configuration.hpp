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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_CONFIGURATION_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/quilt.cpp/types/formattables/helper_descriptor.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_configuration_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class helper_configuration final {
public:
    helper_configuration(const helper_configuration&) = default;
    helper_configuration(helper_configuration&&) = default;
    ~helper_configuration() = default;

public:
    helper_configuration();

public:
    helper_configuration(
        const dogen::quilt::cpp::formattables::helper_descriptor& current,
        const std::list<dogen::quilt::cpp::formattables::helper_descriptor>& direct_descendants,
        const bool in_inheritance_relationship);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::helper_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::helper_configuration& v, unsigned int version);

public:
    const dogen::quilt::cpp::formattables::helper_descriptor& current() const;
    dogen::quilt::cpp::formattables::helper_descriptor& current();
    void current(const dogen::quilt::cpp::formattables::helper_descriptor& v);
    void current(const dogen::quilt::cpp::formattables::helper_descriptor&& v);

    const std::list<dogen::quilt::cpp::formattables::helper_descriptor>& direct_descendants() const;
    std::list<dogen::quilt::cpp::formattables::helper_descriptor>& direct_descendants();
    void direct_descendants(const std::list<dogen::quilt::cpp::formattables::helper_descriptor>& v);
    void direct_descendants(const std::list<dogen::quilt::cpp::formattables::helper_descriptor>&& v);

    bool in_inheritance_relationship() const;
    void in_inheritance_relationship(const bool v);

public:
    bool operator==(const helper_configuration& rhs) const;
    bool operator!=(const helper_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_configuration& other) noexcept;
    helper_configuration& operator=(helper_configuration other);

private:
    dogen::quilt::cpp::formattables::helper_descriptor current_;
    std::list<dogen::quilt::cpp::formattables::helper_descriptor> direct_descendants_;
    bool in_inheritance_relationship_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::helper_configuration& lhs,
    dogen::quilt::cpp::formattables::helper_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
