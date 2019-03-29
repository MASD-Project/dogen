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
#include "masd.dogen.coding/io/meta_model/editor_io.hpp"
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.coding/types/meta_model/modeline.hpp"
#include "masd.dogen.coding/io/meta_model/modeline_field_io.hpp"
#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"
#include "masd.dogen.coding/io/meta_model/modeline_location_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<masd::dogen::coding::meta_model::modeline_field>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

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

namespace masd::dogen::coding::meta_model {

modeline::modeline()
    : editor_(static_cast<masd::dogen::coding::meta_model::editor>(0)),
      location_(static_cast<masd::dogen::coding::meta_model::modeline_location>(0)) { }

modeline::modeline(
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
    const masd::dogen::coding::meta_model::editor editor,
    const masd::dogen::coding::meta_model::modeline_location location,
    const std::list<masd::dogen::coding::meta_model::modeline_field>& fields,
    const std::list<std::string>& applicable_meta_elements)
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
      editor_(editor),
      location_(location),
      fields_(fields),
      applicable_meta_elements_(applicable_meta_elements) { }

void modeline::accept(const element_visitor& v) const {
    v.visit(*this);
}

void modeline::accept(element_visitor& v) const {
    v.visit(*this);
    }

void modeline::accept(const element_visitor& v) {
    v.visit(*this);
}

void modeline::accept(element_visitor& v) {
    v.visit(*this);
}

void modeline::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::coding::meta_model::modeline\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"editor\": " << editor_ << ", "
      << "\"location\": " << location_ << ", "
      << "\"fields\": " << fields_ << ", "
      << "\"applicable_meta_elements\": " << applicable_meta_elements_
      << " }";
}

void modeline::swap(modeline& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(editor_, other.editor_);
    swap(location_, other.location_);
    swap(fields_, other.fields_);
    swap(applicable_meta_elements_, other.applicable_meta_elements_);
}

bool modeline::equals(const masd::dogen::coding::meta_model::element& other) const {
    const modeline* const p(dynamic_cast<const modeline* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool modeline::operator==(const modeline& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        editor_ == rhs.editor_ &&
        location_ == rhs.location_ &&
        fields_ == rhs.fields_ &&
        applicable_meta_elements_ == rhs.applicable_meta_elements_;
}

modeline& modeline::operator=(modeline other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

masd::dogen::coding::meta_model::editor modeline::editor() const {
    return editor_;
}

void modeline::editor(const masd::dogen::coding::meta_model::editor v) {
    editor_ = v;
}

masd::dogen::coding::meta_model::modeline_location modeline::location() const {
    return location_;
}

void modeline::location(const masd::dogen::coding::meta_model::modeline_location v) {
    location_ = v;
}

const std::list<masd::dogen::coding::meta_model::modeline_field>& modeline::fields() const {
    return fields_;
}

std::list<masd::dogen::coding::meta_model::modeline_field>& modeline::fields() {
    return fields_;
}

void modeline::fields(const std::list<masd::dogen::coding::meta_model::modeline_field>& v) {
    fields_ = v;
}

void modeline::fields(const std::list<masd::dogen::coding::meta_model::modeline_field>&& v) {
    fields_ = std::move(v);
}

const std::list<std::string>& modeline::applicable_meta_elements() const {
    return applicable_meta_elements_;
}

std::list<std::string>& modeline::applicable_meta_elements() {
    return applicable_meta_elements_;
}

void modeline::applicable_meta_elements(const std::list<std::string>& v) {
    applicable_meta_elements_ = v;
}

void modeline::applicable_meta_elements(const std::list<std::string>&& v) {
    applicable_meta_elements_ = std::move(v);
}

}
