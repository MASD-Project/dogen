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
#ifndef MASD_DOGEN_CODING_TYPES_TRAITS_FWD_HPP
#define MASD_DOGEN_CODING_TYPES_TRAITS_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace masd::dogen::coding {

struct traits {
    static std::string enabled();
    static std::string directory();
    static std::string postfix();
    static std::string supported();
    static std::string overwrite();
    static std::string input_language();
    static std::string output_language();
    static std::string is_proxy_model();
    static std::string reference();
    static std::string external_modules();
    static std::string model_modules();
    static std::string enable_backend_directories();
    static std::string force_backend_directory();

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

    struct primitive {
        static std::string underlying_element();
        static std::string is_nullable();
        static std::string use_type_aliasing();
    };

    struct orm {
        static std::string database_system();
        static std::string table_name();
        static std::string schema_name();
        static std::string is_primary_key();
        static std::string column_name();
        static std::string is_nullable();
        static std::string letter_case();
        static std::string type_override();
        static std::string is_composite();
    };
};

}

#endif
