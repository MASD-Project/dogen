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
#include <boost/io/ios_state.hpp>
#include "dogen/test_models/cpp_model/io/descendant1_io.hpp"
#include "dogen/test_models/cpp_model/types/descendant3.hpp"
#include "dogen/test_models/cpp_model/types/base_visitor.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

descendant3::descendant3()
    : prop_0_(static_cast<bool>(0)) { }

descendant3::descendant3(const bool prop_0)
    : dogen::test_models::cpp_model::descendant1(),
      prop_0_(prop_0) { }

void descendant3::accept(const base_visitor& v) const {
    v.visit(*this);
}

void descendant3::accept(base_visitor& v) const {
    v.visit(*this);
    }

void descendant3::accept(const base_visitor& v) {
    v.visit(*this);
}

void descendant3::accept(base_visitor& v) {
    v.visit(*this);
}

void descendant3::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::descendant3\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_model::descendant1::to_stream(s);
    s << ", "
      << "\"prop_0\": " << prop_0_
      << " }";
}

void descendant3::swap(descendant3& other) noexcept {
    dogen::test_models::cpp_model::descendant1::swap(other);

    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool descendant3::equals(const dogen::test_models::cpp_model::base& other) const {
    const descendant3* const p(dynamic_cast<const descendant3* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool descendant3::operator==(const descendant3& rhs) const {
    return dogen::test_models::cpp_model::descendant1::compare(rhs) &&
        prop_0_ == rhs.prop_0_;
}

descendant3& descendant3::operator=(descendant3 other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool descendant3::prop_0() const {
    return prop_0_;
}

void descendant3::prop_0(const bool v) {
    prop_0_ = v;
}

} } }
