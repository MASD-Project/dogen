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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/lexical_cast/entities/decoration/editor_lc.hpp"
#include "dogen.logical/lexical_cast/entities/decoration/modeline_location_lc.hpp"
#include "dogen.logical/types/features/decoration_modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/modelines_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.modelines_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string missing_container("Modeline does not have a container: ");
const std::string missing_group("Cannot find modeline group: ");

}

namespace dogen::logical::transforms {

void modelines_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "modelines transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * Obtain the feature group.
     */
    const auto& fm(*ctx.feature_model());
    using features::decoration_modeline;
    const auto fg(decoration_modeline::make_feature_group(fm));

    /*
     * Read the configuration for all modelines.
     */
    for(auto& pair : m.decoration_elements().modelines()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, trace) << "Processing modeline: " << id;

        /*
         * Obtain the static configuration, and populate the modeline
         * properties from it.
         */
        auto& ml(*pair.second);
        const auto scfg(decoration_modeline::make_static_configuration(fg, ml));

        using boost::lexical_cast;
        using entities::decoration::editor;
        ml.editor(lexical_cast<editor>(scfg.editor));

        using entities::decoration::modeline_location;
        ml.location(lexical_cast<modeline_location>(scfg.location));

        using entities::technical_space;
        ml.technical_space(lexical_cast<technical_space>(scfg.technical_space));

        /*
         * Locate the modeline group that contains this modeline and
         * update its list of modelines it contains.
         */
        const auto cby(ml.contained_by());
        if (cby.empty()) {
            BOOST_LOG_SEV(lg, error) << missing_container << id;
            BOOST_THROW_EXCEPTION(transformation_error(missing_container + id));
        }

        auto& mgs(m.decoration_elements().modeline_groups());
        const auto i(mgs.find(cby));
        if (i == mgs.end()) {
            BOOST_LOG_SEV(lg, error) << missing_group << cby;
            BOOST_THROW_EXCEPTION(transformation_error(missing_group + cby));
        }
        i->second->modelines().push_back(pair.second);
    }

    stp.end_transform(m);
}

}
