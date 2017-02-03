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
#ifndef DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_K_HPP
#define DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_K_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/std_model/types/string_primitive.hpp"
#include "dogen/test_models/std_model/serialization/class_k_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class class_k final {
public:
    class_k() = default;
    class_k(const class_k&) = default;
    class_k(class_k&&) = default;
    ~class_k() = default;

public:
    explicit class_k(const dogen::test_models::std_model::string_primitive& prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::std_model::class_k& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::std_model::class_k& v, unsigned int version);

public:
    const dogen::test_models::std_model::string_primitive& prop_0() const;
    dogen::test_models::std_model::string_primitive& prop_0();
    void prop_0(const dogen::test_models::std_model::string_primitive& v);
    void prop_0(const dogen::test_models::std_model::string_primitive&& v);

public:
    bool operator==(const class_k& rhs) const;
    bool operator!=(const class_k& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_k& other) noexcept;
    class_k& operator=(class_k other);

private:
    dogen::test_models::std_model::string_primitive prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::std_model::class_k& lhs,
    dogen::test_models::std_model::class_k& rhs) {
    lhs.swap(rhs);
}

}

#endif
