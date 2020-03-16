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
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/types/features/output_technical_space.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/technical_space_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.technical_space_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string technical_space_not_set("Input technical space must be set.");

}

namespace dogen::logical::transforms {

using entities::technical_space;

void technical_space_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "technical space transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * Update the intrinsic technical space on all modeling elements
     * available thus far.
     */
    entities::elements_traversal(m,
        [](entities::element& e) {
            e.intrinsic_technical_space(technical_space::agnostic);
        });

    /*
     * Ensure the input technical space has been set by now.
     */
    const auto inv(entities::technical_space::invalid);
    const bool has_input_ts(m.input_technical_space() != inv);
    if (!has_input_ts) {
        BOOST_LOG_SEV(lg, error) << technical_space_not_set;
        BOOST_THROW_EXCEPTION(transformation_error(technical_space_not_set));
    }

    /*
     * If we've already got output technical_space, there is no work
     * required.
     */
    if (!m.output_technical_spaces().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Model has output technical spaces set: "
                                 << m.output_technical_spaces();
        return; // not ending tracing by design as there are no changes.
    }

    /*
     * Read the output technical_space requested by the user.
     */
    const auto& cfg(*m.root_module()->configuration());
    const auto& fm(*ctx.feature_model());
    const auto fg(features::output_technical_space::make_feature_group(fm));
    const auto scfg(features::output_technical_space::
        make_static_configuration(fg, cfg));

    /*
     * If the user did not set an output technical space, assume the
     * input as output. Validator will ensure this technical space is
     * legal - e.g. the output technical space is not abstract but can
     * be extracted into a concrete technical space.
     */
    if (scfg.output_technical_space.empty()) {
        m.output_technical_spaces().push_back(m.input_technical_space());
        BOOST_LOG_SEV(lg, debug) << "No overrides for output technical space "
                                 << "  found. Defaulting to input: "
                                 << m.output_technical_spaces();
    } else {
        std::list<entities::technical_space> ots;
        for (const auto s : scfg.output_technical_space)
            ots.push_back(boost::lexical_cast<entities::technical_space>(s));

        m.output_technical_spaces(ots);
        BOOST_LOG_SEV(lg, debug) << "Expanded output technical spaces to: "
                                 << m.output_technical_spaces();
    }

    stp.end_transform(m);
}

}
