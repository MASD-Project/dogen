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
#include "dogen/test_models/cpp_model/types/move_ctor_empty_descendant.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

move_ctor_empty_descendant::move_ctor_empty_descendant(const boost::filesystem::path& prop_0)
    : dogen::test_models::cpp_model::move_ctor_base(prop_0) { }

void move_ctor_empty_descendant::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::move_ctor_empty_descendant\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_model::move_ctor_base::to_stream(s);
    s << " }";
}

void move_ctor_empty_descendant::swap(move_ctor_empty_descendant& other) noexcept {
    dogen::test_models::cpp_model::move_ctor_base::swap(other);

}

bool move_ctor_empty_descendant::equals(const dogen::test_models::cpp_model::move_ctor_base& other) const {
    const move_ctor_empty_descendant* const p(dynamic_cast<const move_ctor_empty_descendant* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool move_ctor_empty_descendant::operator==(const move_ctor_empty_descendant& rhs) const {
    return dogen::test_models::cpp_model::move_ctor_base::compare(rhs);
}

move_ctor_empty_descendant& move_ctor_empty_descendant::operator=(move_ctor_empty_descendant other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
