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
#include "dogen.m2t.cpp/types/transforms/templates/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/types/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/io/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/lexical_cast/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/test_data/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/tests/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/visual_studio/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/build/initializer.hpp"
#include "dogen.m2t.cpp/types/transforms/initializer.hpp"

namespace dogen::m2t::cpp::transforms {

void initializer::initialize(registrar& rg) {
    types::initializer::initialize(rg);
    hash::initializer::initialize(rg);
    odb::initializer::initialize(rg);
    io::initializer::initialize(rg);
    lexical_cast::initializer::initialize(rg);
    test_data::initializer::initialize(rg);
    serialization::initializer::initialize(rg);
    tests::initializer::initialize(rg);
    templates::initializer::initialize(rg);
    visual_studio::initializer::initialize(rg);
    build::initializer::initialize(rg);
}

}
