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
#include "dogen/config.hpp"
#include "dogen.text.csharp/types/initializer.hpp"
#include "dogen.text.cpp/types/initializer.hpp"
#include "dogen.injection.json/types/initializer.hpp"
#include "dogen.injection.org_mode/types/initializer.hpp"
#include "dogen.injection.dia/types/initializer.hpp"
#include "dogen.tracing/types/initializer.hpp"
#ifdef DOGEN_HAVE_RELATIONAL_MODEL
#include "dogen.relational/types/initializer.hpp"
#endif // DOGEN_HAVE_RELATIONAL_MODEL
#include "dogen.cli/types/initializer.hpp"

namespace dogen::cli {

void initializer::initialize() {
    dogen::injection::org_mode::initializer::initialize();
    dogen::injection::json::initializer::initialize();
    dogen::injection::dia::initializer::initialize();
    dogen::text::csharp::initializer::initialize();
    dogen::text::cpp::initializer::initialize();
    dogen::tracing::initializer::initialize();
#ifdef DOGEN_HAVE_RELATIONAL_MODEL
    dogen::relational::initializer::initialize();
#endif // DOGEN_HAVE_RELATIONAL_MODEL
}

}
