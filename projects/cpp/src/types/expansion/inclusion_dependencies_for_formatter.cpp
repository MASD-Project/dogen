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
#include "dogen/cpp/types/expansion/inclusion_dependencies_for_formatter.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

inclusion_dependencies_for_formatter::inclusion_dependencies_for_formatter(
    const std::string& formatter_name,
    const std::list<std::string>& inclusion_dependencies)
    : formatter_name_(formatter_name),
      inclusion_dependencies_(inclusion_dependencies) { }

void inclusion_dependencies_for_formatter::swap(inclusion_dependencies_for_formatter& other) noexcept {
    using std::swap;
    swap(formatter_name_, other.formatter_name_);
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
}

bool inclusion_dependencies_for_formatter::operator==(const inclusion_dependencies_for_formatter& rhs) const {
    return formatter_name_ == rhs.formatter_name_ &&
        inclusion_dependencies_ == rhs.inclusion_dependencies_;
}

inclusion_dependencies_for_formatter& inclusion_dependencies_for_formatter::operator=(inclusion_dependencies_for_formatter other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& inclusion_dependencies_for_formatter::formatter_name() const {
    return formatter_name_;
}

std::string& inclusion_dependencies_for_formatter::formatter_name() {
    return formatter_name_;
}

void inclusion_dependencies_for_formatter::formatter_name(const std::string& v) {
    formatter_name_ = v;
}

void inclusion_dependencies_for_formatter::formatter_name(const std::string&& v) {
    formatter_name_ = std::move(v);
}

const std::list<std::string>& inclusion_dependencies_for_formatter::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<std::string>& inclusion_dependencies_for_formatter::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void inclusion_dependencies_for_formatter::inclusion_dependencies(const std::list<std::string>& v) {
    inclusion_dependencies_ = v;
}

void inclusion_dependencies_for_formatter::inclusion_dependencies(const std::list<std::string>&& v) {
    inclusion_dependencies_ = std::move(v);
}

} } }