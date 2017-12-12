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
#include "dogen/test_models/boost_model/types/class_a.hpp"
#include "dogen/test_models/boost_model/types/class_b.hpp"
#include "dogen/test_models/boost_model/types/class_base.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::test_models::boost_model::class_a>& lhs,
const boost::shared_ptr<dogen::test_models::boost_model::class_a>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c>& lhs,
const boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::test_models::boost_model::class_base>& lhs,
const boost::shared_ptr<dogen::test_models::boost_model::class_base>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

class_b::class_b(
    const boost::shared_ptr<dogen::test_models::boost_model::class_a>& prop_0,
    const std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_a> >& prop_1,
    const std::unordered_map<int, boost::shared_ptr<dogen::test_models::boost_model::class_a> >& prop_2,
    const boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c>& prop_3,
    const boost::shared_ptr<dogen::test_models::boost_model::class_base>& prop_4,
    const std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_base> >& prop_5,
    const dogen::test_models::boost_model::pkg1::class_c& prop_6)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2),
      prop_3_(prop_3),
      prop_4_(prop_4),
      prop_5_(prop_5),
      prop_6_(prop_6) { }

void class_b::swap(class_b& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
    swap(prop_3_, other.prop_3_);
    swap(prop_4_, other.prop_4_);
    swap(prop_5_, other.prop_5_);
    swap(prop_6_, other.prop_6_);
}

bool class_b::operator==(const class_b& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_ &&
        prop_3_ == rhs.prop_3_ &&
        prop_4_ == rhs.prop_4_ &&
        prop_5_ == rhs.prop_5_ &&
        prop_6_ == rhs.prop_6_;
}

class_b& class_b::operator=(class_b other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::test_models::boost_model::class_a>& class_b::prop_0() const {
    return prop_0_;
}

boost::shared_ptr<dogen::test_models::boost_model::class_a>& class_b::prop_0() {
    return prop_0_;
}

void class_b::prop_0(const boost::shared_ptr<dogen::test_models::boost_model::class_a>& v) {
    prop_0_ = v;
}

void class_b::prop_0(const boost::shared_ptr<dogen::test_models::boost_model::class_a>&& v) {
    prop_0_ = std::move(v);
}

const std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_a> >& class_b::prop_1() const {
    return prop_1_;
}

std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_a> >& class_b::prop_1() {
    return prop_1_;
}

void class_b::prop_1(const std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_a> >& v) {
    prop_1_ = v;
}

void class_b::prop_1(const std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_a> >&& v) {
    prop_1_ = std::move(v);
}

const std::unordered_map<int, boost::shared_ptr<dogen::test_models::boost_model::class_a> >& class_b::prop_2() const {
    return prop_2_;
}

std::unordered_map<int, boost::shared_ptr<dogen::test_models::boost_model::class_a> >& class_b::prop_2() {
    return prop_2_;
}

void class_b::prop_2(const std::unordered_map<int, boost::shared_ptr<dogen::test_models::boost_model::class_a> >& v) {
    prop_2_ = v;
}

void class_b::prop_2(const std::unordered_map<int, boost::shared_ptr<dogen::test_models::boost_model::class_a> >&& v) {
    prop_2_ = std::move(v);
}

const boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c>& class_b::prop_3() const {
    return prop_3_;
}

boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c>& class_b::prop_3() {
    return prop_3_;
}

void class_b::prop_3(const boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c>& v) {
    prop_3_ = v;
}

void class_b::prop_3(const boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c>&& v) {
    prop_3_ = std::move(v);
}

const boost::shared_ptr<dogen::test_models::boost_model::class_base>& class_b::prop_4() const {
    return prop_4_;
}

boost::shared_ptr<dogen::test_models::boost_model::class_base>& class_b::prop_4() {
    return prop_4_;
}

void class_b::prop_4(const boost::shared_ptr<dogen::test_models::boost_model::class_base>& v) {
    prop_4_ = v;
}

void class_b::prop_4(const boost::shared_ptr<dogen::test_models::boost_model::class_base>&& v) {
    prop_4_ = std::move(v);
}

const std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_base> >& class_b::prop_5() const {
    return prop_5_;
}

std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_base> >& class_b::prop_5() {
    return prop_5_;
}

void class_b::prop_5(const std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_base> >& v) {
    prop_5_ = v;
}

void class_b::prop_5(const std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_base> >&& v) {
    prop_5_ = std::move(v);
}

const dogen::test_models::boost_model::pkg1::class_c& class_b::prop_6() const {
    return prop_6_;
}

dogen::test_models::boost_model::pkg1::class_c& class_b::prop_6() {
    return prop_6_;
}

void class_b::prop_6(const dogen::test_models::boost_model::pkg1::class_c& v) {
    prop_6_ = v;
}

void class_b::prop_6(const dogen::test_models::boost_model::pkg1::class_c&& v) {
    prop_6_ = std::move(v);
}

} } }
