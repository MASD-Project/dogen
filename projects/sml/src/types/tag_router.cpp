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
#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/tag_error.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/tag_router.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.tag_router"));
const std::string duplicated_key(
    "Attempt to use a simple tag key which has already been used: ");

}

namespace dogen {
namespace sml {

tag_router::tag_router(boost::property_tree::ptree& tags)
    : tags_(tags) { }

bool tag_router::is_complex(const std::string& key) const {
    return key == tags::odb_pragma;
}

bool tag_router::has_key(const std::string& key) const {
    const auto node(tags_.get_optional<std::string>(key));
    return node;
}

void tag_router::route(const std::string& key, const std::string& value) {
    using boost::property_tree::ptree;
    if (is_complex(key)) {
        const auto node(tags_.get_child_optional(key));
        unsigned int i(0);
        if (node)
            i = node->size();

        const std::string nk(key + "." + boost::lexical_cast<std::string>(i));
        tags_.put_child(nk, ptree(value));
        return;
    }

    if (has_key(key)) {
        BOOST_LOG_SEV(lg, error) << duplicated_key << key;
        BOOST_THROW_EXCEPTION(tag_error(duplicated_key + key));
    }
    tags_.put(key, value);
}

void tag_router::
route(const std::list<std::pair<std::string, std::string> >& kvps) {
    for (const auto& pair : kvps)
        route(pair.first, pair.second);
}

bool tag_router::route_if_marker_found(const std::string& key,
    const std::list<std::pair<std::string, std::string> >& kvps) {
    bool has_marker(false);
    for (const auto& kvp : kvps) {
        has_marker = kvp.first == key;
        if (has_marker)
            break;
    }

    if (!has_marker)
        return false;

    route(kvps);
    return true;
}

bool tag_router::
route_if_key_not_found(const std::string& key, const std::string& value) {
    if (has_key(key))
        return false;

    route(key, value);
    return true;
}

} }
