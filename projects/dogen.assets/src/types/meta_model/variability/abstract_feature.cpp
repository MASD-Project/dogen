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
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/name_tree_io.hpp"
#include "dogen.variability/io/meta_model/value_type_io.hpp"
#include "dogen.variability/io/meta_model/binding_point_io.hpp"
#include "dogen.variability/io/meta_model/configuration_io.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.assets/types/meta_model/variability/abstract_feature.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::variability::meta_model::binding_point>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::assets::meta_model::variability {

abstract_feature::abstract_feature()
    : value_type_(static_cast<dogen::variability::meta_model::value_type>(0)),
      is_optional_(static_cast<bool>(0)),
      requires_optionality_(static_cast<bool>(0)) { }

abstract_feature::abstract_feature(abstract_feature&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      configuration_(std::move(rhs.configuration_)),
      name_(std::move(rhs.name_)),
      key_(std::move(rhs.key_)),
      identifiable_key_(std::move(rhs.identifiable_key_)),
      unparsed_type_(std::move(rhs.unparsed_type_)),
      mapped_type_(std::move(rhs.mapped_type_)),
      parsed_type_(std::move(rhs.parsed_type_)),
      value_(std::move(rhs.value_)),
      value_type_(std::move(rhs.value_type_)),
      binding_point_(std::move(rhs.binding_point_)),
      is_optional_(std::move(rhs.is_optional_)),
      requires_optionality_(std::move(rhs.requires_optionality_)) { }

abstract_feature::abstract_feature(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::assets::meta_model::name& name,
    const std::string& key,
    const std::string& identifiable_key,
    const std::string& unparsed_type,
    const std::string& mapped_type,
    const dogen::assets::meta_model::name_tree& parsed_type,
    const std::string& value,
    const dogen::variability::meta_model::value_type value_type,
    const boost::optional<dogen::variability::meta_model::binding_point>& binding_point,
    const bool is_optional,
    const bool requires_optionality)
    : documentation_(documentation),
      configuration_(configuration),
      name_(name),
      key_(key),
      identifiable_key_(identifiable_key),
      unparsed_type_(unparsed_type),
      mapped_type_(mapped_type),
      parsed_type_(parsed_type),
      value_(value),
      value_type_(value_type),
      binding_point_(binding_point),
      is_optional_(is_optional),
      requires_optionality_(requires_optionality) { }

void abstract_feature::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::abstract_feature\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"configuration\": " << configuration_ << ", "
      << "\"name\": " << name_ << ", "
      << "\"key\": " << "\"" << tidy_up_string(key_) << "\"" << ", "
      << "\"identifiable_key\": " << "\"" << tidy_up_string(identifiable_key_) << "\"" << ", "
      << "\"unparsed_type\": " << "\"" << tidy_up_string(unparsed_type_) << "\"" << ", "
      << "\"mapped_type\": " << "\"" << tidy_up_string(mapped_type_) << "\"" << ", "
      << "\"parsed_type\": " << parsed_type_ << ", "
      << "\"value\": " << "\"" << tidy_up_string(value_) << "\"" << ", "
      << "\"value_type\": " << value_type_ << ", "
      << "\"binding_point\": " << binding_point_ << ", "
      << "\"is_optional\": " << is_optional_ << ", "
      << "\"requires_optionality\": " << requires_optionality_
      << " }";
}

void abstract_feature::swap(abstract_feature& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(configuration_, other.configuration_);
    swap(name_, other.name_);
    swap(key_, other.key_);
    swap(identifiable_key_, other.identifiable_key_);
    swap(unparsed_type_, other.unparsed_type_);
    swap(mapped_type_, other.mapped_type_);
    swap(parsed_type_, other.parsed_type_);
    swap(value_, other.value_);
    swap(value_type_, other.value_type_);
    swap(binding_point_, other.binding_point_);
    swap(is_optional_, other.is_optional_);
    swap(requires_optionality_, other.requires_optionality_);
}

