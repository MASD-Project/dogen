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
#ifndef DOGEN_NEEDLE_BOOST_IO_POSIX_TIME_IO_HPP
#define DOGEN_NEEDLE_BOOST_IO_POSIX_TIME_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen/needle/core/io/jsonify.hpp"

namespace dogen {
namespace needle {
namespace core {
namespace io {

namespace detail {

template<typename Value>
class json_boost_posix_time_type {
public:
    explicit json_boost_posix_time_type(const Value& v) : value_(v) { }
    const Value& get() const { return value_; }

private:
    const Value& value_;
};

}

inline detail::json_boost_posix_time_type<boost::posix_time::ptime>
jsonify(const boost::posix_time::ptime& v) {
    return detail::json_boost_posix_time_type<boost::posix_time::ptime>(v);
}

inline detail::json_boost_posix_time_type<boost::posix_time::time_duration>
jsonify(const boost::posix_time::time_duration& v) {
    return detail::json_boost_posix_time_type<
        boost::posix_time::time_duration>(v);
}

namespace detail {

template<typename Value>
inline std::ostream& operator<<(std::ostream& s,
    const json_boost_posix_time_type<Value>& p) {
    s << "\"" << p.get() << "\"";
    return s;
}

} } } } }

#endif
