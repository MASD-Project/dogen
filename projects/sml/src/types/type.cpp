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
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/type.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<std::string, std::string>& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << "\"" << tidy_up_string(v.first) << "\"" << ", ";
    s << "\"second\": " << "\"" << tidy_up_string(v.second) << "\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::pair<std::string, std::string> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace sml {

type::type()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)) { }

type::type(
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type)
    : documentation_(documentation),
      implementation_specific_parameters_(implementation_specific_parameters),
      name_(name),
      generation_type_(generation_type) { }

void type::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::type\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"implementation_specific_parameters\": " << implementation_specific_parameters_ << ", "
      << "\"name\": " << name_ << ", "
      << "\"generation_type\": " << generation_type_
      << " }";
}

void type::swap(type& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(implementation_specific_parameters_, other.implementation_specific_parameters_);
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
}

bool type::compare(const type& rhs) const {
    return documentation_ == rhs.documentation_ &&
        implementation_specific_parameters_ == rhs.implementation_specific_parameters_ &&
        name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_;
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

const std::vector<std::pair<std::string, std::string> >& type::implementation_specific_parameters() const {
    return implementation_specific_parameters_;
}

std::vector<std::pair<std::string, std::string> >& type::implementation_specific_parameters() {
    return implementation_specific_parameters_;
}

void type::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v) {
    implementation_specific_parameters_ = v;
}

void type::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v) {
    implementation_specific_parameters_ = std::move(v);
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

} }