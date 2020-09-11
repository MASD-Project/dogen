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
#include "dogen.variability/types/transforms/context.hpp"
#include "dogen.physical/types/transforms/minimal_context.hpp"
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Factory that creates the transformation context.
 */
class context_factory final {
public:
    /**
     * @brief Creates the physical minimal context for bootstrapping.
     */
    static physical::transforms::minimal_context
    make_minimal_context(boost::shared_ptr<tracing::tracer> tracer);

    /**
     * @brief Creates the physical minimal context for bootstrapping.
     */
    static variability::transforms::context
    make_variability_context(
        const configuration& cfg,
        boost::shared_ptr<tracing::tracer> tracer,
        const std::unordered_map<std::string, std::vector<std::string>>&
        template_instantiation_domains);

    /**
     * @brief Creates a transform context required by the codec
     * chain.
     */
    static codec::transforms::context make_codec_context(
        const std::string& activity, boost::shared_ptr<tracing::tracer> tracer,
        boost::shared_ptr<physical::entities::meta_model> pmm);

    /**
     * @brief Creates the top-level context required by all transform
     * chains.
     */
    static context make_context(const configuration& cfg,
        const std::string& activity,
        const boost::filesystem::path& output_directory,
        const variability::transforms::context& vctx,
        boost::shared_ptr<variability::entities::feature_model> fm,
        boost::shared_ptr<physical::entities::meta_model> pmm);
};

}

#endif
