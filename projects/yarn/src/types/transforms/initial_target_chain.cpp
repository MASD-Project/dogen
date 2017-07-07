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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/exogenous_model_chain.hpp"
#include "dogen/yarn/types/transforms/pre_processing_chain.hpp"
#include "dogen/yarn/types/transforms/initial_target_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.initial_target_chain"));

const std::string non_absolute_target("Target path is not absolute: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

void initial_target_chain::
ensure_target_path_is_absolute(const boost::filesystem::path& p) {
    const auto gs(p.generic_string());
    if (p.is_absolute()) {
        BOOST_LOG_SEV(lg, debug) << "Target path is valid: " << gs;
        return;
    }

    BOOST_LOG_SEV(lg, error) << non_absolute_target << gs;
    BOOST_THROW_EXCEPTION(transformation_error(non_absolute_target + gs));
}

intermediate_model initial_target_chain::transform(const context& ctx) {
    BOOST_LOG_SEV(lg, debug) << "Executing the initial target chain.";

    const auto tp(ctx.options().target());
    ensure_target_path_is_absolute(tp);

    /*
     * First we obtain the target model exactly as it was read out
     * from the exogenous transformer.
     */
    auto r(exogenous_model_chain::transform(tp));

    /*
     * Next, we set the origin of the target model to target so that
     * further transforms can be applied such as the origin
     * transforms.
     */
    r.origin_type(origin_types::target);

    /*
     * Finally, we apply all of the pre-processing transforms to the
     * target.
     */
    pre_processing_chain::transform(ctx, r);

    BOOST_LOG_SEV(lg, debug) << "Initial target chain executed.";
    return r;
}

} } }
