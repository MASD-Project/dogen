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
#ifndef DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_FACTORY_HPP
#define DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <boost/optional.hpp>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/annotations/types/repository.hpp"
#include "dogen/yarn/types/frontend_registrar.hpp"
#include "dogen/yarn/types/frontend_interface.hpp"
#include "dogen/yarn/types/descriptor.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Generates intermediate models from descriptors.
 */
class intermediate_model_factory {
public:
    /**
     * @brief Process all of the descriptors into intermediate models,
     * using the appropriate frontends.
     *
     * @pre All supplied descriptors must be supported by the
     * registered frontends.
     */
    std::list<intermediate_model>
    execute(frontend_registrar& rg, const std::list<descriptor>& descriptors);
};

} }

#endif
