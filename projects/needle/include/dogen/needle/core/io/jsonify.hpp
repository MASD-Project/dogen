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
#include "dogen/needle/core/io/constants.hpp"

namespace dogen {
namespace needle {
namespace core {
namespace io {

namespace detail {

/**
 * @brief Do not perform any formatting at all.
 */
template<typename Value>
class no_op_formatting {
public:
    explicit no_op_formatting(Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    Value value_;
};

/**
 * @brief Setup formatting for floating point numbers.
 */
template<typename Value>
class float_formatting {
public:
    explicit float_formatting(Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    Value value_;
};

/**
 * @brief Output value as a quoted hexadecimal number.
 */
template<typename Value>
class quoted_hex_formatting {
public:
    explicit quoted_hex_formatting(Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    Value value_;
};

/**
 * @brief Output value quoted.
 */
template<typename Value>
class quoted_formatting {
public:
    explicit quoted_formatting(Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    Value value_;
};

/**
 * @brief First transform value with tidying function, then output it
 * quoted.
 */
template<typename Value>
class quoted_tidied_formatting {
public:
    explicit quoted_tidied_formatting(Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    Value value_;
};

/**
 * @brief Output value as either true or false (non-quoted).
 */
template<typename Value>
class truth_values_formatting {
public:
    explicit truth_values_formatting(Value v) : value_(v) { }
    Value get() const { return value_; }

private:
    Value value_;
};

/**
 * @brief Output values as an array.
 */
template<typename Value>
class array_formatting {
public:
    explicit array_formatting(const Value& v) : value_(v) { }
    const Value& get() const { return value_; }

private:
    const Value& value_;
};

} } } } }

/**
 * @brief Integer handling.
 */
/**@{*/
inline dogen::needle::core::io::detail::no_op_formatting<const unsigned int>
jsonify(const unsigned int v) {
    return dogen::needle::core::io::
        detail::no_op_formatting<const unsigned int>(v);
}

inline dogen::needle::core::io::detail::no_op_formatting<const int>
jsonify(const int v) {
    return dogen::needle::core::io::detail::no_op_formatting<const int>(v);
}

inline dogen::needle::core::io::detail::no_op_formatting<const unsigned short>
jsonify(const unsigned short v) {
    return dogen::needle::core::io::
        detail::no_op_formatting<const unsigned short>(v);
}

inline dogen::needle::core::io::detail::no_op_formatting<const short>
jsonify(const short v) {
    return dogen::needle::core::io::detail::no_op_formatting<const short>(v);
}

inline dogen::needle::core::io::detail::no_op_formatting<const unsigned long>
jsonify(const unsigned long v) {
    return dogen::needle::core::io::
        detail::no_op_formatting<const unsigned long>(v);
}

inline dogen::needle::core::io::detail::no_op_formatting<const long>
jsonify(const long v) {
    return dogen::needle::core::io::detail::no_op_formatting<const long>(v);
}
/**@}*/

/**
 * @brief Floating handling.
 */
/**@{*/
inline dogen::needle::core::io::detail::float_formatting<const float>
jsonify(const float v) {
    return dogen::needle::core::io::detail::float_formatting<const float>(v);
}

inline dogen::needle::core::io::detail::float_formatting<const double>
jsonify(const double v) {
    return dogen::needle::core::io::detail::float_formatting<const double>(v);
}
/**@}*/

/**
 * @brief Char handling.
 */
/**@{*/
inline dogen::needle::core::io::
detail::quoted_hex_formatting<const unsigned char>
jsonify(const unsigned char v) {
    return dogen::needle::core::io::
        detail::quoted_hex_formatting<const unsigned char>(v);
}

inline dogen::needle::core::io::detail::quoted_hex_formatting<const char>
jsonify(const char v) {
    return dogen::needle::core::io::
        detail::quoted_hex_formatting<const char>(v);
}
/**@}*/

/**
 * @brief Bool handling.
 */
inline dogen::needle::core::io::detail::truth_values_formatting<const bool>
jsonify(const bool v) {
    return dogen::needle::core::io::
        detail::truth_values_formatting<const bool>(v);
}

namespace dogen {
namespace needle {
namespace core {
namespace io {

namespace detail {

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const no_op_formatting<Value>& v) {
    s << v.get();
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const float_formatting<Value>& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.setf(std::ios::showpoint);
    s.precision(6);
    s << v.get();
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const quoted_hex_formatting<Value>& v) {
    boost::io::ios_flags_saver ifs(s);
    s.precision(2);
    s << "\"" << "0x" << std::setfill('0') << std::setw(2) << std::hex
      << static_cast<unsigned int>(v.get()) << "\"";
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const quoted_formatting<Value>& v) {
    s << "\"" << v.get() << "\"";
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const quoted_tidied_formatting<Value>& v) {
    s << "\"" << tidy_up_copy(v.get()) << "\"";
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const truth_values_formatting<Value>& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s << v.get();
    return s;
}

template<typename Value>
inline std::ostream&
operator<<(std::ostream& s, const array_formatting<Value>& v) {
    s << constants::open_array();
    const auto c(v.get());
    for(auto i(c.cbegin()); i != c.end(); ++i) {
        if (i != c.begin())
            s << constants::separator();
        s << jsonify(*i);
    }
    s << constants::close_array();
    return s;
}

} } } } }

#endif
