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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/transforms/context_factory.hpp"
#include "dogen/yarn/types/transforms/model_generation_chain.hpp"
#include "dogen/yarn/types/transforms/code_generation_chain.hpp"
#include "dogen/yarn/types/code_generator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("dogen.yarn.code_generator"));

}

namespace dogen {
namespace yarn {

transforms::code_generation_output
code_generator::generate(const options::knitting_options& o) {
    BOOST_LOG_SEV(lg, info) << "Starting code generation.";

    /*
     * First we obtain the context for all transformations.
     */
    using namespace transforms;
    const auto als(code_generation_chain::registrar().archetype_locations());
    const auto ctx(context_factory::make(o, als));

    /*
     * Then we generate all models.
     */
    const auto models(model_generation_chain::transform(ctx));

    /*
     * Finally we transform them into text.
     */
    const auto r(code_generation_chain::transform(ctx, models));

    BOOST_LOG_SEV(lg, info) << "Finished code generation.";
    return r;
}

} }
