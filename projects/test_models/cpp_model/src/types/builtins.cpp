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
#include "dogen/test_models/cpp_model/types/builtins.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

builtins::builtins()
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

builtins::builtins(
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
    const float float_property)
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
      float_property_(float_property) { }

void builtins::swap(builtins& other) noexcept {
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
}

bool builtins::operator==(const builtins& rhs) const {
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
        float_property_ == rhs.float_property_;
}

builtins& builtins::operator=(builtins other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool builtins::bool_property() const {
    return bool_property_;
}

void builtins::bool_property(const bool v) {
    bool_property_ = v;
}

char builtins::char_property() const {
    return char_property_;
}

void builtins::char_property(const char v) {
    char_property_ = v;
}

unsigned char builtins::uchar_property() const {
    return uchar_property_;
}

void builtins::uchar_property(const unsigned char v) {
    uchar_property_ = v;
}

int builtins::int_property() const {
    return int_property_;
}

void builtins::int_property(const int v) {
    int_property_ = v;
}

unsigned int builtins::uint_property() const {
    return uint_property_;
}

void builtins::uint_property(const unsigned int v) {
    uint_property_ = v;
}

long builtins::long_property() const {
    return long_property_;
}

void builtins::long_property(const long v) {
    long_property_ = v;
}

unsigned long builtins::ulong_property() const {
    return ulong_property_;
}

void builtins::ulong_property(const unsigned long v) {
    ulong_property_ = v;
}

long long builtins::long_long_property() const {
    return long_long_property_;
}

void builtins::long_long_property(const long long v) {
    long_long_property_ = v;
}

unsigned long long builtins::ulong_long_property() const {
    return ulong_long_property_;
}

void builtins::ulong_long_property(const unsigned long long v) {
    ulong_long_property_ = v;
}

short builtins::short_property() const {
    return short_property_;
}

void builtins::short_property(const short v) {
    short_property_ = v;
}

unsigned short builtins::ushort_property() const {
    return ushort_property_;
}

void builtins::ushort_property(const unsigned short v) {
    ushort_property_ = v;
}

double builtins::double_property() const {
    return double_property_;
}

void builtins::double_property(const double v) {
    double_property_ = v;
}

float builtins::float_property() const {
    return float_property_;
}

void builtins::float_property(const float v) {
    float_property_ = v;
}

} } }
