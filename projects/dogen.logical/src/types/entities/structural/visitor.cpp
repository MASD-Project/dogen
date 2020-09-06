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
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::logical_name>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::identification::entities::logical_name>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::logical::entities::structural {

visitor::visitor(visitor&& rhs)
    : dogen::logical::entities::element(
        std::forward<dogen::logical::entities::element>(rhs)),
      visits_(std::move(rhs.visits_)),
      parent_(std::move(rhs.parent_)) { }

visitor::visitor(
    const dogen::identification::entities::logical_name& name,
    const std::string& documentation,
    const dogen::identification::entities::injection_provenance& provenance,
    const dogen::identification::entities::logical_id& contained_by,
    const bool in_global_module,
    const dogen::logical::entities::stereotypes& stereotypes,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::identification::entities::logical_name>& visits,
    const boost::optional<dogen::identification::entities::logical_name>& parent)
    : dogen::logical::entities::element(
      name,
      documentation,
      provenance,
      contained_by,
      in_global_module,
      stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      generability_status,
      decoration),
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
      << "\"__type__\": " << "\"dogen::logical::entities::structural::visitor\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"visits\": " << visits_ << ", "
      << "\"parent\": " << parent_
      << " }";
}

void visitor::swap(visitor& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(visits_, other.visits_);
    swap(parent_, other.parent_);
}

bool visitor::equals(const dogen::logical::entities::element& other) const {
    const visitor* const p(dynamic_cast<const visitor* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool visitor::operator==(const visitor& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        visits_ == rhs.visits_ &&
        parent_ == rhs.parent_;
}

visitor& visitor::operator=(visitor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::identification::entities::logical_name>& visitor::visits() const {
    return visits_;
}

std::list<dogen::identification::entities::logical_name>& visitor::visits() {
    return visits_;
}

void visitor::visits(const std::list<dogen::identification::entities::logical_name>& v) {
    visits_ = v;
}

void visitor::visits(const std::list<dogen::identification::entities::logical_name>&& v) {
    visits_ = std::move(v);
}

const boost::optional<dogen::identification::entities::logical_name>& visitor::parent() const {
    return parent_;
}

boost::optional<dogen::identification::entities::logical_name>& visitor::parent() {
    return parent_;
}

void visitor::parent(const boost::optional<dogen::identification::entities::logical_name>& v) {
    parent_ = v;
}

void visitor::parent(const boost::optional<dogen::identification::entities::logical_name>&& v) {
    parent_ = std::move(v);
}

}
