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
#include <ostream>
#include "dogen/test_models/cpp_model/types/further_inherited.hpp"
#include "dogen/test_models/cpp_model/io/base_with_object_template_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

further_inherited::further_inherited()
    : prop_3_(static_cast<int>(0)),
      prop_1_(static_cast<int>(0)) { }

further_inherited::further_inherited(
    const int prop_2,
    const std::string& prop_0,
    const int prop_3,
    const int prop_1)
    : dogen::test_models::cpp_model::base_with_object_template(
      prop_2,
      prop_0),
      prop_3_(prop_3),
      prop_1_(prop_1) { }

void further_inherited::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::further_inherited\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_model::base_with_object_template::to_stream(s);
    s << ", "
      << "\"prop_3\": " << prop_3_ << ", "
      << "\"prop_1\": " << prop_1_
      << " }";
}

void further_inherited::swap(further_inherited& other) noexcept {
    dogen::test_models::cpp_model::base_with_object_template::swap(other);

    using std::swap;
    swap(prop_3_, other.prop_3_);
    swap(prop_1_, other.prop_1_);
}

bool further_inherited::equals(const dogen::test_models::cpp_model::base_with_object_template& other) const {
    const further_inherited* const p(dynamic_cast<const further_inherited* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool further_inherited::operator==(const further_inherited& rhs) const {
    return dogen::test_models::cpp_model::base_with_object_template::compare(rhs) &&
        prop_3_ == rhs.prop_3_ &&
        prop_1_ == rhs.prop_1_;
}

further_inherited& further_inherited::operator=(further_inherited other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int further_inherited::prop_3() const {
    return prop_3_;
}

void further_inherited::prop_3(const int v) {
    prop_3_ = v;
}

int further_inherited::prop_1() const {
    return prop_1_;
}

void further_inherited::prop_1(const int v) {
    prop_1_ = v;
}

} } }
