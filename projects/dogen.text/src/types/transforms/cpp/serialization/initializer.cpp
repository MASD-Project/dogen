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
// #include "dogen.text.cpp/types/transforms/serialization/builtin_header_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/primitive_header_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/primitive_implementation_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/class_header_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/class_implementation_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/enum_header_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/class_forward_declarations_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/primitive_forward_declarations_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/type_registrar_header_transform.hpp"
// #include "dogen.text.cpp/types/transforms/serialization/type_registrar_implementation_transform.hpp"
#include "dogen.text/types/transforms/cpp/serialization/path_helper_transform.hpp"

#include "dogen.text/types/transforms/cpp/serialization/initializer.hpp"

namespace dogen::text::transforms::cpp::serialization {

void initializer::initialize(registrar& rg) {
    // register_formatter<builtin_header_transform>(rg);
    // register_formatter<primitive_header_transform>(rg);
    // register_formatter<primitive_implementation_transform>(rg);
    // register_formatter<class_header_transform>(rg);
    // register_formatter<class_implementation_transform>(rg);
    // register_formatter<enum_header_transform>(rg);
    // register_formatter<class_forward_declarations_transform>(rg);
    // register_formatter<primitive_forward_declarations_transform>(rg);
    // register_formatter<type_registrar_header_transform>(rg);
    // register_formatter<type_registrar_implementation_transform>(rg);
    register_helper<path_helper_transform>(rg);
}

}
