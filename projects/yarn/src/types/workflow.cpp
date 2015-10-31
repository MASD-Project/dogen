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
#include "dogen/yarn/types/frontend_workflow.hpp"
#include "dogen/yarn/types/assembler.hpp"
#include "dogen/yarn/types/workflow.hpp"

namespace dogen {
namespace yarn {

std::list<intermediate_model> workflow::obtain_intermediate_models_activity(
    const dynamic::repository& rp,
    const std::list<input_descriptor>& id) const {
    frontend_workflow w(rp);
    return w.execute(id);
}

intermediate_model workflow::assemble_intermediate_models_activity(
    const std::list<intermediate_model>& m) const {
    assembler a;
    return a.assemble(m);
}

intermediate_model workflow::execute(const dynamic::repository& rp,
    const std::list<input_descriptor>& id) const {
    const auto pm(obtain_intermediate_models_activity(rp, id));
    return assemble_intermediate_models_activity(pm);
}

} }
