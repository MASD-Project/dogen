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
#include "dogen/cpp/io/formattables/file_settings_io.hpp"
#include "dogen/cpp/types/formattables/entity.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::cpp::formattables::file_settings>& v) {
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
namespace cpp {
namespace formattables {

entity::entity(
    const std::string& name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const std::unordered_map<std::string, dogen::cpp::formattables::file_settings>& file_settings_for_formatter)
    : name_(name),
      documentation_(documentation),
      namespaces_(namespaces),
      file_settings_for_formatter_(file_settings_for_formatter) { }

void entity::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::entity\"" << ", "
      << "\"name\": " << "\"" << tidy_up_string(name_) << "\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"namespaces\": " << namespaces_ << ", "
      << "\"file_settings_for_formatter\": " << file_settings_for_formatter_
      << " }";
}

void entity::swap(entity& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
    swap(namespaces_, other.namespaces_);
    swap(file_settings_for_formatter_, other.file_settings_for_formatter_);
}

bool entity::compare(const entity& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_ &&
        namespaces_ == rhs.namespaces_ &&
        file_settings_for_formatter_ == rhs.file_settings_for_formatter_;
}

const std::string& entity::name() const {
    return name_;
}

std::string& entity::name() {
    return name_;
}

void entity::name(const std::string& v) {
    name_ = v;
}

void entity::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& entity::documentation() const {
    return documentation_;
}

std::string& entity::documentation() {
    return documentation_;
}

void entity::documentation(const std::string& v) {
    documentation_ = v;
}

void entity::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::list<std::string>& entity::namespaces() const {
    return namespaces_;
}

std::list<std::string>& entity::namespaces() {
    return namespaces_;
}

void entity::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void entity::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::unordered_map<std::string, dogen::cpp::formattables::file_settings>& entity::file_settings_for_formatter() const {
    return file_settings_for_formatter_;
}

std::unordered_map<std::string, dogen::cpp::formattables::file_settings>& entity::file_settings_for_formatter() {
    return file_settings_for_formatter_;
}

void entity::file_settings_for_formatter(const std::unordered_map<std::string, dogen::cpp::formattables::file_settings>& v) {
    file_settings_for_formatter_ = v;
}

void entity::file_settings_for_formatter(const std::unordered_map<std::string, dogen::cpp::formattables::file_settings>&& v) {
    file_settings_for_formatter_ = std::move(v);
}

} } }