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
#include <boost/io/ios_state.hpp>
#include "masd.dogen.coding/io/meta_model/name_io.hpp"
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.generation.cpp/types/fabric/element_visitor.hpp"
#include "masd.dogen.generation.cpp/types/fabric/forward_declarations.hpp"

namespace masd::dogen::generation::cpp::fabric {

forward_declarations::forward_declarations()
    : is_enum_(static_cast<bool>(0)),
      is_exception_(static_cast<bool>(0)) { }

forward_declarations::forward_declarations(
    const masd::dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const boost::optional<masd::dogen::coding::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::coding::meta_model::name& meta_name,
    const masd::dogen::coding::meta_model::technical_space intrinsic_technical_space,
    const bool is_element_extension,
    const masd::dogen::extraction::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<masd::dogen::coding::meta_model::decoration>& decoration,
    const bool is_enum,
    const masd::dogen::coding::meta_model::name& underlying_element,
    const bool is_exception)
    : masd::dogen::coding::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties,
      decoration),
      is_enum_(is_enum),
      underlying_element_(underlying_element),
      is_exception_(is_exception) { }

void forward_declarations::accept(const masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void forward_declarations::accept(masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void forward_declarations::accept(const masd::dogen::coding::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void forward_declarations::accept(masd::dogen::coding::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void forward_declarations::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"masd::dogen::generation::cpp::fabric::forward_declarations\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"is_enum\": " << is_enum_ << ", "
      << "\"underlying_element\": " << underlying_element_ << ", "
      << "\"is_exception\": " << is_exception_
      << " }";
}

void forward_declarations::swap(forward_declarations& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(is_enum_, other.is_enum_);
    swap(underlying_element_, other.underlying_element_);
    swap(is_exception_, other.is_exception_);
}

bool forward_declarations::equals(const masd::dogen::coding::meta_model::element& other) const {
    const forward_declarations* const p(dynamic_cast<const forward_declarations* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool forward_declarations::operator==(const forward_declarations& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        is_enum_ == rhs.is_enum_ &&
        underlying_element_ == rhs.underlying_element_ &&
        is_exception_ == rhs.is_exception_;
}

forward_declarations& forward_declarations::operator=(forward_declarations other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool forward_declarations::is_enum() const {
    return is_enum_;
}

void forward_declarations::is_enum(const bool v) {
    is_enum_ = v;
}

const masd::dogen::coding::meta_model::name& forward_declarations::underlying_element() const {
    return underlying_element_;
}

masd::dogen::coding::meta_model::name& forward_declarations::underlying_element() {
    return underlying_element_;
}

void forward_declarations::underlying_element(const masd::dogen::coding::meta_model::name& v) {
    underlying_element_ = v;
}

void forward_declarations::underlying_element(const masd::dogen::coding::meta_model::name&& v) {
    underlying_element_ = std::move(v);
}

bool forward_declarations::is_exception() const {
    return is_exception_;
}

void forward_declarations::is_exception(const bool v) {
    is_exception_ = v;
}

}
