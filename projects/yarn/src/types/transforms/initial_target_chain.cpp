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
validate_target_path(const boost::filesystem::path& p) {
    /*
     * We require the target path supplied to us to be an absolute
     * path. This is because we perform calculations off of it such as
     * locating the reference models and so forth. The end-user is not
     * required to have supplied an absolute path, but someone above
     * us must be responsible for ensuring we receive an absolute
     * path.
     */
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
    validate_target_path(tp);

    /*
     * First we obtain the target model exactly as it was read out
     * from the exogenous transformer.
     */
    const auto r(exogenous_model_chain::transform(tp));

    BOOST_LOG_SEV(lg, debug) << "Initial target chain executed.";
    return r;
}

} } }
