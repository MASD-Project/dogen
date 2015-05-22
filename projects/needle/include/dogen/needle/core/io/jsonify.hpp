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
#ifndef DOGEN_NEEDLE_CORE_IO_JSONIFY_HPP
#define DOGEN_NEEDLE_CORE_IO_JSONIFY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include <iomanip>
#include <boost/io/ios_state.hpp>
#include "dogen/needle/core/io/tidy_up.hpp"

namespace dogen {
namespace needle {
namespace core {
namespace io {

namespace detail {

template<typename Value>
class json_integer_type {
public:
    explicit json_integer_type(const Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    const Value value_;
};

template<typename Value>
class json_floating_type {
public:
    explicit json_floating_type(const Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    const Value value_;
};

template<typename Value>
class json_char_type {
public:
    explicit json_char_type(const Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    const Value value_;
};

template<typename Value>
class json_string_type {
public:
    explicit json_string_type(const Value& v) : value_(v) { }
    const Value& get() const { return value_; }

private:
    const Value& value_;
};

template<typename Value>
class json_bool_type {
public:
    explicit json_bool_type(const Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    const Value value_;
};

template<typename Value>
class json_complex_type {
public:
    explicit json_complex_type(const Value& v) : value_(v) { }
    const Value& get() const { return value_; }

private:
    const Value& value_;
};

} } } } }

namespace dogen {
namespace needle {
namespace core {
namespace io {

/**
 * @brief Integer handling.
 */
/*@{*/
inline detail::json_integer_type<unsigned int>
jsonify(const unsigned int v) {
    return detail::json_integer_type<unsigned int>(v);
}

inline detail::json_integer_type<int>
jsonify(const int v) {
    return detail::json_integer_type<int>(v);
}

inline detail::json_integer_type<unsigned short>
jsonify(const unsigned short v) {
    return detail::json_integer_type<unsigned short>(v);
}

inline detail::json_integer_type<short>
jsonify(const short v) {
    return detail::json_integer_type<short>(v);
}

inline detail::json_integer_type<unsigned long>
jsonify(const unsigned long v) {
    return detail::json_integer_type<unsigned long>(v);
}

inline detail::json_integer_type<long>
jsonify(const long v) {
    return detail::json_integer_type<long>(v);
}
/*@}*/

/**
 * @brief Floating handling.
 */
/*@{*/
inline detail::json_floating_type<float>
jsonify(const float v) {
    return detail::json_floating_type<float>(v);
}

inline detail::json_floating_type<double>
jsonify(const double v) {
    return detail::json_floating_type<double>(v);
}
/*@}*/

/**
 * @brief Char handling.
 */
/*@{*/
inline detail::json_char_type<unsigned char>
jsonify(const unsigned char v) {
    return detail::json_char_type<unsigned char>(v);
}

inline detail::json_char_type<char>
jsonify(const char v) {
    return detail::json_char_type<char>(v);
}
/*@}*/

/**
 * @brief String handling.
 */
inline detail::json_string_type<std::string>
jsonify(const std::string& v) {
    return detail::json_string_type<std::string>(v);
}

/**
 * @brief Bool handling.
 */
inline detail::json_bool_type<bool>
jsonify(const bool v) {
    return detail::json_bool_type<bool>(v);
}

/**
 * @brief Handling of any other object.
 */
template<typename Value>
inline detail::json_complex_type<Value>
jsonify(const Value& v) {
    return detail::json_complex_type<Value>(v);
}

namespace detail {

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const json_integer_type<Value>& v) {
    s << v.get();
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const json_floating_type<Value>& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.setf(std::ios::showpoint);
    s.precision(6);
    s << v.get();
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const json_char_type<Value>& v) {
    boost::io::ios_flags_saver ifs(s);
    s.precision(2);
    s << "\"" << "0x" << std::setfill('0') << std::setw(2) << std::hex
      << static_cast<unsigned int>(v.get()) << "\"";
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const json_string_type<Value>& v) {
    s << "\"" << tidy_up_copy(v.get()) << "\"";
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const json_bool_type<Value>& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s << v.get();
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const json_complex_type<Value>& v) {
    s << v.get();
    return s;
}

} } } } }

#endif
