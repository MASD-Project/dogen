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
#include "masd.dogen.variability/types/transforms/context.hpp"

namespace masd::dogen::variability::transforms {

context::context(
    const std::vector<boost::filesystem::path>& data_directories,
    const boost::shared_ptr<masd::dogen::archetypes::location_repository>& archetype_location_repository,
    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer)

    : data_directories_(data_directories),
      archetype_location_repository_(archetype_location_repository),
      tracer_(tracer) { }

const std::vector<boost::filesystem::path>& context::data_directories() const {
    return data_directories_;
}

void context::data_directories(const std::vector<boost::filesystem::path>& v) {
    data_directories_ = v;
}

const boost::shared_ptr<masd::dogen::archetypes::location_repository>& context::archetype_location_repository() const {
    return archetype_location_repository_;
}

void context::archetype_location_repository(const boost::shared_ptr<masd::dogen::archetypes::location_repository>& v) {
    archetype_location_repository_ = v;
}

const boost::shared_ptr<masd::dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v) {
    tracer_ = v;
}

}
