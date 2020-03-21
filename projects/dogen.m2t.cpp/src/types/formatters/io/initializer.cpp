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
#include "dogen.m2t.cpp/types/formatters/io/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/io/builtin_header_formatter.hpp"
#include "dogen.m2t.cpp/types/formatters/io/primitive_header_formatter.hpp"
#include "dogen.m2t.cpp/types/formatters/io/primitive_implementation_formatter.hpp"
#include "dogen.m2t.cpp/types/formatters/io/class_header_formatter.hpp"
#include "dogen.m2t.cpp/types/formatters/io/class_implementation_formatter.hpp"
#include "dogen.m2t.cpp/types/formatters/io/enum_header_formatter.hpp"
#include "dogen.m2t.cpp/types/formatters/io/enum_implementation_formatter.hpp"
#include "dogen.m2t.cpp/types/formatters/io/smart_pointer_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/associative_container_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/optional_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/pair_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/ptree_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/sequence_container_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/smart_pointer_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/string_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/variant_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/io/initializer.hpp"

namespace dogen::m2t::cpp::formatters::io {

void initializer::initialize(registrar& rg) {
    register_formatter<builtin_header_formatter>(rg);
    register_formatter<primitive_header_formatter>(rg);
    register_formatter<primitive_implementation_formatter>(rg);
    register_formatter<class_header_formatter>(rg);
    register_formatter<class_implementation_formatter>(rg);
    register_formatter<enum_header_formatter>(rg);
    register_formatter<enum_implementation_formatter>(rg);
    register_helper_formatter<smart_pointer_helper>(rg);
    register_helper_formatter<associative_container_helper>(rg);
    register_helper_formatter<optional_helper>(rg);
    register_helper_formatter<pair_helper>(rg);
    register_helper_formatter<ptree_helper>(rg);
    register_helper_formatter<sequence_container_helper>(rg);
    register_helper_formatter<string_helper>(rg);
    register_helper_formatter<variant_helper>(rg);
}

}