bool abstract_feature::compare(const abstract_feature& rhs) const {
    return documentation_ == rhs.documentation_ &&
        configuration_ == rhs.configuration_ &&
        name_ == rhs.name_ &&
        key_ == rhs.key_ &&
        identifiable_key_ == rhs.identifiable_key_ &&
        unparsed_type_ == rhs.unparsed_type_ &&
        mapped_type_ == rhs.mapped_type_ &&
        parsed_type_ == rhs.parsed_type_ &&
        value_ == rhs.value_ &&
        value_type_ == rhs.value_type_ &&
        binding_point_ == rhs.binding_point_ &&
        is_optional_ == rhs.is_optional_ &&
        requires_optionality_ == rhs.requires_optionality_;
}

const std::string& abstract_feature::documentation() const {
    return documentation_;
}

std::string& abstract_feature::documentation() {
    return documentation_;
}

void abstract_feature::documentation(const std::string& v) {
    documentation_ = v;
}

void abstract_feature::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::configuration>& abstract_feature::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::meta_model::configuration>& abstract_feature::configuration() {
    return configuration_;
}

void abstract_feature::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void abstract_feature::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::assets::meta_model::name& abstract_feature::name() const {
    return name_;
}

dogen::assets::meta_model::name& abstract_feature::name() {
    return name_;
}

void abstract_feature::name(const dogen::assets::meta_model::name& v) {
    name_ = v;
}

void abstract_feature::name(const dogen::assets::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::string& abstract_feature::key() const {
    return key_;
}

std::string& abstract_feature::key() {
    return key_;
}

void abstract_feature::key(const std::string& v) {
    key_ = v;
}

void abstract_feature::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::string& abstract_feature::identifiable_key() const {
    return identifiable_key_;
}

std::string& abstract_feature::identifiable_key() {
    return identifiable_key_;
}

void abstract_feature::identifiable_key(const std::string& v) {
    identifiable_key_ = v;
}

void abstract_feature::identifiable_key(const std::string&& v) {
    identifiable_key_ = std::move(v);
}

const std::string& abstract_feature::unparsed_type() const {
    return unparsed_type_;
}

std::string& abstract_feature::unparsed_type() {
    return unparsed_type_;
}

void abstract_feature::unparsed_type(const std::string& v) {
    unparsed_type_ = v;
}

void abstract_feature::unparsed_type(const std::string&& v) {
    unparsed_type_ = std::move(v);
}

const std::string& abstract_feature::mapped_type() const {
    return mapped_type_;
}

std::string& abstract_feature::mapped_type() {
    return mapped_type_;
}

void abstract_feature::mapped_type(const std::string& v) {
    mapped_type_ = v;
}

void abstract_feature::mapped_type(const std::string&& v) {
    mapped_type_ = std::move(v);
}

const dogen::assets::meta_model::name_tree& abstract_feature::parsed_type() const {
    return parsed_type_;
}

dogen::assets::meta_model::name_tree& abstract_feature::parsed_type() {
    return parsed_type_;
}

void abstract_feature::parsed_type(const dogen::assets::meta_model::name_tree& v) {
    parsed_type_ = v;
}

void abstract_feature::parsed_type(const dogen::assets::meta_model::name_tree&& v) {
    parsed_type_ = std::move(v);
}

const std::string& abstract_feature::value() const {
    return value_;
}

std::string& abstract_feature::value() {
    return value_;
}

void abstract_feature::value(const std::string& v) {
    value_ = v;
}

void abstract_feature::value(const std::string&& v) {
    value_ = std::move(v);
}

dogen::variability::meta_model::value_type abstract_feature::value_type() const {
    return value_type_;
}

void abstract_feature::value_type(const dogen::variability::meta_model::value_type v) {
    value_type_ = v;
}

const boost::optional<dogen::variability::meta_model::binding_point>& abstract_feature::binding_point() const {
    return binding_point_;
}

boost::optional<dogen::variability::meta_model::binding_point>& abstract_feature::binding_point() {
    return binding_point_;
}

void abstract_feature::binding_point(const boost::optional<dogen::variability::meta_model::binding_point>& v) {
    binding_point_ = v;
}

void abstract_feature::binding_point(const boost::optional<dogen::variability::meta_model::binding_point>&& v) {
    binding_point_ = std::move(v);
}

bool abstract_feature::is_optional() const {
    return is_optional_;
}

void abstract_feature::is_optional(const bool v) {
    is_optional_ = v;
}

bool abstract_feature::requires_optionality() const {
    return requires_optionality_;
}

void abstract_feature::requires_optionality(const bool v) {
    requires_optionality_ = v;
}

}
