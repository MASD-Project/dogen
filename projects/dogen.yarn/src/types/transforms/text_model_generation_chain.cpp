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
#include "dogen.probing/types/scoped_prober.hpp"
#include "dogen/yarn/io/meta_model/text_model_io.hpp"
#include "dogen/yarn/types/transforms/model_to_text_model_chain.hpp"
#include "dogen/yarn/types/transforms/model_generation_chain.hpp"
#include "dogen/yarn/types/transforms/text_model_generation_chain.hpp"

namespace {

const std::string transform_id("dogen.yarn.text_model_generation_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen {
namespace yarn {
namespace transforms {

meta_model::text_model
text_model_generation_chain::transform(const context& ctx) {
    const auto model_name(ctx.transform_options().target().filename().string());
    probing::scoped_chain_prober stp(lg, "text model generation chain",
        transform_id, model_name, ctx.prober());

    /*
     * Obtain the models.
     */
    const auto models(model_generation_chain::transform(ctx));

    /*
     * Run the model to text transforms.
     */
    const auto r(model_to_text_model_chain::transform(ctx, models));
    stp.end_chain(r);

    return r;
}

} } }
