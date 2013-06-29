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
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

qname::qname()
    : meta_type_(static_cast<dogen::sml::meta_types>(0)) { }

qname::qname(
    const std::string& model_name,
    const std::list<std::string>& external_module_path,
    const std::list<std::string>& module_path,
    const std::string& simple_name,
    const dogen::sml::meta_types& meta_type)
    : model_name_(model_name),
      external_module_path_(external_module_path),
      module_path_(module_path),
      simple_name_(simple_name),
      meta_type_(meta_type) { }

void qname::swap(qname& other) noexcept {
    using std::swap;
    swap(model_name_, other.model_name_);
    swap(external_module_path_, other.external_module_path_);
    swap(module_path_, other.module_path_);
    swap(simple_name_, other.simple_name_);
    swap(meta_type_, other.meta_type_);
}

bool qname::operator==(const qname& rhs) const {
    return model_name_ == rhs.model_name_ &&
        external_module_path_ == rhs.external_module_path_ &&
        module_path_ == rhs.module_path_ &&
        simple_name_ == rhs.simple_name_ &&
        meta_type_ == rhs.meta_type_;
}

qname& qname::operator=(qname other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& qname::model_name() const {
    return model_name_;
}

std::string& qname::model_name() {
    return model_name_;
}

void qname::model_name(const std::string& v) {
    model_name_ = v;
}

void qname::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

const std::list<std::string>& qname::external_module_path() const {
    return external_module_path_;
}

std::list<std::string>& qname::external_module_path() {
    return external_module_path_;
}

void qname::external_module_path(const std::list<std::string>& v) {
    external_module_path_ = v;
}

void qname::external_module_path(const std::list<std::string>&& v) {
    external_module_path_ = std::move(v);
}

const std::list<std::string>& qname::module_path() const {
    return module_path_;
}

std::list<std::string>& qname::module_path() {
    return module_path_;
}

void qname::module_path(const std::list<std::string>& v) {
    module_path_ = v;
}

void qname::module_path(const std::list<std::string>&& v) {
    module_path_ = std::move(v);
}

const std::string& qname::simple_name() const {
    return simple_name_;
}

std::string& qname::simple_name() {
    return simple_name_;
}

void qname::simple_name(const std::string& v) {
    simple_name_ = v;
}

void qname::simple_name(const std::string&& v) {
    simple_name_ = std::move(v);
}

dogen::sml::meta_types qname::meta_type() const {
    return meta_type_;
}

void qname::meta_type(const dogen::sml::meta_types& v) {
    meta_type_ = v;
}

} }