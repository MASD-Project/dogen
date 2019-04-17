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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONTEXT_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.tracing/types/tracer_fwd.hpp"
#include "masd.dogen.archetypes/types/location_repository_fwd.hpp"

namespace masd::dogen::variability::transforms {

/**
 * @brief Context for transformations.
 */
class context final {
public:
    context() = default;
    context(const context&) = default;

public:
    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const boost::shared_ptr<masd::dogen::archetypes::location_repository>& archetype_location_repository,
        const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer);

public:
    const std::vector<boost::filesystem::path>& data_directories() const;
    void data_directories(const std::vector<boost::filesystem::path>& v);

    const boost::shared_ptr<masd::dogen::archetypes::location_repository>& archetype_location_repository() const;
    void archetype_location_repository(const boost::shared_ptr<masd::dogen::archetypes::location_repository>& v);

    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer() const;
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v);

private:
    std::vector<boost::filesystem::path> data_directories_;
    boost::shared_ptr<masd::dogen::archetypes::location_repository> archetype_location_repository_;
    boost::shared_ptr<masd::dogen::tracing::tracer> tracer_;
};

}

#endif
