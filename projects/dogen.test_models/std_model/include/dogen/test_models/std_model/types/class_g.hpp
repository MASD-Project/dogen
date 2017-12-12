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
#ifndef DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_G_HPP
#define DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_G_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "dogen/test_models/std_model/types/class_a.hpp"
#include "dogen/test_models/std_model/hash/class_a_hash.hpp"
#include "dogen/test_models/std_model/types/pkg1/class_c.hpp"
#include "dogen/test_models/std_model/hash/pkg1/class_c_hash.hpp"
#include "dogen/test_models/std_model/serialization/class_g_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class class_g final {
public:
    class_g() = default;
    class_g(const class_g&) = default;
    class_g(class_g&&) = default;
    ~class_g() = default;

public:
    class_g(
        const std::unordered_map<dogen::test_models::std_model::class_a, std::vector<dogen::test_models::std_model::pkg1::class_c> >& prop_0,
        const std::unordered_map<dogen::test_models::std_model::pkg1::class_c, std::list<dogen::test_models::std_model::class_a> >& prop_1,
        const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& prop_2);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::std_model::class_g& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::std_model::class_g& v, unsigned int version);

public:
    const std::unordered_map<dogen::test_models::std_model::class_a, std::vector<dogen::test_models::std_model::pkg1::class_c> >& prop_0() const;
    std::unordered_map<dogen::test_models::std_model::class_a, std::vector<dogen::test_models::std_model::pkg1::class_c> >& prop_0();
    void prop_0(const std::unordered_map<dogen::test_models::std_model::class_a, std::vector<dogen::test_models::std_model::pkg1::class_c> >& v);
    void prop_0(const std::unordered_map<dogen::test_models::std_model::class_a, std::vector<dogen::test_models::std_model::pkg1::class_c> >&& v);

    const std::unordered_map<dogen::test_models::std_model::pkg1::class_c, std::list<dogen::test_models::std_model::class_a> >& prop_1() const;
    std::unordered_map<dogen::test_models::std_model::pkg1::class_c, std::list<dogen::test_models::std_model::class_a> >& prop_1();
    void prop_1(const std::unordered_map<dogen::test_models::std_model::pkg1::class_c, std::list<dogen::test_models::std_model::class_a> >& v);
    void prop_1(const std::unordered_map<dogen::test_models::std_model::pkg1::class_c, std::list<dogen::test_models::std_model::class_a> >&& v);

    const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& prop_2() const;
    std::unordered_map<std::string, dogen::test_models::std_model::class_a>& prop_2();
    void prop_2(const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& v);
    void prop_2(const std::unordered_map<std::string, dogen::test_models::std_model::class_a>&& v);

public:
    bool operator==(const class_g& rhs) const;
    bool operator!=(const class_g& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_g& other) noexcept;
    class_g& operator=(class_g other);

private:
    std::unordered_map<dogen::test_models::std_model::class_a, std::vector<dogen::test_models::std_model::pkg1::class_c> > prop_0_;
    std::unordered_map<dogen::test_models::std_model::pkg1::class_c, std::list<dogen::test_models::std_model::class_a> > prop_1_;
    std::unordered_map<std::string, dogen::test_models::std_model::class_a> prop_2_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::std_model::class_g& lhs,
    dogen::test_models::std_model::class_g& rhs) {
    lhs.swap(rhs);
}

}

#endif
