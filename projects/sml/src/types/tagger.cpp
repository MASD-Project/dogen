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
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/tag_router.hpp"
#include "dogen/sml/types/tagger.hpp"

namespace dogen {
namespace sml {

tagger::tagger(const std::set<config::cpp_facet_types>& enabled_facets)
    : enabled_facets_(enabled_facets) { }

bool tagger::is_facet_enabled(const config::cpp_facet_types ft) const {
    const auto i(enabled_facets_.find(ft));
    return i != enabled_facets_.end();
}

std::string tagger::
filename_for_qname(const qname& /*qn*/, const config::cpp_facet_types /*ft*/) const {
    std::string r;
    return r;
}

void tagger::tag_type(type& /*t*/) const {
}

void tagger::tag(model& m) const {
    tag_router router(make_tag_router(m));
    router.route_if_key_not_found(tags::generate_preamble, tags::bool_true);

    using config::cpp_facet_types;
    const auto& ss(tags::status_supported);
    router.route_if_key_not_found(tags::cpp::types::status, ss);

    if (is_facet_enabled(cpp_facet_types::hash))
        router.route_if_key_not_found(tags::cpp::hash::standard::status, ss);

    if (is_facet_enabled(cpp_facet_types::io))
        router.route_if_key_not_found(tags::cpp::io::status, ss);

    if (is_facet_enabled(cpp_facet_types::serialization)) {
        const auto& key(tags::cpp::serialization::boost::status);
        router.route_if_key_not_found(key, ss);
    }

    if (is_facet_enabled(cpp_facet_types::test_data)) {
        const auto& key(tags::cpp::test_data::status);
        router.route_if_key_not_found(key, ss);
    }

    if (is_facet_enabled(cpp_facet_types::odb)) {
        router.route_if_key_not_found(tags::cpp::odb::status, ss);
    }
}

} }
