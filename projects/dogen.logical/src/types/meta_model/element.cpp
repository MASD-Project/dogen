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
#include "dogen.logical/io/meta_model/name_io.hpp"
#include "dogen.logical/types/meta_model/element.hpp"
#include "dogen.logical/io/meta_model/origin_types_io.hpp"
#include "dogen.logical/io/meta_model/technical_space_io.hpp"
#include "dogen.variability/io/meta_model/configuration_io.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.logical/io/meta_model/static_stereotypes_io.hpp"
#include "dogen.logical/io/meta_model/artefact_properties_io.hpp"
#include "dogen.logical/io/meta_model/decoration/element_properties_io.hpp"
#include "dogen.logical/io/meta_model/local_archetype_location_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::meta_model::static_stereotypes>& v) {
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

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::logical::meta_model::decoration::element_properties>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen::logical::meta_model {

element::element()
    : origin_type_(static_cast<dogen::logical::meta_model::origin_types>(0)),
      in_global_module_(static_cast<bool>(0)),
      intrinsic_technical_space_(static_cast<dogen::logical::meta_model::technical_space>(0)) { }

element::element(
    const dogen::logical::meta_model::name& name,
    const std::string& documentation,
    const dogen::logical::meta_model::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::meta_model::name& meta_name,
    const dogen::logical::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >& decoration)
    : name_(name),
      documentation_(documentation),
      origin_type_(origin_type),
      origin_sha1_hash_(origin_sha1_hash),
      origin_element_id_(origin_element_id),
      contained_by_(contained_by),
      in_global_module_(in_global_module),
      static_stereotypes_(static_stereotypes),
      dynamic_stereotypes_(dynamic_stereotypes),
      meta_name_(meta_name),
      intrinsic_technical_space_(intrinsic_technical_space),
      configuration_(configuration),
      artefact_properties_(artefact_properties),
      archetype_location_properties_(archetype_location_properties),
      decoration_(decoration) { }

void element::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::meta_model::element\"" << ", "
      << "\"name\": " << name_ << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"origin_type\": " << origin_type_ << ", "
      << "\"origin_sha1_hash\": " << "\"" << tidy_up_string(origin_sha1_hash_) << "\"" << ", "
      << "\"origin_element_id\": " << "\"" << tidy_up_string(origin_element_id_) << "\"" << ", "
      << "\"contained_by\": " << "\"" << tidy_up_string(contained_by_) << "\"" << ", "
      << "\"in_global_module\": " << in_global_module_ << ", "
      << "\"static_stereotypes\": " << static_stereotypes_ << ", "
      << "\"dynamic_stereotypes\": " << dynamic_stereotypes_ << ", "
      << "\"meta_name\": " << meta_name_ << ", "
      << "\"intrinsic_technical_space\": " << intrinsic_technical_space_ << ", "
      << "\"configuration\": " << configuration_ << ", "
      << "\"artefact_properties\": " << artefact_properties_ << ", "
      << "\"archetype_location_properties\": " << archetype_location_properties_ << ", "
      << "\"decoration\": " << decoration_
      << " }";
}

void element::swap(element& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
    swap(origin_type_, other.origin_type_);
    swap(origin_sha1_hash_, other.origin_sha1_hash_);
    swap(origin_element_id_, other.origin_element_id_);
    swap(contained_by_, other.contained_by_);
    swap(in_global_module_, other.in_global_module_);
    swap(static_stereotypes_, other.static_stereotypes_);
    swap(dynamic_stereotypes_, other.dynamic_stereotypes_);
    swap(meta_name_, other.meta_name_);
    swap(intrinsic_technical_space_, other.intrinsic_technical_space_);
    swap(configuration_, other.configuration_);
    swap(artefact_properties_, other.artefact_properties_);
    swap(archetype_location_properties_, other.archetype_location_properties_);
    swap(decoration_, other.decoration_);
}

bool element::compare(const element& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_ &&
        origin_type_ == rhs.origin_type_ &&
        origin_sha1_hash_ == rhs.origin_sha1_hash_ &&
        origin_element_id_ == rhs.origin_element_id_ &&
        contained_by_ == rhs.contained_by_ &&
        in_global_module_ == rhs.in_global_module_ &&
        static_stereotypes_ == rhs.static_stereotypes_ &&
        dynamic_stereotypes_ == rhs.dynamic_stereotypes_ &&
        meta_name_ == rhs.meta_name_ &&
        intrinsic_technical_space_ == rhs.intrinsic_technical_space_ &&
        configuration_ == rhs.configuration_ &&
        artefact_properties_ == rhs.artefact_properties_ &&
        archetype_location_properties_ == rhs.archetype_location_properties_ &&
        decoration_ == rhs.decoration_;
}

