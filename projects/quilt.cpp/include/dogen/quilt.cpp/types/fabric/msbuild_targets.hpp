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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_MSBUILD_TARGETS_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_MSBUILD_TARGETS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/quilt.cpp/types/fabric/odb_target.hpp"
#include "dogen/quilt.cpp/serialization/fabric/msbuild_targets_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class msbuild_targets final {
public:
    msbuild_targets() = default;
    msbuild_targets(const msbuild_targets&) = default;
    msbuild_targets(msbuild_targets&&) = default;
    ~msbuild_targets() = default;

public:
    explicit msbuild_targets(const std::list<dogen::quilt::cpp::fabric::odb_target>& odb_targets);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::msbuild_targets& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::msbuild_targets& v, unsigned int version);

public:
    const std::list<dogen::quilt::cpp::fabric::odb_target>& odb_targets() const;
    std::list<dogen::quilt::cpp::fabric::odb_target>& odb_targets();
    void odb_targets(const std::list<dogen::quilt::cpp::fabric::odb_target>& v);
    void odb_targets(const std::list<dogen::quilt::cpp::fabric::odb_target>&& v);

public:
    bool operator==(const msbuild_targets& rhs) const;
    bool operator!=(const msbuild_targets& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(msbuild_targets& other) noexcept;
    msbuild_targets& operator=(msbuild_targets other);

private:
    std::list<dogen::quilt::cpp::fabric::odb_target> odb_targets_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::msbuild_targets& lhs,
    dogen::quilt::cpp::fabric::msbuild_targets& rhs) {
    lhs.swap(rhs);
}

}

#endif
