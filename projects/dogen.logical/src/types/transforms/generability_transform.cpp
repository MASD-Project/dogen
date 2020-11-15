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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.identification/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/types/features/output_technical_space.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/generability_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.generability_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

namespace {

using namespace entities;

/**
 * @brief Updates all dynamic stereotypes for model elements which
 * require them.
 */
class updater {
public:
    /*
     * Elements that may have dynamic stereotypes.
     */
    void operator()(element& v) {
        v.generability_status(generability_status::generatable);
    }
    void operator()(structural::object_template &v) {
        v.generability_status(generability_status::generation_not_expected);
    }

    void operator()(structural::module& v) {
        if (v.is_global_module()) {
            /*
             * Ignore the global module. This is just a pseudo module
             * that is used as a top-level container and has no
             * expression in code.
             */
            v.generability_status(generability_status::non_generatable_state);
        } else if (v.documentation().empty()) {
            /*
             * Modules are only generatable for the purposes of
             * documentation. Set them to disabled if there is no
             * documentation.
             */
            BOOST_LOG_SEV(lg, trace) << "Module does not have documentation. "
                                     << "Disabling it. Id: "
                                     << v.name().qualified().dot();
            v.generability_status(generability_status::non_generatable_state);
        } else {
            /*
             * Regular module with documentation should be generated.
             */
            v.generability_status(generability_status::generatable);
        }
    }

    void operator()(decoration::licence& v) {
        v.generability_status(generability_status::generation_not_expected);
    }

    void operator()(decoration::modeline_group& v) {
        v.generability_status(generability_status::generation_not_expected);
    }

    void operator()(decoration::modeline& v) {
        v.generability_status(generability_status::generation_not_expected);
    }

    void operator()(decoration::generation_marker& v) {
        v.generability_status(generability_status::generation_not_expected);
    }

    void operator()(variability::profile& v) {
        v.generability_status(generability_status::generation_not_expected);
    }

    void operator()(variability::profile_template& v) {
        v.generability_status(generability_status::generation_not_expected);
    }

     void operator()(templating::logic_less_template& v) {
         v.generability_status(generability_status::generation_not_expected);
     }
};

}

void generability_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "generability",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    updater u;
    entities::elements_traversal(m, u);

    stp.end_transform(m);
}

}
