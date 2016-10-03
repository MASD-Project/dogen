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
#include "dogen/yarn/types/parsing_expander.hpp"
#include "dogen/yarn/types/annotations_expander.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"
#include "dogen/yarn/types/intermediate_model_factory.hpp"
#include "dogen/yarn/types/pre_merge_workflow.hpp"

namespace dogen {
namespace yarn {

std::list<descriptor> pre_merge_workflow::
obtain_descriptors(const std::list<boost::filesystem::path>& dirs,
    const options::input_options& io) const {
    descriptor_factory f;
    return f.make(dirs, io);
}

std::list<intermediate_model> pre_merge_workflow::
obtain_intermediate_models(
    const dynamic::repository& drp, frontend_registrar& rg,
    const std::list<descriptor>& d) const {
    intermediate_model_factory f;
    return f.execute(drp, rg, d);
}

void pre_merge_workflow::expand_modules(intermediate_model& m) const {
    modules_expander ex;
    ex.expand(m);
}

void pre_merge_workflow::expand_annotations(const dynamic::repository& drp,
    intermediate_model& m) const {
    annotations_expander ex(drp);
    ex.expand(m);
}

void pre_merge_workflow::expand_parsing(intermediate_model& m) const {
    parsing_expander ex;
    ex.expand(m);
}

std::list<intermediate_model>
pre_merge_workflow::execute(const dynamic::repository& drp,
    const std::list<boost::filesystem::path>& dirs,
    const options::input_options& io,
    frontend_registrar& rg) const {

    const auto d(obtain_descriptors(dirs, io));
    auto r(obtain_intermediate_models(drp, rg, d));
    for (auto& im: r) {
        expand_modules(im);
        expand_annotations(drp, im);
        expand_parsing(im);
    }
    return r;
}

} }
