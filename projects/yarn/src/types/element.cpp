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
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/dynamic/io/object_io.hpp"
#include "dogen/yarn/io/origin_types_io.hpp"
#include "dogen/yarn/io/generation_types_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::yarn::name>& v) {
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
namespace yarn {

element::element()
    : in_global_namespace_(static_cast<bool>(0)),
      generation_type_(static_cast<dogen::yarn::generation_types>(0)),
      origin_type_(static_cast<dogen::yarn::origin_types>(0)) { }

element::element(element&& rhs)
    : in_global_namespace_(std::move(rhs.in_global_namespace_)),
      documentation_(std::move(rhs.documentation_)),
      extensions_(std::move(rhs.extensions_)),
      name_(std::move(rhs.name_)),
      generation_type_(std::move(rhs.generation_type_)),
      origin_type_(std::move(rhs.origin_type_)),
      original_model_name_(std::move(rhs.original_model_name_)),
      containing_module_(std::move(rhs.containing_module_)) { }

element::element(
    const bool in_global_namespace,
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const std::string& original_model_name,
    const boost::optional<dogen::yarn::name>& containing_module)
    : in_global_namespace_(in_global_namespace),
      documentation_(documentation),
      extensions_(extensions),
      name_(name),
      generation_type_(generation_type),
      origin_type_(origin_type),
      original_model_name_(original_model_name),
      containing_module_(containing_module) { }

void element::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::element\"" << ", "
      << "\"in_global_namespace\": " << in_global_namespace_ << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"extensions\": " << extensions_ << ", "
      << "\"name\": " << name_ << ", "
      << "\"generation_type\": " << generation_type_ << ", "
      << "\"origin_type\": " << origin_type_ << ", "
      << "\"original_model_name\": " << "\"" << tidy_up_string(original_model_name_) << "\"" << ", "
      << "\"containing_module\": " << containing_module_
      << " }";
}

void element::swap(element& other) noexcept {
    using std::swap;
    swap(in_global_namespace_, other.in_global_namespace_);
    swap(documentation_, other.documentation_);
    swap(extensions_, other.extensions_);
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
    swap(origin_type_, other.origin_type_);
    swap(original_model_name_, other.original_model_name_);
    swap(containing_module_, other.containing_module_);
}

bool element::compare(const element& rhs) const {
    return in_global_namespace_ == rhs.in_global_namespace_ &&
        documentation_ == rhs.documentation_ &&
        extensions_ == rhs.extensions_ &&
        name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_ &&
        origin_type_ == rhs.origin_type_ &&
        original_model_name_ == rhs.original_model_name_ &&
        containing_module_ == rhs.containing_module_;
}

bool element::in_global_namespace() const {
    return in_global_namespace_;
}

void element::in_global_namespace(const bool v) {
    in_global_namespace_ = v;
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

const dogen::dynamic::object& element::extensions() const {
    return extensions_;
}

dogen::dynamic::object& element::extensions() {
    return extensions_;
}

void element::extensions(const dogen::dynamic::object& v) {
    extensions_ = v;
}

void element::extensions(const dogen::dynamic::object&& v) {
    extensions_ = std::move(v);
}

const dogen::yarn::name& element::name() const {
    return name_;
}

dogen::yarn::name& element::name() {
    return name_;
}

void element::name(const dogen::yarn::name& v) {
    name_ = v;
}

void element::name(const dogen::yarn::name&& v) {
    name_ = std::move(v);
}

dogen::yarn::generation_types element::generation_type() const {
    return generation_type_;
}

void element::generation_type(const dogen::yarn::generation_types v) {
    generation_type_ = v;
}

dogen::yarn::origin_types element::origin_type() const {
    return origin_type_;
}

void element::origin_type(const dogen::yarn::origin_types v) {
    origin_type_ = v;
}

const std::string& element::original_model_name() const {
    return original_model_name_;
}

std::string& element::original_model_name() {
    return original_model_name_;
}

void element::original_model_name(const std::string& v) {
    original_model_name_ = v;
}

void element::original_model_name(const std::string&& v) {
    original_model_name_ = std::move(v);
}

const boost::optional<dogen::yarn::name>& element::containing_module() const {
    return containing_module_;
}

boost::optional<dogen::yarn::name>& element::containing_module() {
    return containing_module_;
}

void element::containing_module(const boost::optional<dogen::yarn::name>& v) {
    containing_module_ = v;
}

void element::containing_module(const boost::optional<dogen::yarn::name>&& v) {
    containing_module_ = std::move(v);
}

} }
