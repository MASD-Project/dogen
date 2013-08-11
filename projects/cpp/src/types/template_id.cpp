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
#include "dogen/cpp/types/template_id.hpp"

namespace dogen {
namespace cpp {

template_id::template_id(
    const std::string& template_name,
    const std::list<dogen::cpp::template_argument>& template_argument_list)
    : template_name_(template_name),
      template_argument_list_(template_argument_list) { }

void template_id::swap(template_id& other) noexcept {
    using std::swap;
    swap(template_name_, other.template_name_);
    swap(template_argument_list_, other.template_argument_list_);
}

bool template_id::operator==(const template_id& rhs) const {
    return template_name_ == rhs.template_name_ &&
        template_argument_list_ == rhs.template_argument_list_;
}

template_id& template_id::operator=(template_id other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& template_id::template_name() const {
    return template_name_;
}

std::string& template_id::template_name() {
    return template_name_;
}

void template_id::template_name(const std::string& v) {
    template_name_ = v;
}

void template_id::template_name(const std::string&& v) {
    template_name_ = std::move(v);
}

const std::list<dogen::cpp::template_argument>& template_id::template_argument_list() const {
    return template_argument_list_;
}

std::list<dogen::cpp::template_argument>& template_id::template_argument_list() {
    return template_argument_list_;
}

void template_id::template_argument_list(const std::list<dogen::cpp::template_argument>& v) {
    template_argument_list_ = v;
}

void template_id::template_argument_list(const std::list<dogen::cpp::template_argument>&& v) {
    template_argument_list_ = std::move(v);
}

} }