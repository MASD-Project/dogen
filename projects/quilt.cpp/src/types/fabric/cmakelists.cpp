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
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

cmakelists::cmakelists(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::unordered_set<dogen::yarn::stereotypes>& stereotypes,
    const bool is_element_extension)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      generation_type,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension) { }

void cmakelists::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void cmakelists::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}


void cmakelists::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::cmakelists\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << " }";
}

void cmakelists::swap(cmakelists& other) noexcept {
    element::swap(other);

}

bool cmakelists::equals(const dogen::yarn::element& other) const {
    const cmakelists* const p(dynamic_cast<const cmakelists* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cmakelists::operator==(const cmakelists& rhs) const {
    return element::compare(rhs);
}

cmakelists& cmakelists::operator=(cmakelists other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } } }
