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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_PARENT_WITH_MEMBERS_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_PARENT_WITH_MEMBERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/parent_with_members_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class parent_with_members {
public:
    parent_with_members(const parent_with_members&) = default;
    parent_with_members(parent_with_members&&) = default;

public:
    parent_with_members();

    virtual ~parent_with_members() noexcept = 0;

public:
    explicit parent_with_members(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::parent_with_members& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::parent_with_members& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    int prop_0() const;
    void prop_0(const int v);

protected:
    bool compare(const parent_with_members& rhs) const;
public:
    virtual bool equals(const parent_with_members& other) const = 0;

protected:
    void swap(parent_with_members& other) noexcept;

private:
    int prop_0_;
};

inline parent_with_members::~parent_with_members() noexcept { }

inline bool operator==(const parent_with_members& lhs, const parent_with_members& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif
