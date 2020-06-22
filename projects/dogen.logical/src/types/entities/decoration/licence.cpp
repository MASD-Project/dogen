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
#include <boost/algorithm/string.hpp>
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/decoration/licence.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::logical::entities::decoration {

licence::licence(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::entities::name& meta_name,
    const dogen::logical::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::logical::entities::label>& labels,
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::string& short_form,
    const std::string& long_form)
    : dogen::logical::entities::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      artefact_properties,
      enablement_properties,
      decoration),
      short_form_(short_form),
      long_form_(long_form) { }

void licence::accept(const element_visitor& v) const {
    v.visit(*this);
}

void licence::accept(element_visitor& v) const {
    v.visit(*this);
    }

void licence::accept(const element_visitor& v) {
    v.visit(*this);
}

void licence::accept(element_visitor& v) {
    v.visit(*this);
}

void licence::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::decoration::licence\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"short_form\": " << "\"" << tidy_up_string(short_form_) << "\"" << ", "
      << "\"long_form\": " << "\"" << tidy_up_string(long_form_) << "\""
      << " }";
}

void licence::swap(licence& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(short_form_, other.short_form_);
    swap(long_form_, other.long_form_);
}

bool licence::equals(const dogen::logical::entities::element& other) const {
    const licence* const p(dynamic_cast<const licence* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool licence::operator==(const licence& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        short_form_ == rhs.short_form_ &&
        long_form_ == rhs.long_form_;
}

licence& licence::operator=(licence other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& licence::short_form() const {
    return short_form_;
}

std::string& licence::short_form() {
    return short_form_;
}

void licence::short_form(const std::string& v) {
    short_form_ = v;
}

void licence::short_form(const std::string&& v) {
    short_form_ = std::move(v);
}

const std::string& licence::long_form() const {
    return long_form_;
}

std::string& licence::long_form() {
    return long_form_;
}

void licence::long_form(const std::string& v) {
    long_form_ = v;
}

void licence::long_form(const std::string&& v) {
    long_form_ = std::move(v);
}

}
