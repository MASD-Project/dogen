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
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.generation.cpp/types/element_visitor.hpp"
#include "dogen.generation.cpp/types/fabric/object_odb_options.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen::generation::cpp::fabric {

object_odb_options::object_odb_options(
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
    const std::string& epilogue,
    const std::list<std::string>& include_regexes,
    const std::string& header_guard_prefix)
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
      epilogue_(epilogue),
      include_regexes_(include_regexes),
      header_guard_prefix_(header_guard_prefix) { }

void object_odb_options::accept(const dogen::assets::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void object_odb_options::accept(dogen::assets::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void object_odb_options::accept(const dogen::assets::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void object_odb_options::accept(dogen::assets::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void object_odb_options::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::generation::cpp::fabric::object_odb_options\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"epilogue\": " << "\"" << tidy_up_string(epilogue_) << "\"" << ", "
      << "\"include_regexes\": " << include_regexes_ << ", "
      << "\"header_guard_prefix\": " << "\"" << tidy_up_string(header_guard_prefix_) << "\""
      << " }";
}

void object_odb_options::swap(object_odb_options& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(epilogue_, other.epilogue_);
    swap(include_regexes_, other.include_regexes_);
    swap(header_guard_prefix_, other.header_guard_prefix_);
}

bool object_odb_options::equals(const dogen::assets::meta_model::element& other) const {
    const object_odb_options* const p(dynamic_cast<const object_odb_options* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool object_odb_options::operator==(const object_odb_options& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        epilogue_ == rhs.epilogue_ &&
        include_regexes_ == rhs.include_regexes_ &&
        header_guard_prefix_ == rhs.header_guard_prefix_;
}

object_odb_options& object_odb_options::operator=(object_odb_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& object_odb_options::epilogue() const {
    return epilogue_;
}

std::string& object_odb_options::epilogue() {
    return epilogue_;
}

void object_odb_options::epilogue(const std::string& v) {
    epilogue_ = v;
}

void object_odb_options::epilogue(const std::string&& v) {
    epilogue_ = std::move(v);
}

const std::list<std::string>& object_odb_options::include_regexes() const {
    return include_regexes_;
}

std::list<std::string>& object_odb_options::include_regexes() {
    return include_regexes_;
}

void object_odb_options::include_regexes(const std::list<std::string>& v) {
    include_regexes_ = v;
}

void object_odb_options::include_regexes(const std::list<std::string>&& v) {
    include_regexes_ = std::move(v);
}

const std::string& object_odb_options::header_guard_prefix() const {
    return header_guard_prefix_;
}

std::string& object_odb_options::header_guard_prefix() {
    return header_guard_prefix_;
}

void object_odb_options::header_guard_prefix(const std::string& v) {
    header_guard_prefix_ = v;
}

void object_odb_options::header_guard_prefix(const std::string&& v) {
    header_guard_prefix_ = std::move(v);
}

}
