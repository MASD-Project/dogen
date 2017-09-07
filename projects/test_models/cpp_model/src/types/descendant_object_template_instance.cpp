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
#include "dogen/test_models/cpp_model/types/descendant_object_template_instance.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

descendant_object_template_instance::descendant_object_template_instance()
    : prop_1_(static_cast<int>(0)),
      prop_0_(static_cast<int>(0)) { }

descendant_object_template_instance::descendant_object_template_instance(
    const int prop_1,
    const int prop_0)
    : prop_1_(prop_1),
      prop_0_(prop_0) { }

void descendant_object_template_instance::swap(descendant_object_template_instance& other) noexcept {
    using std::swap;
    swap(prop_1_, other.prop_1_);
    swap(prop_0_, other.prop_0_);
}

bool descendant_object_template_instance::operator==(const descendant_object_template_instance& rhs) const {
    return prop_1_ == rhs.prop_1_ &&
        prop_0_ == rhs.prop_0_;
}

descendant_object_template_instance& descendant_object_template_instance::operator=(descendant_object_template_instance other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int descendant_object_template_instance::prop_1() const {
    return prop_1_;
}

void descendant_object_template_instance::prop_1(const int v) {
    prop_1_ = v;
}

int descendant_object_template_instance::prop_0() const {
    return prop_0_;
}

void descendant_object_template_instance::prop_0(const int v) {
    prop_0_ = v;
}

} } }
