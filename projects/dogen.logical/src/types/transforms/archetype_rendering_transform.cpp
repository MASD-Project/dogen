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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.templating/types/wale/instantiator.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/features/wale.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/archetype_rendering_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.parsing_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty_wale_template("Wale template has no content: ");
const std::string duplicate_wale_key("Duplicate wale key: ");

}

namespace dogen::logical::transforms {

void archetype_rendering_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "parsing transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    auto& archs(m.physical_elements().archetypes());
    for (auto& pair : archs) {
        auto& arch(*pair.second);
        if (arch.wale_template()) {
            /*
             * If the user specifically requested a wale template, we
             * expect its contents to be non-zero.
             */
            if (arch.wale_template_content().empty()) {
                const auto tid(arch.wale_template()->qualified().dot());
                BOOST_LOG_SEV(lg, error) << empty_wale_template << tid;
                BOOST_THROW_EXCEPTION(
                    transformation_error(empty_wale_template + tid));
            }

            /*
             * Read wale features.
             */
            const auto& fm(*ctx.feature_model());
            const auto fg(features::wale::make_feature_group(fm));
            const auto scfg(features::wale::make_static_configuration(fg, arch));

            /*
             * Create the input kvps for wale template.
             */
            std::unordered_map<std::string, std::string> kvps;
            for (const auto& pair : scfg.kvp) {
                const auto inserted(kvps.insert(pair).second);
                if (!inserted) {
                    const auto& k(pair.first);
                    BOOST_LOG_SEV(lg, error) << duplicate_wale_key << k;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(duplicate_wale_key + k));
                }
            }

            /*
             * Instantiate the wale template.
             */
            templating::wale::instantiator inst;
            inst.instantiate(arch.wale_template_content(), kvps);
        }
    }

    stp.end_transform(m);
}

}
