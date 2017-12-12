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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHILD_VIA_SETTINGS_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHILD_VIA_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/parent_with_members.hpp"
#include "dogen/test_models/cpp_model/serialization/child_via_settings_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class child_via_settings final : public dogen::test_models::cpp_model::parent_with_members {
public:
    child_via_settings(const child_via_settings&) = default;
    child_via_settings(child_via_settings&&) = default;

public:
    child_via_settings();

    virtual ~child_via_settings() noexcept { }

public:
    child_via_settings(
        const int prop_0,
        const int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::child_via_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::child_via_settings& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    int prop_1() const;
    void prop_1(const int v);

public:
    bool operator==(const child_via_settings& rhs) const;
    bool operator!=(const child_via_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::cpp_model::parent_with_members& other) const override;

public:
    void swap(child_via_settings& other) noexcept;
    child_via_settings& operator=(child_via_settings other);

private:
    int prop_1_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::child_via_settings& lhs,
    dogen::test_models::cpp_model::child_via_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
