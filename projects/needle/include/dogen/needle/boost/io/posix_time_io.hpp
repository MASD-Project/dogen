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
#ifndef DOGEN_NEEDLE_BOOST_IO_VARIANT_IO_HPP
#define DOGEN_NEEDLE_BOOST_IO_VARIANT_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <boost/variant.hpp>
#include "dogen/needle/core/io/jsonify.hpp"

namespace dogen {
namespace needle {
namespace core {
namespace io {

namespace detail {

template<typename Value>
class json_boost_variant_type {
public:
    explicit json_boost_variant_type(const Value& v) : value_(v) { }
    const Value& get() const { return value_; }

private:
    const Value& value_;
};

}

template<typename... Types>
inline detail::json_boost_variant_type<boost::variant<Types...> >
jsonify(const boost::variant<Types...>& v) {
    return detail::json_boost_variant_type<boost::variant<Types...> >(v);
}

namespace detail {

struct visitor : public boost::static_visitor<> {
    explicit visitor(std::ostream& s) : stream_(s) {}

    template<typename T>
    void operator()(const T& t) const {
        using namespace dogen::needle::core::io;
        stream_ << jsonify(t);
    }

private:
    std::ostream& stream_;
};

template<typename Value>
inline std::ostream& operator<<(std::ostream& s,
    const json_boost_variant_type<Value>& p) {
    s << "{ \"__type__\": \"boost::variant\", \"data\": ";
    boost::apply_visitor(detail::visitor(s), p.get());
    s << " }";
    return s;
}

} } } } }

#endif
