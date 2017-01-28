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
#ifndef DOGEN_YARN_TYPES_TRAITS_FWD_HPP
#define DOGEN_YARN_TYPES_TRAITS_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace yarn {

struct traits {
    static std::string input_language();
    static std::string output_language();
    static std::string is_proxy_model();
    static std::string reference();

    struct type_parameters {
        static std::string variable_number_of_parameters();
        static std::string type_parameters_count();
        static std::string type_parameters_always_in_heap();
    };

    struct generalization {
        static std::string is_final();
        static std::string parent();
    };

    struct enumeration {
        static std::string use_implementation_defined_underlying_element();
        static std::string underlying_element();
        static std::string use_implementation_defined_enumerator_values();
        static std::string add_invalid_enumerator();
    };

    struct enumerator {
        static std::string value();
    };
};

} }

#endif
