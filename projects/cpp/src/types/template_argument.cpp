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
#include "dogen/cpp/types/template_argument.hpp"

namespace dogen {
namespace cpp {

template_argument::template_argument(const std::string& name)
    : name_(name) { }

void template_argument::swap(template_argument& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
}

bool template_argument::operator==(const template_argument& rhs) const {
    return name_ == rhs.name_;
}

template_argument& template_argument::operator=(template_argument other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& template_argument::name() const {
    return name_;
}

std::string& template_argument::name() {
    return name_;
}

void template_argument::name(const std::string& v) {
    name_ = v;
}

void template_argument::name(const std::string&& v) {
    name_ = std::move(v);
}

} }