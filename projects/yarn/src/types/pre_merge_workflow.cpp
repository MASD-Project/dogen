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
#include "dogen/yarn/types/modules_expander.hpp"
#include "dogen/yarn/types/annotations_expander.hpp"
#include "dogen/yarn/types/origin_expander.hpp"
#include "dogen/yarn/types/parsing_expander.hpp"
#include "dogen/yarn/types/type_parameters_expander.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"
#include "dogen/yarn/types/intermediate_model_factory.hpp"
#include "dogen/yarn/types/pre_merge_workflow.hpp"

namespace dogen {
namespace yarn {

std::list<descriptor> pre_merge_workflow::
obtain_descriptors(const std::vector<boost::filesystem::path>& dirs,
    const options::input_options& io) const {
    descriptor_factory f;
    return f.make(dirs, io);
}

std::list<intermediate_model> pre_merge_workflow::
obtain_intermediate_models(frontend_registrar& rg,
    const std::list<descriptor>& d) const {
    intermediate_model_factory f;
    return f.execute(rg, d);
}

void pre_merge_workflow::expand_modules(intermediate_model& im) const {
    modules_expander ex;
    ex.expand(im);
}

void pre_merge_workflow::
expand_annotations(const std::vector<boost::filesystem::path>& data_dirs,
    const annotations::archetype_location_repository& ohrp,
    const annotations::type_repository& atrp, intermediate_model& im) const {
    annotations_expander ex;
    ex.expand(data_dirs, ohrp, atrp, im);
}

void pre_merge_workflow::expand_origin(const annotations::type_repository& atrp,
    intermediate_model& im) const {
    origin_expander ex;
    ex.expand(atrp, im);
}

void pre_merge_workflow::expand_type_parameters(
    const annotations::type_repository& atrp, intermediate_model& im) const {
    type_parameters_expander ex;
    ex.expand(atrp, im);
}

void pre_merge_workflow::expand_parsing(
    const annotations::type_repository& atrp, intermediate_model& im) const {
    parsing_expander ex;
    ex.expand(atrp, im);
}

std::list<intermediate_model>
pre_merge_workflow::
execute(const std::vector<boost::filesystem::path>& data_dirs,
    const annotations::archetype_location_repository& ohrp,
    const annotations::type_repository& atrp,
    const options::input_options& io, frontend_registrar& rg) const {

    const auto d(obtain_descriptors(data_dirs, io));
    auto r(obtain_intermediate_models(rg, d));
    for (auto& im: r) {
        /*
         * We must expand annotations before we expand modules to
         * ensure the root module is populated with entries
         * before being copied over.
         */
        expand_annotations(data_dirs, ohrp, atrp, im);
        expand_modules(im);
        expand_origin(atrp, im);
        expand_type_parameters(atrp, im);
        expand_parsing(atrp, im);
    }
    return r;
}

} }
