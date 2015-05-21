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
#ifndef DOGEN_NEEDLE_CORE_IO_JSONIFY_IO_HPP
#define DOGEN_NEEDLE_CORE_IO_JSONIFY_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include <boost/io/ios_state.hpp>

namespace dogen {
namespace needle {
namespace core {
namespace io {

namespace detail {

template<typename Target>
class json_integer_type {
public:
    explicit json_integer_type(const Target target) : target_(target) { }
    Target get() const { return(target_); }

private:
    const Target target_;
};

template<typename Target>
class json_floating_type {
public:
    explicit json_floating_type(const Target target) : target_(target) { }
    Target get() const { return(target_); }

private:
    const Target target_;
};

template<typename Target>
class json_char_type {
public:
    explicit json_char_type(const Target target) : target_(target) { }
    Target get() const { return(target_); }

private:
    const Target target_;
};

template<typename Target>
class json_string_type {
public:
    explicit json_string_type(const Target& target) : target_(target) { }
    const Target& get() const { return(target_); }

private:
    const Target& target_;
};

template<typename Target>
class json_complex_type {
public:
    explicit json_complex_type(const Target& target) : target_(target) { }
    const Target& get() const { return(target_); }

private:
    const Target& target_;
};

} } } } }

namespace dogen {
namespace needle {
namespace core {
namespace io {

/**
 * @brief String handling.
 */
inline detail::json_string_type<std::string>
jsonify(const std::string& insertee) {
    return(detail::json_string_type<std::string>(insertee));
}

/**
 * @brief Char handling.
 */
/*@{*/
inline detail::json_char_type<unsigned char>
jsonify(const unsigned char insertee) {
    return(detail::json_char_type<unsigned char>(insertee));
}

inline detail::json_char_type<char>
jsonify(const char insertee) {
    return(detail::json_char_type<char>(insertee));
}
/*@}*/

/**
 * @brief Integer handling.
 */
/*@{*/
inline detail::json_integer_type<unsigned int>
jsonify(const unsigned int insertee) {
    return(detail::json_integer_type<unsigned int>(insertee));
}

inline detail::json_integer_type<int>
jsonify(const int insertee) {
    return(detail::json_integer_type<int>(insertee));
}

inline detail::json_integer_type<unsigned short>
jsonify(const unsigned short insertee) {
    return(detail::json_integer_type<unsigned short>(insertee));
}

inline detail::json_integer_type<short>
jsonify(const short insertee) {
    return(detail::json_integer_type<short>(insertee));
}

inline detail::json_integer_type<unsigned long>
jsonify(const unsigned long insertee) {
    return(detail::json_integer_type<unsigned long>(insertee));
}

inline detail::json_integer_type<long>
jsonify(const long insertee) {
    return(detail::json_integer_type<long>(insertee));
}
/*@}*/

/**
 * @brief Floating handling.
 */
/*@{*/
inline detail::json_floating_type<float>
jsonify(const float insertee) {
    return(detail::json_floating_type<float>(insertee));
}

inline detail::json_floating_type<double>
jsonify(const double insertee) {
    return(detail::json_floating_type<double>(insertee));
}
/*@}*/

/**
 * @brief Handling of any other object.
 */
template<typename Insertee>
inline detail::json_complex_type<Insertee>
jsonify(const Insertee& insertee) {
    return(detail::json_complex_type<Insertee>(insertee));
}

namespace detail {

template<typename Target>
inline std::ostream&
operator<<(std::ostream& stream, const json_string_type<Target>& target) {
    stream << "\"" << target.get() << "\"";
    return(stream);
}

template<typename Target>
inline std::ostream&
operator<<(std::ostream& stream, const json_char_type<Target>& target) {
    stream << "\"" << target.get() << "\"";
    return(stream);
}

template<typename Target>
inline std::ostream&
operator<<(std::ostream& stream, const json_integer_type<Target>& target) {
    stream << target.get();
    return(stream);
}

template<typename Target>
inline std::ostream&
operator<<(std::ostream& s, const json_floating_type<Target>& t) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.setf(std::ios::showpoint);
    s.precision(6);
    s << t.get();
    return s;
}

template<typename Target>
inline std::ostream&
operator<<(std::ostream& stream, const json_complex_type<Target>& target) {
    stream << target.get();
    return(stream);
}

} } } } }

#endif
