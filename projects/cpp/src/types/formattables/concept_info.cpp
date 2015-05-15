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
#include "dogen/cpp/types/formattables/concept_info.hpp"
#include "dogen/cpp/io/formattables/property_info_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::formattables::property_info>& v) {
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
namespace cpp {
namespace formattables {

concept_info::concept_info(
    const std::string& identity,
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const dogen::cpp::settings::bundle& settings,
    const std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties>& formatter_properties,
    const std::list<dogen::cpp::formattables::property_info>& properties,
    const std::list<dogen::cpp::formattables::property_info>& all_properties)
    : dogen::cpp::formattables::entity(identity,
      name,
      qualified_name,
      documentation,
      namespaces,
      settings,
      formatter_properties),
      properties_(properties),
      all_properties_(all_properties) { }

void concept_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::concept_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << ", "
      << "\"properties\": " << properties_ << ", "
      << "\"all_properties\": " << all_properties_
      << " }";
}

void concept_info::swap(concept_info& other) noexcept {
    entity::swap(other);

    using std::swap;
    swap(properties_, other.properties_);
    swap(all_properties_, other.all_properties_);
}

bool concept_info::equals(const dogen::cpp::formattables::formattable& other) const {
    const concept_info* const p(dynamic_cast<const concept_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool concept_info::operator==(const concept_info& rhs) const {
    return entity::compare(rhs) &&
        properties_ == rhs.properties_ &&
        all_properties_ == rhs.all_properties_;
}

concept_info& concept_info::operator=(concept_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::cpp::formattables::property_info>& concept_info::properties() const {
    return properties_;
}

std::list<dogen::cpp::formattables::property_info>& concept_info::properties() {
    return properties_;
}

void concept_info::properties(const std::list<dogen::cpp::formattables::property_info>& v) {
    properties_ = v;
}

void concept_info::properties(const std::list<dogen::cpp::formattables::property_info>&& v) {
    properties_ = std::move(v);
}

const std::list<dogen::cpp::formattables::property_info>& concept_info::all_properties() const {
    return all_properties_;
}

std::list<dogen::cpp::formattables::property_info>& concept_info::all_properties() {
    return all_properties_;
}

void concept_info::all_properties(const std::list<dogen::cpp::formattables::property_info>& v) {
    all_properties_ = v;
}

void concept_info::all_properties(const std::list<dogen::cpp::formattables::property_info>&& v) {
    all_properties_ = std::move(v);
}

} } }