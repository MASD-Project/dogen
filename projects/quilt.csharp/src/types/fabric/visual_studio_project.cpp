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
#include "dogen/quilt.csharp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.csharp/types/fabric/visual_studio_project.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

visual_studio_project::visual_studio_project(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const bool is_element_extension)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension) { }

void visual_studio_project::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void visual_studio_project::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void visual_studio_project::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void visual_studio_project::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}


void visual_studio_project::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::csharp::fabric::visual_studio_project\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << " }";
}

void visual_studio_project::swap(visual_studio_project& other) noexcept {
    element::swap(other);

}

bool visual_studio_project::equals(const dogen::yarn::element& other) const {
    const visual_studio_project* const p(dynamic_cast<const visual_studio_project* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool visual_studio_project::operator==(const visual_studio_project& rhs) const {
    return element::compare(rhs);
}

visual_studio_project& visual_studio_project::operator=(visual_studio_project other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } } }
