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
#include "dogen/sml/io/model_element_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/concept.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::property>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::qname>& v) {
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

concept::concept(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const dogen::sml::generation_types& generation_type,
    const std::list<dogen::sml::property>& properties,
    const std::list<dogen::sml::qname>& refines)
    : dogen::sml::model_element(name,
      documentation,
      implementation_specific_parameters,
      generation_type),
      properties_(properties),
      refines_(refines) { }

void concept::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::concept\"" << ", "
      << "\"__parent_0__\": ";
    model_element::to_stream(s);
    s << ", "
      << "\"properties\": " << properties_ << ", "
      << "\"refines\": " << refines_
      << " }";
}

void concept::swap(concept& other) noexcept {
    model_element::swap(other);

    using std::swap;
    swap(properties_, other.properties_);
    swap(refines_, other.refines_);
}

bool concept::equals(const dogen::sml::model_element& other) const {
    const concept* const p(dynamic_cast<const concept* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool concept::operator==(const concept& rhs) const {
    return model_element::compare(rhs) &&
        properties_ == rhs.properties_ &&
        refines_ == rhs.refines_;
}

concept& concept::operator=(concept other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::sml::property>& concept::properties() const {
    return properties_;
}

std::list<dogen::sml::property>& concept::properties() {
    return properties_;
}

void concept::properties(const std::list<dogen::sml::property>& v) {
    properties_ = v;
}

void concept::properties(const std::list<dogen::sml::property>&& v) {
    properties_ = std::move(v);
}

const std::list<dogen::sml::qname>& concept::refines() const {
    return refines_;
}

std::list<dogen::sml::qname>& concept::refines() {
    return refines_;
}

void concept::refines(const std::list<dogen::sml::qname>& v) {
    refines_ = v;
}

void concept::refines(const std::list<dogen::sml::qname>&& v) {
    refines_ = std::move(v);
}

} }