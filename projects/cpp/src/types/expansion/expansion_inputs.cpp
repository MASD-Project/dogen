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
#include "dogen/cpp/types/expansion/expansion_inputs.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

expansion_inputs::expansion_inputs(
    const dogen::cpp::expansion::path_derivatives& path_derivatives,
    const std::list<std::string>& inclusion_dependencies_by_formatter_name)
    : path_derivatives_(path_derivatives),
      inclusion_dependencies_by_formatter_name_(inclusion_dependencies_by_formatter_name) { }

void expansion_inputs::swap(expansion_inputs& other) noexcept {
    using std::swap;
    swap(path_derivatives_, other.path_derivatives_);
    swap(inclusion_dependencies_by_formatter_name_, other.inclusion_dependencies_by_formatter_name_);
}

bool expansion_inputs::operator==(const expansion_inputs& rhs) const {
    return path_derivatives_ == rhs.path_derivatives_ &&
        inclusion_dependencies_by_formatter_name_ == rhs.inclusion_dependencies_by_formatter_name_;
}

expansion_inputs& expansion_inputs::operator=(expansion_inputs other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::cpp::expansion::path_derivatives& expansion_inputs::path_derivatives() const {
    return path_derivatives_;
}

dogen::cpp::expansion::path_derivatives& expansion_inputs::path_derivatives() {
    return path_derivatives_;
}

void expansion_inputs::path_derivatives(const dogen::cpp::expansion::path_derivatives& v) {
    path_derivatives_ = v;
}

void expansion_inputs::path_derivatives(const dogen::cpp::expansion::path_derivatives&& v) {
    path_derivatives_ = std::move(v);
}

const std::list<std::string>& expansion_inputs::inclusion_dependencies_by_formatter_name() const {
    return inclusion_dependencies_by_formatter_name_;
}

std::list<std::string>& expansion_inputs::inclusion_dependencies_by_formatter_name() {
    return inclusion_dependencies_by_formatter_name_;
}

void expansion_inputs::inclusion_dependencies_by_formatter_name(const std::list<std::string>& v) {
    inclusion_dependencies_by_formatter_name_ = v;
}

void expansion_inputs::inclusion_dependencies_by_formatter_name(const std::list<std::string>&& v) {
    inclusion_dependencies_by_formatter_name_ = std::move(v);
}

} } }