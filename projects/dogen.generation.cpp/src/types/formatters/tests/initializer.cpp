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
#include "dogen.generation.cpp/types/formatters/tests/class_implementation_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/tests/enum_implementation_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/tests/cmakelists_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/tests/main_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/tests/initializer.hpp"

namespace dogen::generation::cpp::formatters::tests {

void initializer::initialize(registrar& rg) {
    register_formatter<cmakelists_formatter>(rg);
    register_formatter<class_implementation_formatter>(rg);
    register_formatter<enum_implementation_formatter>(rg);
    register_formatter<main_formatter>(rg);
}

}
