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
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/element_visitor.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

exception::exception(
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
      << "\"__type__\": " << "\"dogen::yarn::meta_model::exception\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::meta_model::element::to_stream(s);
    s << " }";
}

void exception::swap(exception& other) noexcept {
    dogen::yarn::meta_model::element::swap(other);

}

bool exception::equals(const dogen::yarn::meta_model::element& other) const {
    const exception* const p(dynamic_cast<const exception* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool exception::operator==(const exception& rhs) const {
    return dogen::yarn::meta_model::element::compare(rhs);
}

exception& exception::operator=(exception other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
