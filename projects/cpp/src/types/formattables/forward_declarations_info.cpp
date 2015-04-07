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
#include <ostream>
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/types/formattables/forward_declarations_info.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

forward_declarations_info::forward_declarations_info(
    const std::string& identity,
    const std::string& name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const dogen::cpp::settings::bundle& settings)
    : dogen::cpp::formattables::entity(identity,
      name,
      documentation,
      namespaces,
      settings) { }

void forward_declarations_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::forward_declarations_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << " }";
}

void forward_declarations_info::swap(forward_declarations_info& other) noexcept {
    entity::swap(other);

}

bool forward_declarations_info::equals(const dogen::cpp::formattables::formattable& other) const {
    const forward_declarations_info* const p(dynamic_cast<const forward_declarations_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool forward_declarations_info::operator==(const forward_declarations_info& rhs) const {
    return entity::compare(rhs);
}

forward_declarations_info& forward_declarations_info::operator=(forward_declarations_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }