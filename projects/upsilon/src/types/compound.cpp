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
#include "dogen/upsilon/io/type_io.hpp"
#include "dogen/upsilon/io/field_io.hpp"
#include "dogen/upsilon/types/compound.hpp"
#include "dogen/upsilon/types/type_visitor.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<dogen::upsilon::field>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace upsilon {

compound::compound(
    const std::string& name,
    const std::string& extends,
    const std::string& comment,
    const std::vector<std::string>& tag_refs,
    const std::string& pof_id,
    const std::vector<dogen::upsilon::field>& fields)
    : dogen::upsilon::type(
      name,
      extends,
      comment,
      tag_refs,
      pof_id),
      fields_(fields) { }

void compound::accept(const type_visitor& v) const {
    v.visit(*this);
}

void compound::accept(type_visitor& v) const {
    v.visit(*this);
    }

void compound::accept(const type_visitor& v) {
    v.visit(*this);
}

void compound::accept(type_visitor& v) {
    v.visit(*this);
}

void compound::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::upsilon::compound\"" << ", "
      << "\"__parent_0__\": ";
    dogen::upsilon::type::to_stream(s);
    s << ", "
      << "\"fields\": " << fields_
      << " }";
}

void compound::swap(compound& other) noexcept {
    dogen::upsilon::type::swap(other);

    using std::swap;
    swap(fields_, other.fields_);
}

bool compound::equals(const dogen::upsilon::type& other) const {
    const compound* const p(dynamic_cast<const compound* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool compound::operator==(const compound& rhs) const {
    return dogen::upsilon::type::compare(rhs) &&
        fields_ == rhs.fields_;
}

compound& compound::operator=(compound other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<dogen::upsilon::field>& compound::fields() const {
    return fields_;
}

std::vector<dogen::upsilon::field>& compound::fields() {
    return fields_;
}

void compound::fields(const std::vector<dogen::upsilon::field>& v) {
    fields_ = v;
}

void compound::fields(const std::vector<dogen::upsilon::field>&& v) {
    fields_ = std::move(v);
}

} }
