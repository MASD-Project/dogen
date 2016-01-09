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
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/includers_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/initializer.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {

void initializer::initialize(registrar& rg) {
    initialise_formatter<includers_formatter>(rg, traits::facet_name());
    initialise_formatter<class_header_formatter>(rg);
    initialise_formatter<class_implementation_formatter>(rg);
    initialise_formatter<enum_header_formatter>(rg);
}

} } } } }
