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
#include "dogen/quilt.cpp/types/formatters/master_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/associative_container_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/date_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/optional_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/pair_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/path_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/ptime_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/ptree_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/sequence_container_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/smart_pointer_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/time_duration_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/variant_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/initializer.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {

void initializer::initialize(registrar& rg) {
    register_formatter<master_header_formatter>(rg, traits::facet());
    register_formatter<primitive_header_formatter>(rg);
    register_formatter<class_header_formatter>(rg);
    register_formatter<class_implementation_formatter>(rg);
    register_formatter<enum_header_formatter>(rg);
    register_formatter_helper<associative_container_helper>(rg);
    register_formatter_helper<date_helper>(rg);
    register_formatter_helper<optional_helper>(rg);
    register_formatter_helper<pair_helper>(rg);
    register_formatter_helper<path_helper>(rg);
    register_formatter_helper<ptime_helper>(rg);
    register_formatter_helper<ptree_helper>(rg);
    register_formatter_helper<sequence_container_helper>(rg);
    register_formatter_helper<smart_pointer_helper>(rg);
    register_formatter_helper<time_duration_helper>(rg);
    register_formatter_helper<variant_helper>(rg);
}

} } } } }
