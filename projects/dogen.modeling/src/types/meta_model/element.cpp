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
#include <boost/algorithm/string.hpp>
#include "dogen.annotations/io/annotation_io.hpp"
#include "dogen.modeling/io/meta_model/name_io.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.formatting/io/decoration_properties_io.hpp"
#include "dogen.modeling/io/meta_model/origin_types_io.hpp"
#include "dogen.modeling/io/meta_model/opaque_properties_io.hpp"
#include "dogen.modeling/types/meta_model/opaque_properties.hpp"
#include "dogen.modeling/io/meta_model/static_stereotypes_io.hpp"
#include "dogen.modeling/io/meta_model/artefact_properties_io.hpp"
#include "dogen.modeling/io/meta_model/local_archetype_location_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::modeling::meta_model::static_stereotypes>& v) {
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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::modeling::meta_model::opaque_properties>& lhs,
const boost::shared_ptr<dogen::modeling::meta_model::opaque_properties>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::modeling::meta_model::opaque_properties>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen {
namespace modeling {
namespace meta_model {

element::element()
    : origin_type_(static_cast<dogen::modeling::meta_model::origin_types>(0)),
      in_global_module_(static_cast<bool>(0)),
      is_element_extension_(static_cast<bool>(0)) { }

element::element(element&& rhs)
    : name_(std::move(rhs.name_)),
      documentation_(std::move(rhs.documentation_)),
      annotation_(std::move(rhs.annotation_)),
      origin_type_(std::move(rhs.origin_type_)),
      contained_by_(std::move(rhs.contained_by_)),
      in_global_module_(std::move(rhs.in_global_module_)),
      static_stereotypes_(std::move(rhs.static_stereotypes_)),
      dynamic_stereotypes_(std::move(rhs.dynamic_stereotypes_)),
      meta_name_(std::move(rhs.meta_name_)),
      is_element_extension_(std::move(rhs.is_element_extension_)),
      decoration_properties_(std::move(rhs.decoration_properties_)),
      artefact_properties_(std::move(rhs.artefact_properties_)),
      archetype_location_properties_(std::move(rhs.archetype_location_properties_)),
      opaque_properties_(std::move(rhs.opaque_properties_)) { }

element::element(
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
    const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& opaque_properties)
    : name_(name),
      documentation_(documentation),
      annotation_(annotation),
      origin_type_(origin_type),
      contained_by_(contained_by),
      in_global_module_(in_global_module),
      static_stereotypes_(static_stereotypes),
      dynamic_stereotypes_(dynamic_stereotypes),
      meta_name_(meta_name),
      is_element_extension_(is_element_extension),
      decoration_properties_(decoration_properties),
      artefact_properties_(artefact_properties),
      archetype_location_properties_(archetype_location_properties),
      opaque_properties_(opaque_properties) { }

void element::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::modeling::meta_model::element\"" << ", "
      << "\"name\": " << name_ << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"annotation\": " << annotation_ << ", "
      << "\"origin_type\": " << origin_type_ << ", "
      << "\"contained_by\": " << contained_by_ << ", "
      << "\"in_global_module\": " << in_global_module_ << ", "
      << "\"static_stereotypes\": " << static_stereotypes_ << ", "
      << "\"dynamic_stereotypes\": " << dynamic_stereotypes_ << ", "
      << "\"meta_name\": " << meta_name_ << ", "
      << "\"is_element_extension\": " << is_element_extension_ << ", "
      << "\"decoration_properties\": " << decoration_properties_ << ", "
      << "\"artefact_properties\": " << artefact_properties_ << ", "
      << "\"archetype_location_properties\": " << archetype_location_properties_ << ", "
      << "\"opaque_properties\": " << opaque_properties_
      << " }";
}

void element::swap(element& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
    swap(annotation_, other.annotation_);
    swap(origin_type_, other.origin_type_);
    swap(contained_by_, other.contained_by_);
    swap(in_global_module_, other.in_global_module_);
    swap(static_stereotypes_, other.static_stereotypes_);
    swap(dynamic_stereotypes_, other.dynamic_stereotypes_);
    swap(meta_name_, other.meta_name_);
    swap(is_element_extension_, other.is_element_extension_);
    swap(decoration_properties_, other.decoration_properties_);
    swap(artefact_properties_, other.artefact_properties_);
    swap(archetype_location_properties_, other.archetype_location_properties_);
    swap(opaque_properties_, other.opaque_properties_);
}

bool element::compare(const element& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_ &&
        annotation_ == rhs.annotation_ &&
        origin_type_ == rhs.origin_type_ &&
        contained_by_ == rhs.contained_by_ &&
        in_global_module_ == rhs.in_global_module_ &&
        static_stereotypes_ == rhs.static_stereotypes_ &&
        dynamic_stereotypes_ == rhs.dynamic_stereotypes_ &&
        meta_name_ == rhs.meta_name_ &&
        is_element_extension_ == rhs.is_element_extension_ &&
        decoration_properties_ == rhs.decoration_properties_ &&
        artefact_properties_ == rhs.artefact_properties_ &&
        archetype_location_properties_ == rhs.archetype_location_properties_ &&
        opaque_properties_ == rhs.opaque_properties_;
}

const dogen::modeling::meta_model::name& element::name() const {
    return name_;
}

dogen::modeling::meta_model::name& element::name() {
    return name_;
}

void element::name(const dogen::modeling::meta_model::name& v) {
    name_ = v;
}

void element::name(const dogen::modeling::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::string& element::documentation() const {
    return documentation_;
}

std::string& element::documentation() {
    return documentation_;
}

void element::documentation(const std::string& v) {
    documentation_ = v;
}

void element::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::annotations::annotation& element::annotation() const {
    return annotation_;
}

dogen::annotations::annotation& element::annotation() {
    return annotation_;
}

void element::annotation(const dogen::annotations::annotation& v) {
    annotation_ = v;
}

void element::annotation(const dogen::annotations::annotation&& v) {
    annotation_ = std::move(v);
}

dogen::modeling::meta_model::origin_types element::origin_type() const {
    return origin_type_;
}

void element::origin_type(const dogen::modeling::meta_model::origin_types v) {
    origin_type_ = v;
}

const boost::optional<dogen::modeling::meta_model::name>& element::contained_by() const {
    return contained_by_;
}

boost::optional<dogen::modeling::meta_model::name>& element::contained_by() {
    return contained_by_;
}

void element::contained_by(const boost::optional<dogen::modeling::meta_model::name>& v) {
    contained_by_ = v;
}

void element::contained_by(const boost::optional<dogen::modeling::meta_model::name>&& v) {
    contained_by_ = std::move(v);
}

bool element::in_global_module() const {
    return in_global_module_;
}

void element::in_global_module(const bool v) {
    in_global_module_ = v;
}

const std::list<dogen::modeling::meta_model::static_stereotypes>& element::static_stereotypes() const {
    return static_stereotypes_;
}

std::list<dogen::modeling::meta_model::static_stereotypes>& element::static_stereotypes() {
    return static_stereotypes_;
}

void element::static_stereotypes(const std::list<dogen::modeling::meta_model::static_stereotypes>& v) {
    static_stereotypes_ = v;
}

void element::static_stereotypes(const std::list<dogen::modeling::meta_model::static_stereotypes>&& v) {
    static_stereotypes_ = std::move(v);
}

const std::list<std::string>& element::dynamic_stereotypes() const {
    return dynamic_stereotypes_;
}

std::list<std::string>& element::dynamic_stereotypes() {
    return dynamic_stereotypes_;
}

void element::dynamic_stereotypes(const std::list<std::string>& v) {
    dynamic_stereotypes_ = v;
}

void element::dynamic_stereotypes(const std::list<std::string>&& v) {
    dynamic_stereotypes_ = std::move(v);
}

const dogen::modeling::meta_model::name& element::meta_name() const {
    return meta_name_;
}

dogen::modeling::meta_model::name& element::meta_name() {
    return meta_name_;
}

void element::meta_name(const dogen::modeling::meta_model::name& v) {
    meta_name_ = v;
}

void element::meta_name(const dogen::modeling::meta_model::name&& v) {
    meta_name_ = std::move(v);
}

bool element::is_element_extension() const {
    return is_element_extension_;
}

void element::is_element_extension(const bool v) {
    is_element_extension_ = v;
}

const dogen::formatting::decoration_properties& element::decoration_properties() const {
    return decoration_properties_;
}

dogen::formatting::decoration_properties& element::decoration_properties() {
    return decoration_properties_;
}

void element::decoration_properties(const dogen::formatting::decoration_properties& v) {
    decoration_properties_ = v;
}

void element::decoration_properties(const dogen::formatting::decoration_properties&& v) {
    decoration_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& element::artefact_properties() const {
    return artefact_properties_;
}

std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& element::artefact_properties() {
    return artefact_properties_;
}

void element::artefact_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& v) {
    artefact_properties_ = v;
}

void element::artefact_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>&& v) {
    artefact_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& element::archetype_location_properties() const {
    return archetype_location_properties_;
}

std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& element::archetype_location_properties() {
    return archetype_location_properties_;
}

void element::archetype_location_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& v) {
    archetype_location_properties_ = v;
}

void element::archetype_location_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>&& v) {
    archetype_location_properties_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& element::opaque_properties() const {
    return opaque_properties_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& element::opaque_properties() {
    return opaque_properties_;
}

void element::opaque_properties(const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& v) {
    opaque_properties_ = v;
}

void element::opaque_properties(const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >&& v) {
    opaque_properties_ = std::move(v);
}

} } }
