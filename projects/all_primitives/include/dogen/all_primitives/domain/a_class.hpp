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
#include <iosfwd>
#include "dogen/all_primitives/domain/versioned_key.hpp"

namespace dogen {
namespace all_primitives {

class a_class_serializer;

class a_class {
public:
    a_class(const a_class&) = default;
    ~a_class() = default;
    a_class(a_class&&) = default;

public:
    a_class();

public:
    a_class(
        bool bool_property,
        char char_property,
        unsigned char uchar_property,
        int int_property,
        unsigned int uint_property,
        long long_property,
        unsigned long ulong_property,
        long long long_long_property,
        unsigned long long ulong_long_property,
        short short_property,
        unsigned short ushort_property,
        dogen::all_primitives::versioned_key versioned_key);

public:
    friend class dogen::all_primitives::a_class_serializer;

public:
    void to_stream(std::ostream& stream) const;

public:
    bool bool_property() const {
        return bool_property_;
    }

    void bool_property(bool value) {
        bool_property_ = value;
    }

    char char_property() const {
        return char_property_;
    }

    void char_property(char value) {
        char_property_ = value;
    }

    unsigned char uchar_property() const {
        return uchar_property_;
    }

    void uchar_property(unsigned char value) {
        uchar_property_ = value;
    }

    int int_property() const {
        return int_property_;
    }

    void int_property(int value) {
        int_property_ = value;
    }

    unsigned int uint_property() const {
        return uint_property_;
    }

    void uint_property(unsigned int value) {
        uint_property_ = value;
    }

    long long_property() const {
        return long_property_;
    }

    void long_property(long value) {
        long_property_ = value;
    }

    unsigned long ulong_property() const {
        return ulong_property_;
    }

    void ulong_property(unsigned long value) {
        ulong_property_ = value;
    }

    long long long_long_property() const {
        return long_long_property_;
    }

    void long_long_property(long long value) {
        long_long_property_ = value;
    }

    unsigned long long ulong_long_property() const {
        return ulong_long_property_;
    }

    void ulong_long_property(unsigned long long value) {
        ulong_long_property_ = value;
    }

    short short_property() const {
        return short_property_;
    }

    void short_property(short value) {
        short_property_ = value;
    }

    unsigned short ushort_property() const {
        return ushort_property_;
    }

    void ushort_property(unsigned short value) {
        ushort_property_ = value;
    }

    dogen::all_primitives::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(dogen::all_primitives::versioned_key value) {
        versioned_key_ = value;
    }

public:
    bool operator==(const a_class& rhs) const;

    bool operator!=(const a_class rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(a_class& other);
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
