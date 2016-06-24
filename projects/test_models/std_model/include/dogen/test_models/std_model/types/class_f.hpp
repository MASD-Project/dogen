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
#ifndef DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_F_HPP
#define DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_F_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/test_models/std_model/types/class_a.hpp"
#include "dogen/test_models/std_model/hash/class_a_hash.hpp"
#include "dogen/test_models/std_model/types/pkg1/class_c.hpp"
#include "dogen/test_models/std_model/serialization/class_f_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class class_f final {
public:
    class_f() = default;
    class_f(const class_f&) = default;
    class_f(class_f&&) = default;
    ~class_f() = default;

public:
    class_f(
        const std::unordered_map<std::string, std::string>& prop_0,
        const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& prop_1,
        const std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>& prop_2);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::std_model::class_f& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::std_model::class_f& v, unsigned int version);

public:
    const std::unordered_map<std::string, std::string>& prop_0() const;
    std::unordered_map<std::string, std::string>& prop_0();
    void prop_0(const std::unordered_map<std::string, std::string>& v);
    void prop_0(const std::unordered_map<std::string, std::string>&& v);

    const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& prop_1() const;
    std::unordered_map<std::string, dogen::test_models::std_model::class_a>& prop_1();
    void prop_1(const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& v);
    void prop_1(const std::unordered_map<std::string, dogen::test_models::std_model::class_a>&& v);

    const std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>& prop_2() const;
    std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>& prop_2();
    void prop_2(const std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>& v);
    void prop_2(const std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>&& v);

public:
    bool operator==(const class_f& rhs) const;
    bool operator!=(const class_f& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_f& other) noexcept;
    class_f& operator=(class_f other);

private:
    std::unordered_map<std::string, std::string> prop_0_;
    std::unordered_map<std::string, dogen::test_models::std_model::class_a> prop_1_;
    std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c> prop_2_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::std_model::class_f& lhs,
    dogen::test_models::std_model::class_f& rhs) {
    lhs.swap(rhs);
}

}

#endif
