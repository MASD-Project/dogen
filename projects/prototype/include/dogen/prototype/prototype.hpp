/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_PROTOTYPE_PROTOTYPE_HPP
#define DOGEN_PROTOTYPE_PROTOTYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace kitanda {

/**
 * @brief The prototype model is a sandbox for introducing new code
 * generation features.
 *
 * Before attempting to implement a feature one should manually change
 * the prototype model and make sure the feature works as expected;
 * once that is done the feature should be introduced into dogen;
 * the output of the code generator can then be compared to the
 * current state of the prototype model.
 *
 */
namespace prototype {

} }

#endif
