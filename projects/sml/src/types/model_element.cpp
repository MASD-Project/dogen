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
#include "dogen/sml/types/model_element.hpp"


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

model_element::model_element()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)) { }

model_element::model_element(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const dogen::sml::generation_types& generation_type)
    : name_(name),
      documentation_(documentation),
      implementation_specific_parameters_(implementation_specific_parameters),
      generation_type_(generation_type) { }

void model_element::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::model_element\"" << ", "
      << "\"name\": " << name_ << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"implementation_specific_parameters\": " << implementation_specific_parameters_ << ", "
      << "\"generation_type\": " << generation_type_
      << " }";
}

void model_element::swap(model_element& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
    swap(implementation_specific_parameters_, other.implementation_specific_parameters_);
    swap(generation_type_, other.generation_type_);
}

bool model_element::compare(const model_element& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_ &&
        implementation_specific_parameters_ == rhs.implementation_specific_parameters_ &&
        generation_type_ == rhs.generation_type_;
}

const dogen::sml::qname& model_element::name() const {
    return name_;
}

dogen::sml::qname& model_element::name() {
    return name_;
}

void model_element::name(const dogen::sml::qname& v) {
    name_ = v;
}

void model_element::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

const std::string& model_element::documentation() const {
    return documentation_;
}

std::string& model_element::documentation() {
    return documentation_;
}

void model_element::documentation(const std::string& v) {
    documentation_ = v;
}

void model_element::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::vector<std::pair<std::string, std::string> >& model_element::implementation_specific_parameters() const {
    return implementation_specific_parameters_;
}

std::vector<std::pair<std::string, std::string> >& model_element::implementation_specific_parameters() {
    return implementation_specific_parameters_;
}

void model_element::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v) {
    implementation_specific_parameters_ = v;
}

void model_element::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v) {
    implementation_specific_parameters_ = std::move(v);
}

dogen::sml::generation_types model_element::generation_type() const {
    return generation_type_;
}

void model_element::generation_type(const dogen::sml::generation_types& v) {
    generation_type_ = v;
}

} }