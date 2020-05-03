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
#include "dogen.text/types/formatters/infix_configuration.hpp"

namespace dogen::text::formatters {

infix_configuration::infix_configuration(
    const std::string& first,
    const std::string& not_first,
    const std::string& not_last,
    const std::string& last)
    : first_(first),
      not_first_(not_first),
      not_last_(not_last),
      last_(last) { }

void infix_configuration::swap(infix_configuration& other) noexcept {
    using std::swap;
    swap(first_, other.first_);
    swap(not_first_, other.not_first_);
    swap(not_last_, other.not_last_);
    swap(last_, other.last_);
}

bool infix_configuration::operator==(const infix_configuration& rhs) const {
    return first_ == rhs.first_ &&
        not_first_ == rhs.not_first_ &&
        not_last_ == rhs.not_last_ &&
        last_ == rhs.last_;
}

infix_configuration& infix_configuration::operator=(infix_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& infix_configuration::first() const {
    return first_;
}

std::string& infix_configuration::first() {
    return first_;
}

infix_configuration& infix_configuration::first(const std::string& v) {
    first_ = v;
    return *this;
}

infix_configuration& infix_configuration::first(const std::string&& v) {
    first_ = std::move(v);
    return *this;
}

const std::string& infix_configuration::not_first() const {
    return not_first_;
}

std::string& infix_configuration::not_first() {
    return not_first_;
}

infix_configuration& infix_configuration::not_first(const std::string& v) {
    not_first_ = v;
    return *this;
}

infix_configuration& infix_configuration::not_first(const std::string&& v) {
    not_first_ = std::move(v);
    return *this;
}

const std::string& infix_configuration::not_last() const {
    return not_last_;
}

std::string& infix_configuration::not_last() {
    return not_last_;
}

infix_configuration& infix_configuration::not_last(const std::string& v) {
    not_last_ = v;
    return *this;
}

infix_configuration& infix_configuration::not_last(const std::string&& v) {
    not_last_ = std::move(v);
    return *this;
}

const std::string& infix_configuration::last() const {
    return last_;
}

std::string& infix_configuration::last() {
    return last_;
}

infix_configuration& infix_configuration::last(const std::string& v) {
    last_ = v;
    return *this;
}

infix_configuration& infix_configuration::last(const std::string&& v) {
    last_ = std::move(v);
    return *this;
}

}
