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
#include "dogen/upsilon/types/output.hpp"

namespace dogen {
namespace upsilon {

output::output(
    const std::string& schema_name,
    const std::vector<dogen::upsilon::representation>& representations)
    : schema_name_(schema_name),
      representations_(representations) { }

void output::swap(output& other) noexcept {
    using std::swap;
    swap(schema_name_, other.schema_name_);
    swap(representations_, other.representations_);
}

bool output::operator==(const output& rhs) const {
    return schema_name_ == rhs.schema_name_ &&
        representations_ == rhs.representations_;
}

output& output::operator=(output other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& output::schema_name() const {
    return schema_name_;
}

std::string& output::schema_name() {
    return schema_name_;
}

void output::schema_name(const std::string& v) {
    schema_name_ = v;
}

void output::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const std::vector<dogen::upsilon::representation>& output::representations() const {
    return representations_;
}

std::vector<dogen::upsilon::representation>& output::representations() {
    return representations_;
}

void output::representations(const std::vector<dogen::upsilon::representation>& v) {
    representations_ = v;
}

void output::representations(const std::vector<dogen::upsilon::representation>&& v) {
    representations_ = std::move(v);
}

} }
