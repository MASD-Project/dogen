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
#include "dogen/yarn/io/meta_model/exomodel_io.hpp"
#include "dogen/yarn/types/transforms/naming_transform.hpp"
#include "dogen/yarn/types/transforms/annotations_transform.hpp"
#include "dogen/yarn/types/transforms/exomodel_generation_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.exomodel_generation_chain"));

}

namespace dogen {
namespace yarn {
namespace transforms {

std::shared_ptr<exomodel_transform_registrar>
exomodel_generation_chain::registrar_;

exomodel_transform_interface& exomodel_generation_chain::
transform_for_model(const boost::filesystem::path& p) {
    /*
     * Ensure the registrar is in a valid state before we proceed.
     */
    auto& rg(registrar());
    rg.validate();
    return rg.transform_for_model(p.filename());
}

exomodel_transform_registrar& exomodel_generation_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<exomodel_transform_registrar>();

    return *registrar_;
}

meta_model::exomodel exomodel_generation_chain::
transform(const context& ctx, const boost::filesystem::path& p) {
    BOOST_LOG_SEV(lg, debug) << "Transforming exogenous model: "
                             << p.generic_string();

    /*
     * Transform the exogenous model - in whatever supported exogenous
     * representation it may be in, Dia, JSON, etc - into the internal
     * representation of an exogenous model.
     */
    auto& t(transform_for_model(p));
    auto r(t.transform(p));

    /*
     * Now transform the annotations. This must be done at this point
     * because the naming transform reads naming information from the
     * annotations.
     */
    annotations_transform::transform(ctx, r);

    /*
     * Finally, update all element names and attributes to take into
     * account the external modules and the model modules, supplied as
     * meta-data.
     */
    naming_transform::transform(ctx, r);

    BOOST_LOG_SEV(lg, debug) << "Transformed exogenous  model.";
    return r;
}

} } }
