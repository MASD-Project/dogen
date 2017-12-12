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
#include "dogen/test_models/cpp_model/types/move_ctor_base.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

move_ctor_base::move_ctor_base(move_ctor_base&& rhs)
    : prop_0_(std::move(rhs.prop_0_)) { }

move_ctor_base::move_ctor_base(const boost::filesystem::path& prop_0)
    : prop_0_(prop_0) { }

void move_ctor_base::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::move_ctor_base\"" << ", "
      << "\"prop_0\": " << "\"" << prop_0_.generic_string() << "\""
      << " }";
}

void move_ctor_base::swap(move_ctor_base& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool move_ctor_base::compare(const move_ctor_base& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

const boost::filesystem::path& move_ctor_base::prop_0() const {
    return prop_0_;
}

boost::filesystem::path& move_ctor_base::prop_0() {
    return prop_0_;
}

void move_ctor_base::prop_0(const boost::filesystem::path& v) {
    prop_0_ = v;
}

void move_ctor_base::prop_0(const boost::filesystem::path&& v) {
    prop_0_ = std::move(v);
}

} } }
