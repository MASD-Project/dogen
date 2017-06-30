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

exogenous_model_chain::exogenous_model_chain(const dogen::yarn::transforms::exogenous_transform_registrar& registrar_)
    : registrar__(registrar_) { }

void exogenous_model_chain::swap(exogenous_model_chain& other) noexcept {
    using std::swap;
    swap(registrar__, other.registrar__);
}

bool exogenous_model_chain::operator==(const exogenous_model_chain& rhs) const {
    return registrar__ == rhs.registrar__;
}

exogenous_model_chain& exogenous_model_chain::operator=(exogenous_model_chain other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::transforms::exogenous_transform_registrar& exogenous_model_chain::registrar_() const {
    return registrar__;
}

dogen::yarn::transforms::exogenous_transform_registrar& exogenous_model_chain::registrar_() {
    return registrar__;
}

void exogenous_model_chain::registrar_(const dogen::yarn::transforms::exogenous_transform_registrar& v) {
    registrar__ = v;
}

void exogenous_model_chain::registrar_(const dogen::yarn::transforms::exogenous_transform_registrar&& v) {
    registrar__ = std::move(v);
}

} } }
