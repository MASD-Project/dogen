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
#include "dogen/options/types/input_options.hpp"

namespace dogen {
namespace options {

input_options::input_options(input_options&& rhs)
    : target_(std::move(rhs.target_)) { }

input_options::input_options(const boost::filesystem::path& target)
    : target_(target) { }

void input_options::swap(input_options& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
}

bool input_options::operator==(const input_options& rhs) const {
    return target_ == rhs.target_;
}

input_options& input_options::operator=(input_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& input_options::target() const {
    return target_;
}

boost::filesystem::path& input_options::target() {
    return target_;
}

void input_options::target(const boost::filesystem::path& v) {
    target_ = v;
}

void input_options::target(const boost::filesystem::path&& v) {
    target_ = std::move(v);
}

} }
