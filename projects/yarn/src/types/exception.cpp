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
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/element_visitor.hpp"

namespace dogen {
namespace yarn {

exception::exception(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const bool is_element_extension)
    : dogen::yarn::element(
      documentation,
      extensions,
      name,
      generation_type,
      origin_type,
      contained_by,
      in_global_module,
      is_element_extension) { }

void exception::accept(const element_visitor& v) const {
    v.visit(*this);
}

void exception::accept(element_visitor& v) const {
    v.visit(*this);
    }

void exception::accept(const element_visitor& v) {
    v.visit(*this);
}

void exception::accept(element_visitor& v) {
    v.visit(*this);
}


void exception::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::exception\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << " }";
}

void exception::swap(exception& other) noexcept {
    element::swap(other);

}

bool exception::equals(const dogen::yarn::element& other) const {
    const exception* const p(dynamic_cast<const exception* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool exception::operator==(const exception& rhs) const {
    return element::compare(rhs);
}

exception& exception::operator=(exception other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }
