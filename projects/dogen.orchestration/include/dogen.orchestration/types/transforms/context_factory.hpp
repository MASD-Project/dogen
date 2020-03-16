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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CONTEXT_FACTORY_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CONTEXT_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/types/configuration.hpp"
#include "dogen.physical/types/entities/location_repository.hpp"
#include "dogen.variability/types/helpers/registrar.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Factory that creates the transformation context.
 */
class context_factory final {
private:
    /**
     * @brief Registers all entities defined by the variability
     * initialisation process.
     */
    static void register_variability_entities(
        variability::helpers::registrar& rg);

public:
    /**
     * @brief Creates a transform context required by the injection
     * chain.
     */
    static injection::transforms::context make_injection_context(
        const configuration& cfg, const std::string& activity);

    /**
     * @brief Creates the injection context required by all transform
     * chains.
     */
    static context make_context(const configuration& cfg,
        const std::string& activity,
        const boost::filesystem::path& output_directory);
};

}

#endif
