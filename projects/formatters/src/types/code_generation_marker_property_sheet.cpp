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
#include "dogen/formatters/types/code_generation_marker_property_sheet.hpp"

namespace dogen {
namespace formatters {

code_generation_marker_property_sheet::code_generation_marker_property_sheet()
    : add_date_time_(static_cast<bool>(0)),
      add_warning_(static_cast<bool>(0)) { }

code_generation_marker_property_sheet::code_generation_marker_property_sheet(
    const bool add_date_time,
    const bool add_warning,
    const std::string& message)
    : add_date_time_(add_date_time),
      add_warning_(add_warning),
      message_(message) { }

void code_generation_marker_property_sheet::swap(code_generation_marker_property_sheet& other) noexcept {
    using std::swap;
    swap(add_date_time_, other.add_date_time_);
    swap(add_warning_, other.add_warning_);
    swap(message_, other.message_);
}

bool code_generation_marker_property_sheet::operator==(const code_generation_marker_property_sheet& rhs) const {
    return add_date_time_ == rhs.add_date_time_ &&
        add_warning_ == rhs.add_warning_ &&
        message_ == rhs.message_;
}

code_generation_marker_property_sheet& code_generation_marker_property_sheet::operator=(code_generation_marker_property_sheet other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool code_generation_marker_property_sheet::add_date_time() const {
    return add_date_time_;
}

void code_generation_marker_property_sheet::add_date_time(const bool v) {
    add_date_time_ = v;
}

bool code_generation_marker_property_sheet::add_warning() const {
    return add_warning_;
}

void code_generation_marker_property_sheet::add_warning(const bool v) {
    add_warning_ = v;
}

const std::string& code_generation_marker_property_sheet::message() const {
    return message_;
}

std::string& code_generation_marker_property_sheet::message() {
    return message_;
}

void code_generation_marker_property_sheet::message(const std::string& v) {
    message_ = v;
}

void code_generation_marker_property_sheet::message(const std::string&& v) {
    message_ = std::move(v);
}

} }