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
#ifndef DOGEN_YARN_TYPES_EXPANDER_HPP
#define DOGEN_YARN_TYPES_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/types/repository.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 *  @brief Performs the expansion sub-workflow on a frontend generated
 *  intermediate model.
 */
class expander {
public:
    explicit expander(const dynamic::repository& drp);

private:
    /**
     * @brief Performs a module expansion on the model.
     */
    void expand_modules(intermediate_model& m) const;

    /**
     * @brief Performs an attribute expansion on the model.
     */
    void expand_attributes(intermediate_model& m) const;

    /**
     * @brief Performs a settings expansion on the model.
     */
    void expand_settings(intermediate_model& m) const;

public:
    /**
     * @brief Executes the workflow.
     */
    void expand(intermediate_model& m) const;

private:
    const dynamic::repository& dynamic_repository_;
};

} }

#endif
