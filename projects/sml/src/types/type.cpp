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
#include <ostream>
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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, std::string>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->second) << "\"";
        s << " } ]";
    }
    s << " ] ";
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, std::list<std::string> >& v) {
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
namespace sml {

type::type()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)),
      origin_type_(static_cast<dogen::sml::origin_types>(0)) { }

type::type(
    const std::string& documentation,
    const std::unordered_map<std::string, std::string>& simple_tags,
    const std::unordered_map<std::string, std::list<std::string> >& complex_tags,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type)
    : documentation_(documentation),
      simple_tags_(simple_tags),
      complex_tags_(complex_tags),
      name_(name),
      generation_type_(generation_type),
      origin_type_(origin_type) { }

void type::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::type\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"simple_tags\": " << simple_tags_ << ", "
      << "\"complex_tags\": " << complex_tags_ << ", "
      << "\"name\": " << name_ << ", "
      << "\"generation_type\": " << generation_type_ << ", "
      << "\"origin_type\": " << origin_type_
      << " }";
}

void type::swap(type& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(simple_tags_, other.simple_tags_);
    swap(complex_tags_, other.complex_tags_);
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
    swap(origin_type_, other.origin_type_);
}

bool type::compare(const type& rhs) const {
    return documentation_ == rhs.documentation_ &&
        simple_tags_ == rhs.simple_tags_ &&
        complex_tags_ == rhs.complex_tags_ &&
        name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_ &&
        origin_type_ == rhs.origin_type_;
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

const std::unordered_map<std::string, std::string>& type::simple_tags() const {
    return simple_tags_;
}

std::unordered_map<std::string, std::string>& type::simple_tags() {
    return simple_tags_;
}

void type::simple_tags(const std::unordered_map<std::string, std::string>& v) {
    simple_tags_ = v;
}

void type::simple_tags(const std::unordered_map<std::string, std::string>&& v) {
    simple_tags_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::string> >& type::complex_tags() const {
    return complex_tags_;
}

std::unordered_map<std::string, std::list<std::string> >& type::complex_tags() {
    return complex_tags_;
}

void type::complex_tags(const std::unordered_map<std::string, std::list<std::string> >& v) {
    complex_tags_ = v;
}

void type::complex_tags(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    complex_tags_ = std::move(v);
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

} }