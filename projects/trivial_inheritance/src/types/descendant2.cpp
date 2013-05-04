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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/trivial_inheritance/io/base_io.hpp"
#include "dogen/trivial_inheritance/types/descendant2.hpp"

namespace dogen {
namespace trivial_inheritance {

descendant2::descendant2()
    : prop_0_(static_cast<bool>(0)) { }

descendant2::descendant2(const bool prop_0)
    : dogen::trivial_inheritance::base(),
      prop_0_(prop_0) { }

void descendant2::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::trivial_inheritance::descendant2\"" << ", "
      << "\"__parent_0__\": ";
    base::to_stream(s);
    s << ", "
      << "\"prop_0\": " << prop_0_
      << " }";
}

void descendant2::swap(descendant2& other) noexcept {
    base::swap(other);

    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool descendant2::equals(const dogen::trivial_inheritance::base& other) const {
    const descendant2* const p(dynamic_cast<const descendant2* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool descendant2::operator==(const descendant2& rhs) const {
    return base::compare(rhs) &&
        prop_0_ == rhs.prop_0_;
}

descendant2& descendant2::operator=(descendant2 other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool descendant2::prop_0() const {
    return prop_0_;
}

void descendant2::prop_0(const bool v) {
    prop_0_ = v;
}

} }