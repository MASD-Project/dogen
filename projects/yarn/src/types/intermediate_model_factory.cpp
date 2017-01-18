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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/yarn/io/descriptor_io.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"
#include "dogen/yarn/types/intermediate_model_expander.hpp"
#include "dogen/yarn/types/intermediate_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.intermediate_model_factory"));

}

namespace dogen {
namespace yarn {

intermediate_model
intermediate_model_factory::intermediate_model_for_descriptor(
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    frontend_registrar& rg, const descriptor& d) const {
    BOOST_LOG_SEV(lg, debug) << "Creating intermediate model. "
                             << "Descriptor: " << d;

    auto& fe(rg.frontend_for_path(d.path()));
    auto r(fe.read(d));

    intermediate_model_expander ex;
    ex.expand(agf, atrp, r);

    BOOST_LOG_SEV(lg, debug) << "Created intermediate model.";
    return r;
}

std::vector<intermediate_model>
intermediate_model_factory::
make(const std::vector<boost::filesystem::path>& dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko, frontend_registrar& rg) const {

    descriptor_factory f;

    /*
     * We need to first obtain the target intermediate model and
     * post-process it. This is done because we need to access the
     * annotations inside this model in order to figure out what the
     * user reference intermediate models are.
     */
    const auto timd(f.make(ko.target()));
    const auto tim(intermediate_model_for_descriptor(agf, atrp, rg, timd));
    const auto& ra(tim.root_module().annotation());

    /*
     * Now obtain all of the descriptors for the reference models,
     * using the annotations object and the data directories; then
     * load all reference intermediate models and post-process them.
     */
    const auto target_dir(timd.path().parent_path());
    const auto rimd(f.make(dirs, target_dir, atrp, ra));
    std::vector<intermediate_model> r;
    r.reserve(rimd.size() + 1/*target model*/);
    r.push_back(tim);

    for (const auto& d : rimd)
        r.push_back(intermediate_model_for_descriptor(agf, atrp, rg, d));

    return r;
}

} }
