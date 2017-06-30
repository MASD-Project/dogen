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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_EXOGENOUS_MODEL_CHAIN_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_EXOGENOUS_MODEL_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/yarn/types/transforms/exogenous_transform_registrar.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class exogenous_model_chain final {
public:
    exogenous_model_chain() = default;
    exogenous_model_chain(const exogenous_model_chain&) = default;
    exogenous_model_chain(exogenous_model_chain&&) = default;
    ~exogenous_model_chain() = default;

public:
    explicit exogenous_model_chain(const dogen::yarn::transforms::exogenous_transform_registrar& registrar_);

public:
    const dogen::yarn::transforms::exogenous_transform_registrar& registrar_() const;
    dogen::yarn::transforms::exogenous_transform_registrar& registrar_();
    void registrar_(const dogen::yarn::transforms::exogenous_transform_registrar& v);
    void registrar_(const dogen::yarn::transforms::exogenous_transform_registrar&& v);

public:
    bool operator==(const exogenous_model_chain& rhs) const;
    bool operator!=(const exogenous_model_chain& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(exogenous_model_chain& other) noexcept;
    exogenous_model_chain& operator=(exogenous_model_chain other);

private:
    dogen::yarn::transforms::exogenous_transform_registrar registrar__;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::transforms::exogenous_model_chain& lhs,
    dogen::yarn::transforms::exogenous_model_chain& rhs) {
    lhs.swap(rhs);
}

}

#endif
