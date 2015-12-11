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
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/yarn/types/visitor.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::yarn::name>& v) {
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
namespace yarn {

visitor::visitor(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const std::string& original_model_name,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::list<dogen::yarn::name>& visits)
    : dogen::yarn::element(
      documentation,
      extensions,
      name,
      generation_type,
      origin_type,
      original_model_name,
      contained_by,
      in_global_module),
      visits_(visits) { }

void visitor::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::visitor\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << ", "
      << "\"visits\": " << visits_
      << " }";
}

void visitor::swap(visitor& other) noexcept {
    element::swap(other);

    using std::swap;
    swap(visits_, other.visits_);
}

bool visitor::equals(const dogen::yarn::element& other) const {
    const visitor* const p(dynamic_cast<const visitor* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool visitor::operator==(const visitor& rhs) const {
    return element::compare(rhs) &&
        visits_ == rhs.visits_;
}

visitor& visitor::operator=(visitor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::yarn::name>& visitor::visits() const {
    return visits_;
}

std::list<dogen::yarn::name>& visitor::visits() {
    return visits_;
}

void visitor::visits(const std::list<dogen::yarn::name>& v) {
    visits_ = v;
}

void visitor::visits(const std::list<dogen::yarn::name>&& v) {
    visits_ = std::move(v);
}

} }
