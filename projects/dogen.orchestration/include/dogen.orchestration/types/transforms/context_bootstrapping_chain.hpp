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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CONTEXT_BOOTSTRAPPING_CHAIN_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CONTEXT_BOOTSTRAPPING_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/types/configuration.hpp"
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.variability/types/helpers/registrar.hpp"
#include "dogen.variability/types/transforms/context.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Bootstraps the transforms sub-system.
 *
 * This transform is responsible for running all of the first stage
 * chains needed by the remaining chains, and producing the top-level
 * transform context.
 */
class context_bootstrapping_chain final {
private:
    /**
     * @brief Registers all entities defined by the variability
     * initialisation process.
     */
    static void
    register_variability_entities(variability::helpers::registrar& rg);

    /**
     * @brief Creates and sets up the tracer.
     */
    static boost::shared_ptr<tracing::tracer> create_and_setup_tracer(
        const configuration& cfg, const std::string& activity);

private:
    /**
     * @brief Creates the physical meta-model.
     */
    static boost::shared_ptr<physical::entities::meta_model>
    create_physical_meta_model(boost::shared_ptr<tracing::tracer> tracer);

    /**
     * @brief Creates the variability feature model.
     */
    static boost::shared_ptr<variability::entities::feature_model>
    create_variability_feature_model(
        const variability::transforms::context& ctx);

public:
    /**
     * @brief Execute the full bootstrap process, producing a top-level context.
     */
    static context bootstrap(const configuration& cfg,
        const std::string& activity,
        const std::vector<boost::filesystem::path>& reference_directories,
        const boost::filesystem::path& output_directory);
};

}

#endif
