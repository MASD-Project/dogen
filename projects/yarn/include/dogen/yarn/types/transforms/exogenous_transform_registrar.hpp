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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_EXOGENOUS_TRANSFORM_REGISTRAR_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_EXOGENOUS_TRANSFORM_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <unordered_map>
#include "dogen/yarn/types/transforms/exogenous_transform_interface.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

/**
 * @brief Keeps track of all the available exogenous transforms.
 */
class exogenous_transform_registrar final {
public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate();

    /*
     * @brief Registers a given exogenous transform.
     *
     * @pre Exogenous transform is not yet registered.
     * @pre Pointer must not be null.
     */
    void register_exogenous_transform(
        std::shared_ptr<exogenous_transform_interface> et);

    /**
     * @brief Returns the exogenous transform that handles the
     * supplied model identifier.
     *
     * @pre An exogenous transform must have been registered for this
     * model identifier.
     */
    exogenous_transform_interface&
    transform_for_model(const std::string& model_identifier);

private:
    std::unordered_map<std::string,
                       std::shared_ptr<exogenous_transform_interface>>
    exogenous_transforms_;
};

} } }

#endif
