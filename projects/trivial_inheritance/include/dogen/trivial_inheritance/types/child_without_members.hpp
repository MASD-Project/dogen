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
#ifndef DOGEN_TRIVIAL_INHERITANCE_TYPES_CHILD_WITHOUT_MEMBERS_HPP
#define DOGEN_TRIVIAL_INHERITANCE_TYPES_CHILD_WITHOUT_MEMBERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/serialization/child_without_members_fwd_ser.hpp"
#include "dogen/trivial_inheritance/types/parent_without_members.hpp"

namespace dogen {
namespace trivial_inheritance {

class child_without_members final : public dogen::trivial_inheritance::parent_without_members {
public:
    child_without_members() = default;
    child_without_members(const child_without_members&) = default;
    child_without_members(child_without_members&&) = default;

public:
    explicit child_without_members(const dogen::trivial_inheritance::parent_without_members_versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const child_without_members& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, child_without_members& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const child_without_members& rhs) const;
    bool operator!=(const child_without_members& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::trivial_inheritance::parent_without_members& other) const override;

public:
    void swap(child_without_members& other) noexcept;
    child_without_members& operator=(child_without_members other);

};

} }

namespace std {

template<>
inline void swap(
    dogen::trivial_inheritance::child_without_members& lhs,
    dogen::trivial_inheritance::child_without_members& rhs) {
    lhs.swap(rhs);
}

}

#endif
