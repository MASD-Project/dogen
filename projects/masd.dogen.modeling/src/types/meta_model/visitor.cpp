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
#include "dogen.modeling/io/meta_model/name_io.hpp"
#include "dogen.modeling/io/meta_model/element_io.hpp"
#include "dogen.modeling/types/meta_model/visitor.hpp"
#include "dogen.modeling/types/meta_model/element_visitor.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::modeling::meta_model::name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::modeling::meta_model::name>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::modeling::meta_model {

visitor::visitor(visitor&& rhs)
    : dogen::modeling::meta_model::element(
        std::forward<dogen::modeling::meta_model::element>(rhs)),
      visits_(std::move(rhs.visits_)),
      parent_(std::move(rhs.parent_)) { }

visitor::visitor(
    const dogen::modeling::meta_model::name& name,
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::modeling::meta_model::origin_types origin_type,
    const boost::optional<dogen::modeling::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<dogen::modeling::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::modeling::meta_model::name& meta_name,
    const bool is_element_extension,
    const dogen::formatting::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& opaque_properties,
    const std::list<dogen::modeling::meta_model::name>& visits,
    const boost::optional<dogen::modeling::meta_model::name>& parent)
    : dogen::modeling::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties,
      opaque_properties),
      visits_(visits),
      parent_(parent) { }

void visitor::accept(const element_visitor& v) const {
    v.visit(*this);
}

void visitor::accept(element_visitor& v) const {
    v.visit(*this);
    }

void visitor::accept(const element_visitor& v) {
    v.visit(*this);
}

void visitor::accept(element_visitor& v) {
    v.visit(*this);
}

void visitor::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::modeling::meta_model::visitor\"" << ", "
      << "\"__parent_0__\": ";
    dogen::modeling::meta_model::element::to_stream(s);
    s << ", "
      << "\"visits\": " << visits_ << ", "
      << "\"parent\": " << parent_
      << " }";
}

void visitor::swap(visitor& other) noexcept {
    dogen::modeling::meta_model::element::swap(other);

    using std::swap;
    swap(visits_, other.visits_);
    swap(parent_, other.parent_);
}

bool visitor::equals(const dogen::modeling::meta_model::element& other) const {
    const visitor* const p(dynamic_cast<const visitor* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool visitor::operator==(const visitor& rhs) const {
    return dogen::modeling::meta_model::element::compare(rhs) &&
        visits_ == rhs.visits_ &&
        parent_ == rhs.parent_;
}

visitor& visitor::operator=(visitor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::modeling::meta_model::name>& visitor::visits() const {
    return visits_;
}

std::list<dogen::modeling::meta_model::name>& visitor::visits() {
    return visits_;
}

void visitor::visits(const std::list<dogen::modeling::meta_model::name>& v) {
    visits_ = v;
}

void visitor::visits(const std::list<dogen::modeling::meta_model::name>&& v) {
    visits_ = std::move(v);
}

const boost::optional<dogen::modeling::meta_model::name>& visitor::parent() const {
    return parent_;
}

boost::optional<dogen::modeling::meta_model::name>& visitor::parent() {
    return parent_;
}

void visitor::parent(const boost::optional<dogen::modeling::meta_model::name>& v) {
    parent_ = v;
}

void visitor::parent(const boost::optional<dogen::modeling::meta_model::name>&& v) {
    parent_ = std::move(v);
}

}
