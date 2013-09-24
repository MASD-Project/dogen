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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/cache_error.hpp"
#include "dogen/sml/types/property_cache.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om_formatters.modeline_formatter"));
const std::string not_populated("Attempt to query cache without populating");

}

namespace dogen {
namespace sml {

property_cache::property_cache() : is_populated_(false) { }

void property_cache::populate(const model& m) {
    is_populated_ = true;
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        local_properties_.insert(std::make_pair(o.name(), o.properties()));
    }
}

bool property_cache::is_populated() const {
    return is_populated_;
}

void property_cache::ensure_populated() const {
    if (!is_populated()) {
        BOOST_LOG_SEV(lg, error) << not_populated;
        BOOST_THROW_EXCEPTION(cache_error(not_populated));
    }
}

std::list<property>
property_cache::get_all_properties(const abstract_object& o) const {
    ensure_populated();
    const auto i(all_properties_.find(o.name()));
    if (i != all_properties_.end())
        return i->second;
    return std::list<property>{};
}

std::list<property>
property_cache::get_local_properties(const abstract_object& o) const {
    ensure_populated();
    const auto i(local_properties_.find(o.name()));
    if (i != local_properties_.end())
        return i->second;
    return std::list<property>{};
}

std::unordered_map<qname, std::list<property> >
property_cache::get_inehrited_properties(const abstract_object& o) const {
    ensure_populated();
    std::unordered_map<qname, std::list<property> > r;

    if (o.parent_name()) {
        const auto i(inherited_properties_.find(*o.parent_name()));
        if (i != inherited_properties_.end())
            r.insert(std::make_pair(*o.parent_name(), i->second));
    }
    return r;
}

} }
