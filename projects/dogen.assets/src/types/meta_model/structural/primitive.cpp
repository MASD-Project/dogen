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
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.assets/io/meta_model/attribute_io.hpp"
#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.assets/io/meta_model/orm/primitive_properties_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::assets::meta_model::orm::primitive_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::assets::meta_model::structural {

primitive::primitive()
    : is_nullable_(static_cast<bool>(0)),
      use_type_aliasing_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)) { }

primitive::primitive(primitive&& rhs)
    : dogen::assets::meta_model::element(
        std::forward<dogen::assets::meta_model::element>(rhs)),
      is_nullable_(std::move(rhs.is_nullable_)),
      value_attribute_(std::move(rhs.value_attribute_)),
      use_type_aliasing_(std::move(rhs.use_type_aliasing_)),
      is_immutable_(std::move(rhs.is_immutable_)),
      orm_properties_(std::move(rhs.orm_properties_)) { }

primitive::primitive(
    const dogen::assets::meta_model::name& name,
    const std::string& documentation,
    const dogen::assets::meta_model::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::assets::meta_model::name& meta_name,
    const dogen::assets::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const bool is_element_extension,
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
    const bool is_nullable,
    const dogen::assets::meta_model::attribute& value_attribute,
    const bool use_type_aliasing,
    const bool is_immutable,
    const boost::optional<dogen::assets::meta_model::orm::primitive_properties>& orm_properties)
    : dogen::assets::meta_model::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      origin_element_id,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      is_element_extension,
      artefact_properties,
      archetype_location_properties,
      decoration),
      is_nullable_(is_nullable),
      value_attribute_(value_attribute),
      use_type_aliasing_(use_type_aliasing),
      is_immutable_(is_immutable),
      orm_properties_(orm_properties) { }

void primitive::accept(const element_visitor& v) const {
    v.visit(*this);
}

void primitive::accept(element_visitor& v) const {
    v.visit(*this);
    }

void primitive::accept(const element_visitor& v) {
    v.visit(*this);
}

void primitive::accept(element_visitor& v) {
    v.visit(*this);
}

void primitive::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::structural::primitive\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"is_nullable\": " << is_nullable_ << ", "
      << "\"value_attribute\": " << value_attribute_ << ", "
      << "\"use_type_aliasing\": " << use_type_aliasing_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"orm_properties\": " << orm_properties_
      << " }";
}

void primitive::swap(primitive& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(is_nullable_, other.is_nullable_);
    swap(value_attribute_, other.value_attribute_);
    swap(use_type_aliasing_, other.use_type_aliasing_);
    swap(is_immutable_, other.is_immutable_);
    swap(orm_properties_, other.orm_properties_);
}

bool primitive::equals(const dogen::assets::meta_model::element& other) const {
    const primitive* const p(dynamic_cast<const primitive* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool primitive::operator==(const primitive& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        is_nullable_ == rhs.is_nullable_ &&
        value_attribute_ == rhs.value_attribute_ &&
        use_type_aliasing_ == rhs.use_type_aliasing_ &&
        is_immutable_ == rhs.is_immutable_ &&
        orm_properties_ == rhs.orm_properties_;
}

primitive& primitive::operator=(primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool primitive::is_nullable() const {
    return is_nullable_;
}

void primitive::is_nullable(const bool v) {
    is_nullable_ = v;
}

const dogen::assets::meta_model::attribute& primitive::value_attribute() const {
    return value_attribute_;
}

dogen::assets::meta_model::attribute& primitive::value_attribute() {
    return value_attribute_;
}

void primitive::value_attribute(const dogen::assets::meta_model::attribute& v) {
    value_attribute_ = v;
}

void primitive::value_attribute(const dogen::assets::meta_model::attribute&& v) {
    value_attribute_ = std::move(v);
}

bool primitive::use_type_aliasing() const {
    return use_type_aliasing_;
}

void primitive::use_type_aliasing(const bool v) {
    use_type_aliasing_ = v;
}

bool primitive::is_immutable() const {
    return is_immutable_;
}

void primitive::is_immutable(const bool v) {
    is_immutable_ = v;
}

const boost::optional<dogen::assets::meta_model::orm::primitive_properties>& primitive::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::assets::meta_model::orm::primitive_properties>& primitive::orm_properties() {
    return orm_properties_;
}

void primitive::orm_properties(const boost::optional<dogen::assets::meta_model::orm::primitive_properties>& v) {
    orm_properties_ = v;
}

void primitive::orm_properties(const boost::optional<dogen::assets::meta_model::orm::primitive_properties>&& v) {
    orm_properties_ = std::move(v);
}

}
