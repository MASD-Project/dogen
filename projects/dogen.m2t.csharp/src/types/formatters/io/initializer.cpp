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
#include "dogen.m2t.csharp/types/formatters/registrar.hpp"
#include "dogen.m2t.csharp/types/formatters/io/enumerable_helper.hpp"
#include "dogen.m2t.csharp/types/formatters/io/primitive_formatter.hpp"
#include "dogen.m2t.csharp/types/formatters/io/class_formatter.hpp"
#include "dogen.m2t.csharp/types/formatters/io/enum_formatter.hpp"
#include "dogen.m2t.csharp/types/formatters/io/assistant_formatter.hpp"
#include "dogen.m2t.csharp/types/formatters/io/initializer.hpp"

namespace dogen::m2t::csharp::formatters::io {

void initializer::initialize(registrar& rg) {
    register_formatter<class_formatter>(rg);
    register_formatter<primitive_formatter>(rg);
    register_formatter<enum_formatter>(rg);
    register_formatter<assistant_formatter>(rg);
    register_formatter_helper<enumerable_helper>(rg);
}

}
