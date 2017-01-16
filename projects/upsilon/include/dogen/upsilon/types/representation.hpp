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
#ifndef DOGEN_UPSILON_TYPES_REPRESENTATION_HPP
#define DOGEN_UPSILON_TYPES_REPRESENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include "dogen/upsilon/types/exclusion.hpp"
#include "dogen/upsilon/types/target_types.hpp"
#include "dogen/upsilon/serialization/representation_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class representation final {
public:
    representation(const representation&) = default;
    representation(representation&&) = default;
    ~representation() = default;

public:
    representation();

public:
    representation(
        const dogen::upsilon::target_types target,
        const bool pof,
        const std::vector<dogen::upsilon::exclusion>& exclusions);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::representation& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::representation& v, unsigned int version);

public:
    dogen::upsilon::target_types target() const;
    void target(const dogen::upsilon::target_types v);

    bool pof() const;
    void pof(const bool v);

    const std::vector<dogen::upsilon::exclusion>& exclusions() const;
    std::vector<dogen::upsilon::exclusion>& exclusions();
    void exclusions(const std::vector<dogen::upsilon::exclusion>& v);
    void exclusions(const std::vector<dogen::upsilon::exclusion>&& v);

public:
    bool operator==(const representation& rhs) const;
    bool operator!=(const representation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(representation& other) noexcept;
    representation& operator=(representation other);

private:
    dogen::upsilon::target_types target_;
    bool pof_;
    std::vector<dogen::upsilon::exclusion> exclusions_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::representation& lhs,
    dogen::upsilon::representation& rhs) {
    lhs.swap(rhs);
}

}

#endif
