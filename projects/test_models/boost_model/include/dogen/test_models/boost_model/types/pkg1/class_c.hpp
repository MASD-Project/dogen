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
#ifndef DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_PKG1_CLASS_C_HPP
#define DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_PKG1_CLASS_C_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include "dogen/test_models/boost_model/types/class_a.hpp"
#include "dogen/test_models/boost_model/serialization/pkg1/class_c_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {
namespace pkg1 {

class class_c final {
public:
    class_c(const class_c&) = default;
    class_c(class_c&&) = default;
    ~class_c() = default;

public:
    class_c();

public:
    class_c(
        const int prop_0,
        const std::vector<dogen::test_models::boost_model::class_a>& prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::boost_model::pkg1::class_c& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::boost_model::pkg1::class_c& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

    const std::vector<dogen::test_models::boost_model::class_a>& prop_1() const;
    std::vector<dogen::test_models::boost_model::class_a>& prop_1();
    void prop_1(const std::vector<dogen::test_models::boost_model::class_a>& v);
    void prop_1(const std::vector<dogen::test_models::boost_model::class_a>&& v);

public:
    bool operator==(const class_c& rhs) const;
    bool operator!=(const class_c& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_c& other) noexcept;
    class_c& operator=(class_c other);

private:
    int prop_0_;
    std::vector<dogen::test_models::boost_model::class_a> prop_1_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::test_models::boost_model::pkg1::class_c& lhs,
    dogen::test_models::boost_model::pkg1::class_c& rhs) {
    lhs.swap(rhs);
}

}

#endif
