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
#include "dogen/yarn/io/meta_model/element_io.hpp"
#include "dogen/quilt.csharp/types/fabric/assembly_info.hpp"
#include "dogen/quilt.csharp/types/fabric/element_visitor.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

assembly_info::assembly_info(
    const dogen::yarn::meta_model::name& name,
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::meta_model::origin_types origin_type,
    const boost::optional<dogen::yarn::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const dogen::yarn::meta_model::name& meta_name,
    const bool is_element_extension,
    const dogen::yarn::meta_model::element_properties& element_properties)
    : dogen::yarn::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      meta_name,
      is_element_extension,
      element_properties) { }

void assembly_info::accept(const dogen::yarn::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void assembly_info::accept(dogen::yarn::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void assembly_info::accept(const dogen::yarn::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void assembly_info::accept(dogen::yarn::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void assembly_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::csharp::fabric::assembly_info\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::meta_model::element::to_stream(s);
    s << " }";
}

void assembly_info::swap(assembly_info& other) noexcept {
    dogen::yarn::meta_model::element::swap(other);

}

bool assembly_info::equals(const dogen::yarn::meta_model::element& other) const {
    const assembly_info* const p(dynamic_cast<const assembly_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool assembly_info::operator==(const assembly_info& rhs) const {
    return dogen::yarn::meta_model::element::compare(rhs);
}

assembly_info& assembly_info::operator=(assembly_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } } }
