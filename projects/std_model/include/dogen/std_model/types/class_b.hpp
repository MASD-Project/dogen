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
#ifndef DOGEN_STD_MODEL_TYPES_CLASS_B_HPP
#define DOGEN_STD_MODEL_TYPES_CLASS_B_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <vector>
#include "dogen/std_model/serialization/class_b_fwd_ser.hpp"
#include "dogen/std_model/types/class_a.hpp"
#include "dogen/std_model/types/pkg1/class_c.hpp"

namespace dogen {
namespace std_model {

class class_b final {
public:
    class_b() = default;
    class_b(const class_b&) = default;
    class_b(class_b&&) = default;
    ~class_b() = default;

public:
    class_b(
        const std::vector<std::string>& prop_0,
        const std::vector<dogen::std_model::class_a>& prop_1,
        const std::vector<dogen::std_model::pkg1::class_c>& prop_2,
        const std::vector<unsigned int>& prop_3,
        const std::vector<dogen::std_model::class_a>& prop_4,
        const std::vector<std::vector<unsigned int> >& prop_5);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_b& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_b& v, unsigned int version);

public:
    const std::vector<std::string>& prop_0() const {
        return prop_0_;
    }

    std::vector<std::string>& prop_0() {
        return prop_0_;
    }

    void prop_0(const std::vector<std::string>& v) {
        prop_0_ = v;
    }

    void prop_0(const std::vector<std::string>&& v) {
        prop_0_ = std::move(v);
    }

    const std::vector<dogen::std_model::class_a>& prop_1() const {
        return prop_1_;
    }

    std::vector<dogen::std_model::class_a>& prop_1() {
        return prop_1_;
    }

    void prop_1(const std::vector<dogen::std_model::class_a>& v) {
        prop_1_ = v;
    }

    void prop_1(const std::vector<dogen::std_model::class_a>&& v) {
        prop_1_ = std::move(v);
    }

    const std::vector<dogen::std_model::pkg1::class_c>& prop_2() const {
        return prop_2_;
    }

    std::vector<dogen::std_model::pkg1::class_c>& prop_2() {
        return prop_2_;
    }

    void prop_2(const std::vector<dogen::std_model::pkg1::class_c>& v) {
        prop_2_ = v;
    }

    void prop_2(const std::vector<dogen::std_model::pkg1::class_c>&& v) {
        prop_2_ = std::move(v);
    }

    const std::vector<unsigned int>& prop_3() const {
        return prop_3_;
    }

    std::vector<unsigned int>& prop_3() {
        return prop_3_;
    }

    void prop_3(const std::vector<unsigned int>& v) {
        prop_3_ = v;
    }

    void prop_3(const std::vector<unsigned int>&& v) {
        prop_3_ = std::move(v);
    }

    const std::vector<dogen::std_model::class_a>& prop_4() const {
        return prop_4_;
    }

    std::vector<dogen::std_model::class_a>& prop_4() {
        return prop_4_;
    }

    void prop_4(const std::vector<dogen::std_model::class_a>& v) {
        prop_4_ = v;
    }

    void prop_4(const std::vector<dogen::std_model::class_a>&& v) {
        prop_4_ = std::move(v);
    }

    const std::vector<std::vector<unsigned int> >& prop_5() const {
        return prop_5_;
    }

    std::vector<std::vector<unsigned int> >& prop_5() {
        return prop_5_;
    }

    void prop_5(const std::vector<std::vector<unsigned int> >& v) {
        prop_5_ = v;
    }

    void prop_5(const std::vector<std::vector<unsigned int> >&& v) {
        prop_5_ = std::move(v);
    }

public:
    bool operator==(const class_b& rhs) const;
    bool operator!=(const class_b& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_b& other) noexcept;
    class_b& operator=(class_b other);

private:
    std::vector<std::string> prop_0_;
    std::vector<dogen::std_model::class_a> prop_1_;
    std::vector<dogen::std_model::pkg1::class_c> prop_2_;
    std::vector<unsigned int> prop_3_;
    std::vector<dogen::std_model::class_a> prop_4_;
    std::vector<std::vector<unsigned int> > prop_5_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::std_model::class_b& lhs,
    dogen::std_model::class_b& rhs) {
    lhs.swap(rhs);
}

}

#endif
