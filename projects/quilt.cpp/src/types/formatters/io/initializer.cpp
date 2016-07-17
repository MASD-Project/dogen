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
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/includers_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/io/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/io/enum_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/io/smart_pointer_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/associative_container_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/optional_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/pair_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/ptree_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/sequence_container_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/smart_pointer_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/string_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/variant_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/initializer.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

void initializer::initialize(registrar& rg) {
    initialise_formatter<includers_formatter>(rg, traits::facet_name());
    initialise_formatter<class_header_formatter>(rg);
    initialise_formatter<class_implementation_formatter>(rg);
    initialise_formatter<enum_header_formatter>(rg);
    initialise_formatter<enum_implementation_formatter>(rg);
    initialise_formatter_helper<smart_pointer_helper>(rg);
    initialise_formatter_helper<associative_container_helper>(rg);
    initialise_formatter_helper<optional_helper>(rg);
    initialise_formatter_helper<pair_helper>(rg);
    initialise_formatter_helper<ptree_helper>(rg);
    initialise_formatter_helper<sequence_container_helper>(rg);
    initialise_formatter_helper<string_helper>(rg);
    initialise_formatter_helper<variant_helper>(rg);
}

} } } } }
