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
#include "dogen/cppim/io/feature_io.hpp"
#include "dogen/cppim/types/preamble.hpp"


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

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<std::string, std::string> >& v) {
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
namespace cppim {

preamble::preamble(
    const std::string& prefix,
    const std::list<std::pair<std::string, std::string> >& fields,
    const std::string& kvp_separator,
    const std::string& field_separator,
    const std::string& postfix)
    : dogen::cppim::feature(),
      prefix_(prefix),
      fields_(fields),
      kvp_separator_(kvp_separator),
      field_separator_(field_separator),
      postfix_(postfix) { }

void preamble::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cppim::preamble\"" << ", "
      << "\"__parent_0__\": ";
    feature::to_stream(s);
    s << ", "
      << "\"prefix\": " << "\"" << tidy_up_string(prefix_) << "\"" << ", "
      << "\"fields\": " << fields_ << ", "
      << "\"kvp_separator\": " << "\"" << tidy_up_string(kvp_separator_) << "\"" << ", "
      << "\"field_separator\": " << "\"" << tidy_up_string(field_separator_) << "\"" << ", "
      << "\"postfix\": " << "\"" << tidy_up_string(postfix_) << "\""
      << " }";
}

void preamble::swap(preamble& other) noexcept {
    feature::swap(other);

    using std::swap;
    swap(prefix_, other.prefix_);
    swap(fields_, other.fields_);
    swap(kvp_separator_, other.kvp_separator_);
    swap(field_separator_, other.field_separator_);
    swap(postfix_, other.postfix_);
}

bool preamble::equals(const dogen::cppim::feature& other) const {
    const preamble* const p(dynamic_cast<const preamble* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool preamble::operator==(const preamble& rhs) const {
    return feature::compare(rhs) &&
        prefix_ == rhs.prefix_ &&
        fields_ == rhs.fields_ &&
        kvp_separator_ == rhs.kvp_separator_ &&
        field_separator_ == rhs.field_separator_ &&
        postfix_ == rhs.postfix_;
}

preamble& preamble::operator=(preamble other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& preamble::prefix() const {
    return prefix_;
}

std::string& preamble::prefix() {
    return prefix_;
}

void preamble::prefix(const std::string& v) {
    prefix_ = v;
}

void preamble::prefix(const std::string&& v) {
    prefix_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& preamble::fields() const {
    return fields_;
}

std::list<std::pair<std::string, std::string> >& preamble::fields() {
    return fields_;
}

void preamble::fields(const std::list<std::pair<std::string, std::string> >& v) {
    fields_ = v;
}

void preamble::fields(const std::list<std::pair<std::string, std::string> >&& v) {
    fields_ = std::move(v);
}

const std::string& preamble::kvp_separator() const {
    return kvp_separator_;
}

std::string& preamble::kvp_separator() {
    return kvp_separator_;
}

void preamble::kvp_separator(const std::string& v) {
    kvp_separator_ = v;
}

void preamble::kvp_separator(const std::string&& v) {
    kvp_separator_ = std::move(v);
}

const std::string& preamble::field_separator() const {
    return field_separator_;
}

std::string& preamble::field_separator() {
    return field_separator_;
}

void preamble::field_separator(const std::string& v) {
    field_separator_ = v;
}

void preamble::field_separator(const std::string&& v) {
    field_separator_ = std::move(v);
}

const std::string& preamble::postfix() const {
    return postfix_;
}

std::string& preamble::postfix() {
    return postfix_;
}

void preamble::postfix(const std::string& v) {
    postfix_ = v;
}

void preamble::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

} }