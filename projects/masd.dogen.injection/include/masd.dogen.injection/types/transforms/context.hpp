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
#ifndef MASD_DOGEN_INJECTION_TYPES_TRANSFORMS_CONTEXT_HPP
#define MASD_DOGEN_INJECTION_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.tracing/types/tracer_fwd.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model_fwd.hpp"
#include "masd.dogen.archetypes/types/location_repository_fwd.hpp"

namespace masd::dogen::injection::transforms {

class context final {
public:
    ~context() = default;

public:
    context();

    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const bool compatibility_mode,
        const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& feature_model,
        const boost::shared_ptr<masd::dogen::archetypes::location_repository>& archetype_location_repository,
        const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer);

public:
    const std::vector<boost::filesystem::path>& data_directories() const;
    void data_directories(const std::vector<boost::filesystem::path>& v);

    bool compatibility_mode() const;
    void compatibility_mode(const bool v);

    const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& feature_model() const;
    void feature_model(const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& v);

    const boost::shared_ptr<masd::dogen::archetypes::location_repository>& archetype_location_repository() const;
    void archetype_location_repository(const boost::shared_ptr<masd::dogen::archetypes::location_repository>& v);

    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer() const;
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v);

private:
    std::vector<boost::filesystem::path> data_directories_;
    bool compatibility_mode_;
    boost::shared_ptr<masd::dogen::variability::meta_model::feature_model> feature_model_;
    boost::shared_ptr<masd::dogen::archetypes::location_repository> archetype_location_repository_;
    boost::shared_ptr<masd::dogen::tracing::tracer> tracer_;
};

}

#endif
