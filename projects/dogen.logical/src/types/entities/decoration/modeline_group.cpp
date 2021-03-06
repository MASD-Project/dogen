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
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/io/entities/decoration/modeline_io.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::logical_id>& v) {
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

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::decoration::modeline>& lhs,
const boost::shared_ptr<dogen::logical::entities::decoration::modeline>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::logical::entities::decoration::modeline>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::decoration {

modeline_group::modeline_group(
    const dogen::identification::entities::logical_name& name,
    const std::string& documentation,
    const dogen::identification::entities::codec_provenance& provenance,
    const dogen::identification::entities::logical_id& contained_by,
    const bool in_global_module,
    const dogen::logical::entities::stereotypes& stereotypes,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::entities::helper_properties>& helper_properties,
    const std::list<dogen::identification::entities::logical_id>& contains,
    const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modelines)
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
      decoration,
      helper_properties),
      contains_(contains),
      modelines_(modelines) { }

void modeline_group::accept(const element_visitor& v) const {
    v.visit(*this);
}

void modeline_group::accept(element_visitor& v) const {
    v.visit(*this);
    }

void modeline_group::accept(const element_visitor& v) {
    v.visit(*this);
}

void modeline_group::accept(element_visitor& v) {
    v.visit(*this);
}

void modeline_group::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::decoration::modeline_group\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"contains\": " << contains_ << ", "
      << "\"modelines\": " << modelines_
      << " }";
}

void modeline_group::swap(modeline_group& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(contains_, other.contains_);
    swap(modelines_, other.modelines_);
}

bool modeline_group::equals(const dogen::logical::entities::element& other) const {
    const modeline_group* const p(dynamic_cast<const modeline_group* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool modeline_group::operator==(const modeline_group& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        contains_ == rhs.contains_ &&
        modelines_ == rhs.modelines_;
}

modeline_group& modeline_group::operator=(modeline_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::identification::entities::logical_id>& modeline_group::contains() const {
    return contains_;
}

std::list<dogen::identification::entities::logical_id>& modeline_group::contains() {
    return contains_;
}

void modeline_group::contains(const std::list<dogen::identification::entities::logical_id>& v) {
    contains_ = v;
}

void modeline_group::contains(const std::list<dogen::identification::entities::logical_id>&& v) {
    contains_ = std::move(v);
}

const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modeline_group::modelines() const {
    return modelines_;
}

std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modeline_group::modelines() {
    return modelines_;
}

void modeline_group::modelines(const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& v) {
    modelines_ = v;
}

void modeline_group::modelines(const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >&& v) {
    modelines_ = std::move(v);
}

}
