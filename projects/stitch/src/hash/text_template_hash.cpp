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
#include "dogen/stitch/hash/text_template_hash.hpp"
#include "dogen/dynamic/schema/hash/object_hash.hpp"
#include "dogen/stitch/hash/scriptlet_block_hash.hpp"
#include "dogen/stitch/hash/settings_bundle_hash.hpp"
#include "dogen/stitch/hash/mixed_content_block_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_visitor : public boost::static_visitor<> {
    boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_visitor() : hash(0) {}
    void operator()(const dogen::stitch::mixed_content_block& v) const {
        combine(hash, v);
    }

    void operator()(const dogen::stitch::scriptlet_block& v) const {
        combine(hash, v);
    }

    mutable std::size_t hash;
};

inline std::size_t hash_boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block(const boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block>& v) {
    boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_visitor vis;
    boost::apply_visitor(vis, v);
    return vis.hash;
}

inline std::size_t hash_std_list_boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_(const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block(i));
    }
    return seed;
}

}

namespace dogen {
namespace stitch {

std::size_t text_template_hasher::hash(const text_template&v) {
    std::size_t seed(0);

    combine(seed, v.settings());
    combine(seed, v.extensions());
    combine(seed, hash_std_list_boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_(v.content()));

    return seed;
}

} }
