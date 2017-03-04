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
#include "dogen/test_models/cpp_model/io/move_ctor_base_io.hpp"
#include "dogen/test_models/cpp_model/types/move_ctor_descendant.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

move_ctor_descendant::move_ctor_descendant(move_ctor_descendant&& rhs)
    : dogen::test_models::cpp_model::move_ctor_base(
        std::forward<dogen::test_models::cpp_model::move_ctor_base>(rhs)),
      prop_1_(std::move(rhs.prop_1_)) { }

move_ctor_descendant::move_ctor_descendant(
    const boost::filesystem::path& prop_0,
    const boost::filesystem::path& prop_1)
    : dogen::test_models::cpp_model::move_ctor_base(prop_0),
      prop_1_(prop_1) { }

void move_ctor_descendant::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::move_ctor_descendant\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_model::move_ctor_base::to_stream(s);
    s << ", "
      << "\"prop_1\": " << "\"" << prop_1_.generic_string() << "\""
      << " }";
}

void move_ctor_descendant::swap(move_ctor_descendant& other) noexcept {
    dogen::test_models::cpp_model::move_ctor_base::swap(other);

    using std::swap;
    swap(prop_1_, other.prop_1_);
}

bool move_ctor_descendant::equals(const dogen::test_models::cpp_model::move_ctor_base& other) const {
    const move_ctor_descendant* const p(dynamic_cast<const move_ctor_descendant* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool move_ctor_descendant::operator==(const move_ctor_descendant& rhs) const {
    return dogen::test_models::cpp_model::move_ctor_base::compare(rhs) &&
        prop_1_ == rhs.prop_1_;
}

move_ctor_descendant& move_ctor_descendant::operator=(move_ctor_descendant other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& move_ctor_descendant::prop_1() const {
    return prop_1_;
}

boost::filesystem::path& move_ctor_descendant::prop_1() {
    return prop_1_;
}

void move_ctor_descendant::prop_1(const boost::filesystem::path& v) {
    prop_1_ = v;
}

void move_ctor_descendant::prop_1(const boost::filesystem::path&& v) {
    prop_1_ = std::move(v);
}

} } }
