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
#include "dogen/boost_model/types/class_e.hpp"

namespace dogen {
namespace boost_model {

class_e::class_e(class_e&& rhs)
    : prop_0_(std::move(rhs.prop_0_)),
      prop_1_(std::move(rhs.prop_1_)),
      prop_2_(std::move(rhs.prop_2_)) { }

class_e::class_e(
    const boost::variant<int, double>& prop_0,
    const boost::variant<int, dogen::boost_model::class_derived, double>& prop_1,
    const std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >& prop_2)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2) { }

void class_e::swap(class_e& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
}

bool class_e::operator==(const class_e& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_;
}

class_e& class_e::operator=(class_e other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::variant<int, double>& class_e::prop_0() const {
    return prop_0_;
}

boost::variant<int, double>& class_e::prop_0() {
    return prop_0_;
}

void class_e::prop_0(const boost::variant<int, double>& v) {
    prop_0_ = v;
}

void class_e::prop_0(const boost::variant<int, double>&& v) {
    prop_0_ = std::move(v);
}

const boost::variant<int, dogen::boost_model::class_derived, double>& class_e::prop_1() const {
    return prop_1_;
}

boost::variant<int, dogen::boost_model::class_derived, double>& class_e::prop_1() {
    return prop_1_;
}

void class_e::prop_1(const boost::variant<int, dogen::boost_model::class_derived, double>& v) {
    prop_1_ = v;
}

void class_e::prop_1(const boost::variant<int, dogen::boost_model::class_derived, double>&& v) {
    prop_1_ = std::move(v);
}

const std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >& class_e::prop_2() const {
    return prop_2_;
}

std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >& class_e::prop_2() {
    return prop_2_;
}

void class_e::prop_2(const std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >& v) {
    prop_2_ = v;
}

void class_e::prop_2(const std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >&& v) {
    prop_2_ = std::move(v);
}

} }