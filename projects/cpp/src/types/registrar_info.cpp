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
#include "dogen/cpp/types/registrar_info.hpp"

namespace dogen {
namespace cpp {

registrar_info::registrar_info(
    const std::list<std::string>& namespaces,
    const std::list<std::string>& leaves,
    const std::list<std::string>& model_dependencies)
    : namespaces_(namespaces),
      leaves_(leaves),
      model_dependencies_(model_dependencies) { }

void registrar_info::swap(registrar_info& other) noexcept {
    using std::swap;
    swap(namespaces_, other.namespaces_);
    swap(leaves_, other.leaves_);
    swap(model_dependencies_, other.model_dependencies_);
}

bool registrar_info::operator==(const registrar_info& rhs) const {
    return namespaces_ == rhs.namespaces_ &&
        leaves_ == rhs.leaves_ &&
        model_dependencies_ == rhs.model_dependencies_;
}

registrar_info& registrar_info::operator=(registrar_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& registrar_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& registrar_info::namespaces() {
    return namespaces_;
}

void registrar_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void registrar_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::list<std::string>& registrar_info::leaves() const {
    return leaves_;
}

std::list<std::string>& registrar_info::leaves() {
    return leaves_;
}

void registrar_info::leaves(const std::list<std::string>& v) {
    leaves_ = v;
}

void registrar_info::leaves(const std::list<std::string>&& v) {
    leaves_ = std::move(v);
}

const std::list<std::string>& registrar_info::model_dependencies() const {
    return model_dependencies_;
}

std::list<std::string>& registrar_info::model_dependencies() {
    return model_dependencies_;
}

void registrar_info::model_dependencies(const std::list<std::string>& v) {
    model_dependencies_ = v;
}

void registrar_info::model_dependencies(const std::list<std::string>&& v) {
    model_dependencies_ = std::move(v);
}

} }