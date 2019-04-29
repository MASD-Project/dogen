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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_CONTEXT_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.tracing/types/tracer_fwd.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model_fwd.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository_fwd.hpp"
#include "masd.dogen.archetypes/types/location_repository_fwd.hpp"

namespace masd::dogen::coding::transforms {

/**
 *
 * Context for all coding transformations.
 *
 * Contains all of the external data required for the transformations
 * to execute. It's not ideal to have a huge "global" class, with lots
 * of unrelated state; however, over time, we found that a number of
 * arguments were being supplied across the call graph, resulting in a
 * lot of repetitive code. The context gathers together all of these.
 */
class context final {
public:
    ~context() = default;

public:
    context();

    context(
        const bool use_configuration,
        const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& feature_model,
        const boost::shared_ptr<masd::dogen::archetypes::location_repository>& archetype_location_repository,
        const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& mapping_repository,
        const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer);

public:
    bool use_configuration() const;
    void use_configuration(const bool v);

    const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& feature_model() const;
    void feature_model(const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& v);

    const boost::shared_ptr<masd::dogen::archetypes::location_repository>& archetype_location_repository() const;
    void archetype_location_repository(const boost::shared_ptr<masd::dogen::archetypes::location_repository>& v);

    const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& mapping_repository() const;
    void mapping_repository(const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& v);

    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer() const;
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v);

private:
    bool use_configuration_;
    boost::shared_ptr<masd::dogen::variability::meta_model::feature_model> feature_model_;
    boost::shared_ptr<masd::dogen::archetypes::location_repository> archetype_location_repository_;
    boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository> mapping_repository_;
    boost::shared_ptr<masd::dogen::tracing::tracer> tracer_;
};

}

#endif
