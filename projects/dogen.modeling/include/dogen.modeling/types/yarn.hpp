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
#ifndef DOGEN_YARN_TYPES_YARN_HPP
#define DOGEN_YARN_TYPES_YARN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {

/**
 * @brief Yarn is the Dogen meta-model.
 *
 * @section yarn_0 Overview
 *
 * Yarn is a meta-model that provides a programming-language-neutral type
 * representation, designed for code generation. There are two core types
 * in yarn: @e endomodel and @e model. Intermediate models are
 * obtained via @frontends and post-processed until they form a cohesive
 * whole. They are then transformed into a final model representation, at
 * which point they are suitable for code generation.
 *
 * @section yarn_0 Mission
 *
 * Yarn's objectives are:
 *
 * @li to provide a set of constructs that the frontends can map to
 * easily, as well as the machinery for frontend management
 * (registration, etc.).
 *
 * @li to provide the tooling required to combine multiple intermediate
 * yarn models together into a bigger model - called the intermediate @e
 * merged model.
 *
 * @li to ensure the consistency of the intermediate merged model via
 * validation rules (such as verifying that all types have a definitions,
 * etc.).
 *
 * @li to provide all the information required to build the final model
 * and to build it.
 */
namespace modeling {
}

}

#endif
