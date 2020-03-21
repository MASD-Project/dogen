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
#ifndef DOGEN_M2T_CPP_TYPES_TRANSFORMS_INCLUSION_CONSTANTS_HPP
#define DOGEN_M2T_CPP_TYPES_TRANSFORMS_INCLUSION_CONSTANTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen::m2t::cpp::transforms {

/**
 * @brief All inclusions for implementation-level dependencies in
 * formatters.
 */
struct inclusion_constants {

    struct std {
        static ::std::string list();
        static ::std::string string();
        static ::std::string iosfwd();
        static ::std::string algorithm();
        static ::std::string ostream();
        static ::std::string iostream();
        static ::std::string sstream();
        static ::std::string functional();
        static ::std::string stdexcept();
    };

    struct boost {
        static ::std::string shared_ptr();
        static ::std::string lexical_cast();
        static ::std::string predef();

        struct property_tree {
            static ::std::string ptree();
            static ::std::string json_parser();
        };

        struct type_traits {
            static ::std::string is_virtual_base_of();
        };

        struct archive {
            static ::std::string xml_iarchive();
            static ::std::string xml_oarchive();
            static ::std::string text_iarchive();
            static ::std::string text_oarchive();
            static ::std::string binary_iarchive();
            static ::std::string binary_oarchive();
            static ::std::string polymorphic_iarchive();
            static ::std::string polymorphic_oarchive();
        };

        struct serialization {
            static ::std::string nvp();
            static ::std::string split_free();
            static ::std::string assume_abstract();
            static ::std::string shared_ptr();
        };

        struct exception {
            static ::std::string info();
            static ::std::string diagnostic_information();
        };

        struct test {
            static ::std::string unit_test();
            static ::std::string unit_test_monitor();
        };
    };
};

}

#endif
