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
#include "dogen/test_models/cpp_model/types/second_descendant_object_template_instance.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

second_descendant_object_template_instance::second_descendant_object_template_instance()
    : prop_2_(static_cast<int>(0)),
      prop_10_(static_cast<int>(0)) { }

second_descendant_object_template_instance::second_descendant_object_template_instance(
    const int prop_2,
    const std::string& prop_0,
    const int prop_10)
    : prop_2_(prop_2),
      prop_0_(prop_0),
      prop_10_(prop_10) { }

void second_descendant_object_template_instance::swap(second_descendant_object_template_instance& other) noexcept {
    using std::swap;
    swap(prop_2_, other.prop_2_);
    swap(prop_0_, other.prop_0_);
    swap(prop_10_, other.prop_10_);
}

bool second_descendant_object_template_instance::operator==(const second_descendant_object_template_instance& rhs) const {
    return prop_2_ == rhs.prop_2_ &&
        prop_0_ == rhs.prop_0_ &&
        prop_10_ == rhs.prop_10_;
}

second_descendant_object_template_instance& second_descendant_object_template_instance::operator=(second_descendant_object_template_instance other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int second_descendant_object_template_instance::prop_2() const {
    return prop_2_;
}

void second_descendant_object_template_instance::prop_2(const int v) {
    prop_2_ = v;
}

const std::string& second_descendant_object_template_instance::prop_0() const {
    return prop_0_;
}

std::string& second_descendant_object_template_instance::prop_0() {
    return prop_0_;
}

void second_descendant_object_template_instance::prop_0(const std::string& v) {
    prop_0_ = v;
}

void second_descendant_object_template_instance::prop_0(const std::string&& v) {
    prop_0_ = std::move(v);
}

int second_descendant_object_template_instance::prop_10() const {
    return prop_10_;
}

void second_descendant_object_template_instance::prop_10(const int v) {
    prop_10_ = v;
}

} } }
