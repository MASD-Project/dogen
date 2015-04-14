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
#include "dogen/stitch/types/stitching_settings.hpp"

namespace dogen {
namespace stitch {

stitching_settings::stitching_settings(const std::string& stream_variable_name)
    : stream_variable_name_(stream_variable_name) { }

void stitching_settings::swap(stitching_settings& other) noexcept {
    using std::swap;
    swap(stream_variable_name_, other.stream_variable_name_);
}

bool stitching_settings::operator==(const stitching_settings& rhs) const {
    return stream_variable_name_ == rhs.stream_variable_name_;
}

stitching_settings& stitching_settings::operator=(stitching_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& stitching_settings::stream_variable_name() const {
    return stream_variable_name_;
}

std::string& stitching_settings::stream_variable_name() {
    return stream_variable_name_;
}

void stitching_settings::stream_variable_name(const std::string& v) {
    stream_variable_name_ = v;
}

void stitching_settings::stream_variable_name(const std::string&& v) {
    stream_variable_name_ = std::move(v);
}

} }