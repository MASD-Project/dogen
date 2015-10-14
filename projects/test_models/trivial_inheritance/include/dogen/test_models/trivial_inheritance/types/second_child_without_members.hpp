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
#ifndef DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_TYPES_SECOND_CHILD_WITHOUT_MEMBERS_HPP
#define DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_TYPES_SECOND_CHILD_WITHOUT_MEMBERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/trivial_inheritance/types/parent_with_members.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/second_child_without_members_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace trivial_inheritance {

class second_child_without_members final : public dogen::test_models::trivial_inheritance::parent_with_members {
public:
    second_child_without_members() = default;
    second_child_without_members(const second_child_without_members&) = default;
    second_child_without_members(second_child_without_members&&) = default;

    virtual ~second_child_without_members() noexcept { }

public:
    explicit second_child_without_members(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const second_child_without_members& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, second_child_without_members& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const second_child_without_members& rhs) const;
    bool operator!=(const second_child_without_members& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::trivial_inheritance::parent_with_members& other) const override;

public:
    void swap(second_child_without_members& other) noexcept;
    second_child_without_members& operator=(second_child_without_members other);

};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::trivial_inheritance::second_child_without_members& lhs,
    dogen::test_models::trivial_inheritance::second_child_without_members& rhs) {
    lhs.swap(rhs);
}

}

#endif
