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
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/all_technical_spaces_transform.hpp"

namespace {

const std::string
transform_id("logical.transforms.all_technical_spaces_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

/**
 * @brief Gathers technical space information from model elements.
 */
class gatherer {
public:
    void operator()(entities::element& e) {
        /*
         * Skip agnostic as it is an abstract technical space.
         */
        const auto ts(e.intrinsic_technical_space());
        if (ts == entities::technical_space::agnostic)
            return;

        const auto inserted(technical_spaces_.insert(ts).second);
        if (!inserted)
            return;

        const auto id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, trace) << "Inserted technical space: " << ts
                                 << " from element: " << id;
    }

public:
    const std::unordered_set<logical::entities::technical_space>& result() {
        return technical_spaces_;
    }

private:
    std::unordered_set<logical::entities::technical_space> technical_spaces_;
};

void all_technical_spaces_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "meta-naming transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * First gather all technical spaces due to model elements.
     */
    gatherer g;
    entities::elements_traversal(m, g);

    /*
     * Now add technical spaces specific to the model itself.
     */
    auto ats(g.result());
    const auto its(m.input_technical_space());
    ats.insert(its);
    BOOST_LOG_SEV(lg, trace) << "Input technical space: " << its;

    for (const auto& ots : m.output_technical_spaces()) {
        ats.insert(ots);
        BOOST_LOG_SEV(lg, trace) << "Output technical space: " << ots;
    }

    /*
     * Finally, add "fixed" technical spaces.
     * FIXME: hackery for ODB options, XML and CMake.
     */
    ats.insert(entities::technical_space::odb);
    ats.insert(entities::technical_space::xml);
    ats.insert(entities::technical_space::cmake);

    /*
     * Update the model with the information obtained.
     */
    m.all_technical_spaces(ats);

    stp.end_transform(m);
}

}
