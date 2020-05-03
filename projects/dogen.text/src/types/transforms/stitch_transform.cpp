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
#include <sstream>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.templating/types/stitch/instantiator.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/stitch_transform.hpp"

namespace {

const std::string empty;
static std::string transform_id("text.transforms.stitch_transform");
static std::string transform_description("Expands stitch templates.");
const std::string decoration_preamble_key("masd.decoration.preamble");
const std::string decoration_postamble_key("masd.decoration.postamble");

static std::string null_input("Input artefact is null.");
static std::string null_output("Output artefact is null.");
static std::string invalid_outputs_size(
    "Invalid number of outputs provided to transform: ");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::text::transforms {

std::string stitch_transform::id() const {
    return transform_id;
}

std::string stitch_transform::description() const {
    return transform_description;
}

void stitch_transform::
apply(const context& ctx, const logical::entities::element& e,
    const boost::shared_ptr<physical::entities::artefact> input, std::list<
    boost::shared_ptr<physical::entities::artefact>>& outputs) const {
    /*
     * Input must not be null
     */
    if (!input) {
        BOOST_LOG_SEV(lg, error) << null_input;
        BOOST_THROW_EXCEPTION(transformation_error(null_input));
    }

    tracing::scoped_transform_tracer stp(lg, "stitch transform",
        transform_id, input->name().simple(), *ctx.tracer(), input);

    /*
     * Output must be exactly one artefact.
     */
    if (outputs.size() != 1) {
        std::ostringstream os;
        os << invalid_outputs_size << outputs.size();
        const auto msg(os.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(transformation_error(msg));
    }

    /*
     * Output must not be null
     */
    if (!outputs.front()) {
        BOOST_LOG_SEV(lg, error) << null_output;
        BOOST_THROW_EXCEPTION(transformation_error(null_output));
    }

    /*
     * Locate the decoration for this template. We have hard-coded it
     * to c++ given that this is the only use case. We use the
     * decoration to build up the KVP map that will be supplied to the
     * template instantiator.
     */
    const auto ts(logical::entities::technical_space::cpp);
    const auto i(e.decoration().find(ts));
    auto dec(i->second);
    const auto external_keys = std::unordered_map<std::string, std::string> {
        {
            decoration_preamble_key, dec ? dec->preamble() : empty
        },
        {
            decoration_postamble_key, dec ? dec->postamble() : empty
        }
    };

    // templating::stitch::instantiator tsi;
    // tsi.ins
}

}
