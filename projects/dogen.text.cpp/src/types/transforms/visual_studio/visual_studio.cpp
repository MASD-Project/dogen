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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_builder.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text.cpp/types/transforms/visual_studio/visual_studio.hpp"
#include "dogen.text.cpp/types/transforms/visual_studio/project_transform.hpp"
#include "dogen.text.cpp/types/transforms/visual_studio/solution_transform.hpp"
#include "dogen.text.cpp/types/transforms/visual_studio/msbuild_targets_transform.hpp"

namespace dogen::text::cpp::transforms::visual_studio {
namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dogen.text.cpp.transforms.visual_studio"));

physical::entities::facet make_facet() {
    physical::helpers::meta_name_builder b;
    b.kernel("masd");
    b.backend("cpp");
    b.facet("visual_studio");

    physical::entities::facet r;
    r.meta_name(b.build());

    const auto lambda([&](const auto& arch) {
        const auto id(arch.meta_name().qualified());
        const auto pair(std::make_pair(id, arch));
        const auto inserted(r.archetypes().insert(pair).second);
        if (!inserted) {
            using text::transforms::transformation_error;
            const std::string duplicate_archetype("Duplicate archetype: ");
            BOOST_LOG_SEV(lg, error) << duplicate_archetype << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_archetype + id));
        }
    });

    lambda(msbuild_targets_transform::static_archetype());
    lambda(solution_transform::static_archetype());
    lambda(project_transform::static_archetype());
    return r;
}

}

physical::entities::facet visual_studio_facet_chain::static_facet() {
    static const auto r(make_facet());
    return r;
}

physical::entities::facet visual_studio_facet_chain::facet() const {
    return static_facet();
}

}

