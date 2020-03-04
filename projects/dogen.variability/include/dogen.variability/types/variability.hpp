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
#ifndef DOGEN_VARIABILITY_TYPES_VARIABILITY_HPP
#define DOGEN_VARIABILITY_TYPES_VARIABILITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief The varibility model is responsible for managing variation in MASD.
 *
 * One of the core principles of MASD is to enable the development of
 * "families" of software products; that is, sets of products which share
 * similar "traits". Those traits are encoded as "configuration" so that
 * we can talk about them at a higher level of abstraction. This approach
 * is often referred to in the literature as Software Product Line
 * Engineering (SPLE). MASD takes a very simplistic view of SPLE,
 * allowing a very restricted form of variation across a set of
 * well-defined features. The present model provides the basic
 * infrastructure required to define features, as well as to read those
 * features from dynamic data structures.
 *
 * Note that the present model only concerns itself with the low-level
 * implementation of variability. You can think of it as a stack, with
 * this model sitting at the bottom. Above it lie the logical
 * representation of variability, which enables the code generator to
 * generate code that makes use of the infrastructure provided by this
 * model. But the present model is designed to be understood in complete
 * isolation from the layers above (and in fact, precedes the generalised
 * approach).
 *
 * The variability space is connected to the physical dimension. We
 * originally tried to avoid this, but due to how some features are
 * defined, we did not achieve our aims, The main reason is because we
 * have feature templates which are instantiated according to the
 * topology of physical space (e.g. enablement, postfix).  In order to
 * instantiate those templates, one needs to know the shape of physical
 * space (by definition). In addition, we also query those features by
 * properties of physical space; e.g., "give me all features called
 * 'enablement' for every archetype". This is so that we can compute
 * enablement in a general manner. At present, enablement is the only use
 * case.
 */
namespace dogen::variability {
}

#endif
