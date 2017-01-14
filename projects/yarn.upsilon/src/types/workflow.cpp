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
#include <list>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn.upsilon/types/workflow_error.hpp"
#include "dogen/yarn.upsilon/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.upsilon.workflow"));

const std::string incorrect_number_of_outputs(
    "Upsilon moodel does not have expected number of outputs (1): ");

}

namespace dogen {
namespace yarn {
namespace upsilon {

yarn::intermediate_model
workflow::create_model(const dogen::upsilon::model& m) const {
    yarn::intermediate_model r;

    if (m.config().outputs().size() != 1) {
        const auto gs(m.config().file_name().generic_string());
        BOOST_LOG_SEV(lg, error) << incorrect_number_of_outputs << gs;
        BOOST_THROW_EXCEPTION(workflow_error(incorrect_number_of_outputs + gs));
    }

    const auto& output(m.config().outputs()[0]);

    yarn::name_factory nf;
    const auto n(nf.build_model_name(output.schema_name()));
    r.name(n);
    r.origin_type(origin_types::target);

    yarn::module root_module;
    root_module.name(n);
    root_module.origin_type(origin_types::target);

    r.modules()[n.id()] = root_module;

    return r;
}

yarn::intermediate_model
workflow::execute(const dogen::upsilon::model& m) const {
    const auto r(create_model(m));
    return r;
}

} } }
