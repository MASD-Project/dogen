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
#include "dogen/test_models/boost_model/types/class_g.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

class_g::class_g(class_g&& rhs)
    : prop_0_(std::move(rhs.prop_0_)),
      prop_1_(std::move(rhs.prop_1_)) { }

class_g::class_g(
    const boost::filesystem::path& prop_0,
    const std::list<boost::filesystem::path>& prop_1)
    : prop_0_(prop_0),
      prop_1_(prop_1) { }

void class_g::swap(class_g& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
}

bool class_g::operator==(const class_g& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_;
}

class_g& class_g::operator=(class_g other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& class_g::prop_0() const {
    return prop_0_;
}

boost::filesystem::path& class_g::prop_0() {
    return prop_0_;
}

void class_g::prop_0(const boost::filesystem::path& v) {
    prop_0_ = v;
}

void class_g::prop_0(const boost::filesystem::path&& v) {
    prop_0_ = std::move(v);
}

const std::list<boost::filesystem::path>& class_g::prop_1() const {
    return prop_1_;
}

std::list<boost::filesystem::path>& class_g::prop_1() {
    return prop_1_;
}

void class_g::prop_1(const std::list<boost::filesystem::path>& v) {
    prop_1_ = v;
}

void class_g::prop_1(const std::list<boost::filesystem::path>&& v) {
    prop_1_ = std::move(v);
}

} } }
