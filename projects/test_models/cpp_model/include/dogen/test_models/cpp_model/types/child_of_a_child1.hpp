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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHILD_OF_A_CHILD1_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHILD_OF_A_CHILD1_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/third_child_with_members.hpp"
#include "dogen/test_models/cpp_model/serialization/child_of_a_child1_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class child_of_a_child1 final : public dogen::test_models::cpp_model::third_child_with_members {
public:
    child_of_a_child1() = default;
    child_of_a_child1(const child_of_a_child1&) = default;
    child_of_a_child1(child_of_a_child1&&) = default;

    virtual ~child_of_a_child1() noexcept { }

public:
    child_of_a_child1(
        const int prop_0,
        const unsigned int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::child_of_a_child1& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::child_of_a_child1& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const child_of_a_child1& rhs) const;
    bool operator!=(const child_of_a_child1& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::cpp_model::parent_with_members& other) const override;

public:
    void swap(child_of_a_child1& other) noexcept;
    child_of_a_child1& operator=(child_of_a_child1 other);

};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::child_of_a_child1& lhs,
    dogen::test_models::cpp_model::child_of_a_child1& rhs) {
    lhs.swap(rhs);
}

}

#endif
