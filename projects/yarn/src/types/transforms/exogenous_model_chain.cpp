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
#include "dogen/yarn/types/transforms/exogenous_model_chain.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

exogenous_transform_registrar& exogenous_model_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<exogenous_transform_registrar>();

    return *registrar_;
}

intermediate_model exogenous_model_chain::
transform(const context& /*ctx*/, const boost::filesystem::path& /*p*/) {
    intermediate_model r;
    return r;
}

} } }
