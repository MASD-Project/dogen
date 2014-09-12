/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <ostream>
#include <sstream>
#include "dogen/sml/io/generation_types_io.hpp"
#include "dogen/sml/io/origin_types_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/type.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace boost {
namespace property_tree {

inline std::ostream& operator<<(std::ostream& s, const boost::property_tree::ptree& v) {
    std::ostringstream ss;
    boost::property_tree::write_json(ss, v);

    std::string content(ss.str());
    boost::replace_all(content, "\r\n", "");
    boost::replace_all(content, "\n", "");

    s << content;
    return s;
}

} }

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::sml::qname>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s << " }";
    return s;
}

}

namespace dogen {
namespace sml {

type::type()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)),
      origin_type_(static_cast<dogen::sml::origin_types>(0)) { }

type::type(type&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      meta_data_(std::move(rhs.meta_data_)),
      name_(std::move(rhs.name_)),
      generation_type_(std::move(rhs.generation_type_)),
      origin_type_(std::move(rhs.origin_type_)),
      parent_module_(std::move(rhs.parent_module_)) { }

type::type(
    const std::string& documentation,
    const boost::property_tree::ptree& meta_data,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type,
    const boost::optional<dogen::sml::qname>& parent_module)
    : documentation_(documentation),
      meta_data_(meta_data),
      name_(name),
      generation_type_(generation_type),
      origin_type_(origin_type),
      parent_module_(parent_module) { }

void type::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::type\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"meta_data\": " << meta_data_ << ", "
      << "\"name\": " << name_ << ", "
      << "\"generation_type\": " << generation_type_ << ", "
      << "\"origin_type\": " << origin_type_ << ", "
      << "\"parent_module\": " << parent_module_
      << " }";
}

void type::swap(type& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(meta_data_, other.meta_data_);
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
    swap(origin_type_, other.origin_type_);
    swap(parent_module_, other.parent_module_);
}

bool type::compare(const type& rhs) const {
    return documentation_ == rhs.documentation_ &&
        meta_data_ == rhs.meta_data_ &&
        name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_ &&
        origin_type_ == rhs.origin_type_ &&
        parent_module_ == rhs.parent_module_;
}

const std::string& type::documentation() const {
    return documentation_;
}

std::string& type::documentation() {
    return documentation_;
}

void type::documentation(const std::string& v) {
    documentation_ = v;
}

void type::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::property_tree::ptree& type::meta_data() const {
    return meta_data_;
}

boost::property_tree::ptree& type::meta_data() {
    return meta_data_;
}

void type::meta_data(const boost::property_tree::ptree& v) {
    meta_data_ = v;
}

void type::meta_data(const boost::property_tree::ptree&& v) {
    meta_data_ = std::move(v);
}

const dogen::sml::qname& type::name() const {
    return name_;
}

dogen::sml::qname& type::name() {
    return name_;
}

void type::name(const dogen::sml::qname& v) {
    name_ = v;
}

void type::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

dogen::sml::generation_types type::generation_type() const {
    return generation_type_;
}

void type::generation_type(const dogen::sml::generation_types& v) {
    generation_type_ = v;
}

dogen::sml::origin_types type::origin_type() const {
    return origin_type_;
}

void type::origin_type(const dogen::sml::origin_types& v) {
    origin_type_ = v;
}

const boost::optional<dogen::sml::qname>& type::parent_module() const {
    return parent_module_;
}

boost::optional<dogen::sml::qname>& type::parent_module() {
    return parent_module_;
}

void type::parent_module(const boost::optional<dogen::sml::qname>& v) {
    parent_module_ = v;
}

void type::parent_module(const boost::optional<dogen::sml::qname>&& v) {
    parent_module_ = std::move(v);
}

} }