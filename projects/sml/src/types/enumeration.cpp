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
#include "dogen/sml/io/type_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/enumerator_io.hpp"
#include "dogen/sml/types/enumeration.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<dogen::sml::enumerator>& v) {
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
namespace sml {

enumeration::enumeration(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type,
    const boost::optional<dogen::sml::qname>& containing_module,
    const dogen::sml::qname& underlying_type,
    const std::vector<dogen::sml::enumerator>& enumerators)
    : dogen::sml::type(documentation,
      extensions,
      name,
      generation_type,
      origin_type,
      containing_module),
      underlying_type_(underlying_type),
      enumerators_(enumerators) { }

void enumeration::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::enumeration\"" << ", "
      << "\"__parent_0__\": ";
    type::to_stream(s);
    s << ", "
      << "\"underlying_type\": " << underlying_type_ << ", "
      << "\"enumerators\": " << enumerators_
      << " }";
}

void enumeration::swap(enumeration& other) noexcept {
    type::swap(other);

    using std::swap;
    swap(underlying_type_, other.underlying_type_);
    swap(enumerators_, other.enumerators_);
}

bool enumeration::equals(const dogen::sml::type& other) const {
    const enumeration* const p(dynamic_cast<const enumeration* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool enumeration::operator==(const enumeration& rhs) const {
    return type::compare(rhs) &&
        underlying_type_ == rhs.underlying_type_ &&
        enumerators_ == rhs.enumerators_;
}

enumeration& enumeration::operator=(enumeration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::qname& enumeration::underlying_type() const {
    return underlying_type_;
}

dogen::sml::qname& enumeration::underlying_type() {
    return underlying_type_;
}

void enumeration::underlying_type(const dogen::sml::qname& v) {
    underlying_type_ = v;
}

void enumeration::underlying_type(const dogen::sml::qname&& v) {
    underlying_type_ = std::move(v);
}

const std::vector<dogen::sml::enumerator>& enumeration::enumerators() const {
    return enumerators_;
}

std::vector<dogen::sml::enumerator>& enumeration::enumerators() {
    return enumerators_;
}

void enumeration::enumerators(const std::vector<dogen::sml::enumerator>& v) {
    enumerators_ = v;
}

void enumeration::enumerators(const std::vector<dogen::sml::enumerator>&& v) {
    enumerators_ = std::move(v);
}

} }
