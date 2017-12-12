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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHILD_WITH_MEMBERS_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHILD_WITH_MEMBERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/parent_without_members.hpp"
#include "dogen/test_models/cpp_model/serialization/child_with_members_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class child_with_members final : public dogen::test_models::cpp_model::parent_without_members {
public:
    child_with_members(const child_with_members&) = default;
    child_with_members(child_with_members&&) = default;

public:
    child_with_members();

    virtual ~child_with_members() noexcept { }

public:
    explicit child_with_members(const unsigned int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::child_with_members& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::child_with_members& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    unsigned int prop_0() const;
    void prop_0(const unsigned int v);

public:
    bool operator==(const child_with_members& rhs) const;
    bool operator!=(const child_with_members& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::cpp_model::parent_without_members& other) const override;

public:
    void swap(child_with_members& other) noexcept;
    child_with_members& operator=(child_with_members other);

private:
    unsigned int prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::child_with_members& lhs,
    dogen::test_models::cpp_model::child_with_members& rhs) {
    lhs.swap(rhs);
}

}

#endif
