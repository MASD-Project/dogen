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
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/builtin_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/primitive_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/primitive_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/class_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/class_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/enum_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/associative_container_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/date_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/optional_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/pair_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/path_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/ptime_helper.hpp"
#include "dogen.text.cpp/types/transforms/hash/ptree_helper.hpp"
#include "dogen.text.cpp/types/transforms/hash/sequence_container_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/smart_pointer_helper.hpp"
#include "dogen.text.cpp/types/transforms/hash/time_duration_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/variant_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/initializer.hpp"

namespace dogen::text::cpp::transforms::hash {

void initializer::initialize(registrar& rg) {
    register_formatter<builtin_header_transform>(rg);
    register_formatter<primitive_header_transform>(rg);
    register_formatter<primitive_implementation_transform>(rg);
    register_formatter<class_header_transform>(rg);
    register_formatter<class_implementation_transform>(rg);
    register_formatter<enum_header_transform>(rg);

    register_helper_formatter<associative_container_helper_transform>(rg);
    register_helper_formatter<date_helper_transform>(rg);
    register_helper_formatter<optional_helper_transform>(rg);
    register_helper_formatter<pair_helper_transform>(rg);
    register_helper_formatter<path_helper_transform>(rg);
    register_helper_formatter<ptime_helper>(rg);
    register_helper_formatter<ptree_helper>(rg);
    register_helper_formatter<sequence_container_helper_transform>(rg);
    register_helper_formatter<smart_pointer_helper>(rg);
    register_helper_formatter<time_duration_helper_transform>(rg);
    register_helper_formatter<variant_helper_transform>(rg);
}

}
