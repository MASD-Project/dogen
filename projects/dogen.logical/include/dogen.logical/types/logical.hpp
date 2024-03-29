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
#ifndef DOGEN_LOGICAL_TYPES_LOGICAL_HPP
#define DOGEN_LOGICAL_TYPES_LOGICAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief The logcal model defines the core entities that live in the logical dimension of
 * MASD's conceptual model.
 *
 * Overview
 *
 * The logical model strives to provide a technical-space agnostic element
 * representation, designed for code generation. Codec models are obtained via
 * frontends and transformed into "bare" logical models, at which point they can
 * enter its pipeline. Within it, they are processed until they form a cohesive
 * whole. They are then in a suitable state for code generation.
 *
 * Mission
 *
 * The objectives of the logical model are:
 *
 * - to represent all high-level entities that exist across a number of technical
 *   spaces used in software engineering. These entities are not necessarily
 *   limited to programming entities, though, of course, these form the core set of
 *   elements we're interested in. Additional entities such as build sytems and
 *   high-level patterns such as GoF and others are also captured.
 * - to provide the tooling required to combine multiple models together into a
 *   bigger model - called the merged model.
 * - to ensure the consistency of the merged model via validation rules (such as
 *   verifying that all types have a definitions, etc.).
 *
 * UML representation:
 *
 * \image html dogen.logical/modeling/dogen.logical.svg
 */
namespace dogen::logical {
}

#endif
