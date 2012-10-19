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
#ifndef DOGEN_ALL_PRIMITIVES_DOMAIN_A_CLASS_HPP
#define DOGEN_ALL_PRIMITIVES_DOMAIN_A_CLASS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/all_primitives/domain/versioned_key.hpp"

namespace dogen {
namespace all_primitives {

class a_class_serializer;

class a_class final {
public:
    a_class(const a_class&) = default;
    a_class(a_class&&) = default;
    ~a_class() = default;

public:
    a_class();

public:
    a_class(
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
        const dogen::all_primitives::versioned_key& versioned_key);

public:
    friend class dogen::all_primitives::a_class_serializer;

public:
    bool bool_property() const {
        return bool_property_;
    }

    void bool_property(const bool v) {
        bool_property_ = v;
    }

    char char_property() const {
        return char_property_;
    }

    void char_property(const char v) {
        char_property_ = v;
    }

    unsigned char uchar_property() const {
        return uchar_property_;
    }

    void uchar_property(const unsigned char v) {
        uchar_property_ = v;
    }

    int int_property() const {
        return int_property_;
    }

    void int_property(const int v) {
        int_property_ = v;
    }

    unsigned int uint_property() const {
        return uint_property_;
    }

    void uint_property(const unsigned int v) {
        uint_property_ = v;
    }

    long long_property() const {
        return long_property_;
    }

    void long_property(const long v) {
        long_property_ = v;
    }

    unsigned long ulong_property() const {
        return ulong_property_;
    }

    void ulong_property(const unsigned long v) {
        ulong_property_ = v;
    }

    long long long_long_property() const {
        return long_long_property_;
    }

    void long_long_property(const long long v) {
        long_long_property_ = v;
    }

    unsigned long long ulong_long_property() const {
        return ulong_long_property_;
    }

    void ulong_long_property(const unsigned long long v) {
        ulong_long_property_ = v;
    }

    short short_property() const {
        return short_property_;
    }

    void short_property(const short v) {
        short_property_ = v;
    }

    unsigned short ushort_property() const {
        return ushort_property_;
    }

    void ushort_property(const unsigned short v) {
        ushort_property_ = v;
    }

    dogen::all_primitives::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::all_primitives::versioned_key& v) {
        versioned_key_ = v;
    }

public:
    bool operator==(const a_class& rhs) const;
    bool operator!=(const a_class& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(a_class& other) noexcept;
    a_class& operator=(a_class other);

private:
    bool bool_property_;
    char char_property_;
    unsigned char uchar_property_;
    int int_property_;
    unsigned int uint_property_;
    long long_property_;
    unsigned long ulong_property_;
    long long long_long_property_;
    unsigned long long ulong_long_property_;
    short short_property_;
    unsigned short ushort_property_;
    dogen::all_primitives::versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::all_primitives::a_class& lhs,
    dogen::all_primitives::a_class& rhs) {
    lhs.swap(rhs);
}

}

#endif
