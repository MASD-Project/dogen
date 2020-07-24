/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <set>
#include <sstream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/io/entities/configuration_io.hpp"
#include "dogen.variability/io/entities/binding_point_io.hpp"
#include "dogen.variability/types/helpers/building_exception.hpp"
#include "dogen.variability/types/helpers/configuration_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("variability.helpers.configuration_factory"));

}

namespace dogen::variability::helpers {

configuration_factory::configuration_factory(
    const entities::feature_model& fm, const bool compatibility_mode)
    : configuration_points_factory_(fm, compatibility_mode) {}

std::unordered_map<std::string, std::list<std::string>>
configuration_factory::aggregate_entries(
    const std::list<identification::entities::tagged_value>& entries) const {
    std::unordered_map<std::string, std::list<std::string>> r;

    for (const auto& entry : entries)
        r[entry.tag()].push_back(entry.value());

    return r;
}

entities::configuration configuration_factory::make(
    const std::list<identification::entities::tagged_value>& tagged_values,
    const std::list<identification::entities::tagged_value>&
    tagged_values_overrides, const entities::binding_point bp) const {
    const auto& tv(tagged_values);
    const auto atvo(aggregate_entries(tagged_values_overrides));
    entities::configuration r;
    r.source_binding_point(bp);
    r.configuration_points(configuration_points_factory_.make(bp, tv, atvo));
    return r;
}

boost::shared_ptr<entities::configuration>
configuration_factory::make_shared_ptr(
    const std::list<identification::entities::tagged_value>& tagged_values,
    const std::list<identification::entities::tagged_value>&
    tagged_values_overrides, const entities::binding_point bp) const {
    const auto& tv(tagged_values);
    const auto atvo(aggregate_entries(tagged_values_overrides));
    auto r(boost::make_shared<entities::configuration>());
    r->source_binding_point(bp);
    r->configuration_points(configuration_points_factory_.make(bp, tv, atvo));
    return r;
}

}
