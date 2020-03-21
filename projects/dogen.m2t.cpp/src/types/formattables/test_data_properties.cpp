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
#include "dogen.m2t.cpp/types/formattables/test_data_properties.hpp"

namespace dogen::m2t::cpp::formattables {

test_data_properties::test_data_properties()
    : maximum_size_(static_cast<unsigned int>(0)) { }

test_data_properties::test_data_properties(
    const unsigned int maximum_size,
    const std::string& prefix)
    : maximum_size_(maximum_size),
      prefix_(prefix) { }

void test_data_properties::swap(test_data_properties& other) noexcept {
    using std::swap;
    swap(maximum_size_, other.maximum_size_);
    swap(prefix_, other.prefix_);
}

bool test_data_properties::operator==(const test_data_properties& rhs) const {
    return maximum_size_ == rhs.maximum_size_ &&
        prefix_ == rhs.prefix_;
}

test_data_properties& test_data_properties::operator=(test_data_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

unsigned int test_data_properties::maximum_size() const {
    return maximum_size_;
}

void test_data_properties::maximum_size(const unsigned int v) {
    maximum_size_ = v;
}

const std::string& test_data_properties::prefix() const {
    return prefix_;
}

std::string& test_data_properties::prefix() {
    return prefix_;
}

void test_data_properties::prefix(const std::string& v) {
    prefix_ = v;
}

void test_data_properties::prefix(const std::string&& v) {
    prefix_ = std::move(v);
}

}