const dogen::logical::meta_model::name& element::name() const {
    return name_;
}

dogen::logical::meta_model::name& element::name() {
    return name_;
}

void element::name(const dogen::logical::meta_model::name& v) {
    name_ = v;
}

void element::name(const dogen::logical::meta_model::name&& v) {
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

dogen::logical::meta_model::origin_types element::origin_type() const {
    return origin_type_;
}

void element::origin_type(const dogen::logical::meta_model::origin_types v) {
    origin_type_ = v;
}

const std::string& element::origin_sha1_hash() const {
    return origin_sha1_hash_;
}

std::string& element::origin_sha1_hash() {
    return origin_sha1_hash_;
}

void element::origin_sha1_hash(const std::string& v) {
    origin_sha1_hash_ = v;
}

void element::origin_sha1_hash(const std::string&& v) {
    origin_sha1_hash_ = std::move(v);
}

const std::string& element::origin_element_id() const {
    return origin_element_id_;
}

std::string& element::origin_element_id() {
    return origin_element_id_;
}

void element::origin_element_id(const std::string& v) {
    origin_element_id_ = v;
}

void element::origin_element_id(const std::string&& v) {
    origin_element_id_ = std::move(v);
}

const std::string& element::contained_by() const {
    return contained_by_;
}

std::string& element::contained_by() {
    return contained_by_;
}

void element::contained_by(const std::string& v) {
    contained_by_ = v;
}

void element::contained_by(const std::string&& v) {
    contained_by_ = std::move(v);
}

bool element::in_global_module() const {
    return in_global_module_;
}

void element::in_global_module(const bool v) {
    in_global_module_ = v;
}

const std::list<dogen::logical::meta_model::static_stereotypes>& element::static_stereotypes() const {
    return static_stereotypes_;
}

std::list<dogen::logical::meta_model::static_stereotypes>& element::static_stereotypes() {
    return static_stereotypes_;
}

void element::static_stereotypes(const std::list<dogen::logical::meta_model::static_stereotypes>& v) {
    static_stereotypes_ = v;
}

void element::static_stereotypes(const std::list<dogen::logical::meta_model::static_stereotypes>&& v) {
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

const dogen::logical::meta_model::name& element::meta_name() const {
    return meta_name_;
}

dogen::logical::meta_model::name& element::meta_name() {
    return meta_name_;
}

void element::meta_name(const dogen::logical::meta_model::name& v) {
    meta_name_ = v;
}

void element::meta_name(const dogen::logical::meta_model::name&& v) {
    meta_name_ = std::move(v);
}

dogen::logical::meta_model::technical_space element::intrinsic_technical_space() const {
    return intrinsic_technical_space_;
}

void element::intrinsic_technical_space(const dogen::logical::meta_model::technical_space v) {
    intrinsic_technical_space_ = v;
}

const boost::shared_ptr<dogen::variability::meta_model::configuration>& element::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::meta_model::configuration>& element::configuration() {
    return configuration_;
}

void element::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void element::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>& element::artefact_properties() const {
    return artefact_properties_;
}

std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>& element::artefact_properties() {
    return artefact_properties_;
}

void element::artefact_properties(const std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>& v) {
    artefact_properties_ = v;
}

void element::artefact_properties(const std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>&& v) {
    artefact_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>& element::archetype_location_properties() const {
    return archetype_location_properties_;
}

std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>& element::archetype_location_properties() {
    return archetype_location_properties_;
}

void element::archetype_location_properties(const std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>& v) {
    archetype_location_properties_ = v;
}

void element::archetype_location_properties(const std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>&& v) {
    archetype_location_properties_ = std::move(v);
}

const std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >& element::decoration() const {
    return decoration_;
}

std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >& element::decoration() {
    return decoration_;
}

void element::decoration(const std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >& v) {
    decoration_ = v;
}

void element::decoration(const std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >&& v) {
    decoration_ = std::move(v);
}

}
