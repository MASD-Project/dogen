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
#include <boost/variant/apply_visitor.hpp>
#include "dogen/dia/hash/font_hash.hpp"
#include "dogen/dia/hash/real_hash.hpp"
#include "dogen/dia/hash/color_hash.hpp"
#include "dogen/dia/hash/point_hash.hpp"
#include "dogen/dia/hash/string_hash.hpp"
#include "dogen/dia/hash/boolean_hash.hpp"
#include "dogen/dia/hash/integer_hash.hpp"
#include "dogen/dia/hash/attribute_hash.hpp"
#include "dogen/dia/hash/composite_hash.hpp"
#include "dogen/dia/hash/rectangle_hash.hpp"
#include "dogen/dia/hash/enumeration_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite_visitor : public boost::static_visitor<> {
    boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite_visitor() : hash(0) {}
    void operator()(const dogen::dia::color& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::real& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::integer& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::font& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::boolean& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::point& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::string& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::enumeration& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::rectangle& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::dia::composite& v) const {
        combine(hash, v);
    }

    mutable std::size_t hash;
};

inline std::size_t hash_boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite(const boost::variant<dogen::dia::color, dogen::dia::real, dogen::dia::integer, dogen::dia::font, dogen::dia::boolean, dogen::dia::point, dogen::dia::string, dogen::dia::enumeration, dogen::dia::rectangle, dogen::dia::composite>& v) {
    boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite_visitor vis;
    boost::apply_visitor(vis, v);
    return vis.hash;
}

inline std::size_t hash_std_vector_boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite_(const std::vector<boost::variant<dogen::dia::color, dogen::dia::real, dogen::dia::integer, dogen::dia::font, dogen::dia::boolean, dogen::dia::point, dogen::dia::string, dogen::dia::enumeration, dogen::dia::rectangle, dogen::dia::composite> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite(i));
    }
    return seed;
}

}

namespace dogen {
namespace dia {

std::size_t attribute_hasher::hash(const attribute&v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, hash_std_vector_boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite_(v.values()));

    return seed;
}

} }
