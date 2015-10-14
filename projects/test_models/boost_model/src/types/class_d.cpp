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
#include "dogen/test_models/boost_model/types/class_d.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

class_d::class_d(class_d&& rhs)
    : prop_0_(std::move(rhs.prop_0_)),
      prop_1_(std::move(rhs.prop_1_)),
      prop_2_(std::move(rhs.prop_2_)),
      prop_3_(std::move(rhs.prop_3_)) { }

class_d::class_d(
    const boost::optional<int>& prop_0,
    const boost::optional<dogen::test_models::boost_model::class_a>& prop_1,
    const boost::optional<dogen::test_models::boost_model::pkg1::class_c>& prop_2,
    const boost::optional<std::vector<dogen::test_models::boost_model::class_a> >& prop_3)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2),
      prop_3_(prop_3) { }

void class_d::swap(class_d& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
    swap(prop_3_, other.prop_3_);
}

bool class_d::operator==(const class_d& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_ &&
        prop_3_ == rhs.prop_3_;
}

class_d& class_d::operator=(class_d other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<int>& class_d::prop_0() const {
    return prop_0_;
}

boost::optional<int>& class_d::prop_0() {
    return prop_0_;
}

void class_d::prop_0(const boost::optional<int>& v) {
    prop_0_ = v;
}

void class_d::prop_0(const boost::optional<int>&& v) {
    prop_0_ = std::move(v);
}

const boost::optional<dogen::test_models::boost_model::class_a>& class_d::prop_1() const {
    return prop_1_;
}

boost::optional<dogen::test_models::boost_model::class_a>& class_d::prop_1() {
    return prop_1_;
}

void class_d::prop_1(const boost::optional<dogen::test_models::boost_model::class_a>& v) {
    prop_1_ = v;
}

void class_d::prop_1(const boost::optional<dogen::test_models::boost_model::class_a>&& v) {
    prop_1_ = std::move(v);
}

const boost::optional<dogen::test_models::boost_model::pkg1::class_c>& class_d::prop_2() const {
    return prop_2_;
}

boost::optional<dogen::test_models::boost_model::pkg1::class_c>& class_d::prop_2() {
    return prop_2_;
}

void class_d::prop_2(const boost::optional<dogen::test_models::boost_model::pkg1::class_c>& v) {
    prop_2_ = v;
}

void class_d::prop_2(const boost::optional<dogen::test_models::boost_model::pkg1::class_c>&& v) {
    prop_2_ = std::move(v);
}

const boost::optional<std::vector<dogen::test_models::boost_model::class_a> >& class_d::prop_3() const {
    return prop_3_;
}

boost::optional<std::vector<dogen::test_models::boost_model::class_a> >& class_d::prop_3() {
    return prop_3_;
}

void class_d::prop_3(const boost::optional<std::vector<dogen::test_models::boost_model::class_a> >& v) {
    prop_3_ = v;
}

void class_d::prop_3(const boost::optional<std::vector<dogen::test_models::boost_model::class_a> >&& v) {
    prop_3_ = std::move(v);
}

} } }
