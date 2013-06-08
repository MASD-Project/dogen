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
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/module.hpp"

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

module::module(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const bool is_external,
    const std::list<dogen::sml::qname>& members)
    : dogen::sml::model_element(name,
      documentation,
      implementation_specific_parameters,
      is_external),
      members_(members) { }

void module::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::module\"" << ", "
      << "\"__parent_0__\": ";
    model_element::to_stream(s);
    s << ", "
      << "\"members\": " << members_
      << " }";
}

void module::swap(module& other) noexcept {
    model_element::swap(other);

    using std::swap;
    swap(members_, other.members_);
}

bool module::equals(const dogen::sml::model_element& other) const {
    const module* const p(dynamic_cast<const module* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool module::operator==(const module& rhs) const {
    return model_element::compare(rhs) &&
        members_ == rhs.members_;
}

module& module::operator=(module other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::sml::qname>& module::members() const {
    return members_;
}

std::list<dogen::sml::qname>& module::members() {
    return members_;
}

void module::members(const std::list<dogen::sml::qname>& v) {
    members_ = v;
}

void module::members(const std::list<dogen::sml::qname>&& v) {
    members_ = std::move(v);
}

} }