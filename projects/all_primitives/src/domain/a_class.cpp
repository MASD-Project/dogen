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
#include "dogen/all_primitives/domain/a_class.hpp"

namespace dogen {
namespace all_primitives {

a_class::a_class()
    : bool_property_(static_cast<bool>(0)),
      char_property_(static_cast<char>(0)),
      uchar_property_(static_cast<unsigned char>(0)),
      int_property_(static_cast<int>(0)),
      uint_property_(static_cast<unsigned int>(0)),
      long_property_(static_cast<long>(0)),
      ulong_property_(static_cast<unsigned long>(0)),
      long_long_property_(static_cast<long long>(0)),
      ulong_long_property_(static_cast<unsigned long long>(0)),
      short_property_(static_cast<short>(0)),
      ushort_property_(static_cast<unsigned short>(0)),
      double_property_(static_cast<double>(0)),
      float_property_(static_cast<float>(0)) { }

a_class::a_class(
    const bool bool_property,
    const char char_property,
    const unsigned char uchar_property,
    const int int_property,
    const unsigned int uint_property,
    const long long_property,
    const unsigned long ulong_property,
    const long long long_long_property,
    const unsigned long long ulong_long_property,
    const short short_property,
    const unsigned short ushort_property,
    const double double_property,
    const float float_property,
    const dogen::all_primitives::a_class_versioned_key& versioned_key)
    : bool_property_(bool_property),
      char_property_(char_property),
      uchar_property_(uchar_property),
      int_property_(int_property),
      uint_property_(uint_property),
      long_property_(long_property),
      ulong_property_(ulong_property),
      long_long_property_(long_long_property),
      ulong_long_property_(ulong_long_property),
      short_property_(short_property),
      ushort_property_(ushort_property),
      double_property_(double_property),
      float_property_(float_property),
      versioned_key_(versioned_key) { }

void a_class::swap(a_class& other) noexcept {
    using std::swap;
    swap(bool_property_, other.bool_property_);
    swap(char_property_, other.char_property_);
    swap(uchar_property_, other.uchar_property_);
    swap(int_property_, other.int_property_);
    swap(uint_property_, other.uint_property_);
    swap(long_property_, other.long_property_);
    swap(ulong_property_, other.ulong_property_);
    swap(long_long_property_, other.long_long_property_);
    swap(ulong_long_property_, other.ulong_long_property_);
    swap(short_property_, other.short_property_);
    swap(ushort_property_, other.ushort_property_);
    swap(double_property_, other.double_property_);
    swap(float_property_, other.float_property_);
    swap(versioned_key_, other.versioned_key_);
}

bool a_class::operator==(const a_class& rhs) const {
    return bool_property_ == rhs.bool_property_ &&
        char_property_ == rhs.char_property_ &&
        uchar_property_ == rhs.uchar_property_ &&
        int_property_ == rhs.int_property_ &&
        uint_property_ == rhs.uint_property_ &&
        long_property_ == rhs.long_property_ &&
        ulong_property_ == rhs.ulong_property_ &&
        long_long_property_ == rhs.long_long_property_ &&
        ulong_long_property_ == rhs.ulong_long_property_ &&
        short_property_ == rhs.short_property_ &&
        ushort_property_ == rhs.ushort_property_ &&
        double_property_ == rhs.double_property_ &&
        float_property_ == rhs.float_property_ &&
        versioned_key_ == rhs.versioned_key_;
}

a_class& a_class::operator=(a_class other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }