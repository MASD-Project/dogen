/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/types/enum_parser.hpp"
#include "dogen/dia/types/all.hpp"
#include "dogen/dia/io/all_io.hpp"

namespace {

const std::string test_module("dia");
const std::string test_suite("object_types_spec");

}

BOOST_AUTO_TEST_SUITE(object_types)

BOOST_AUTO_TEST_CASE(valid_dia_object_types_are_converted_to_the_correct_enum) {
    SETUP_TEST_LOG_SOURCE("valid_dia_object_types_are_converted_to_the_correct_enum");
    using dogen::dia::object_types;
    auto check_types([&](std::string dia_type, object_types expected) {
            using dogen::dia::enum_parser;
            object_types actual(enum_parser::parse_object_type(dia_type));

            BOOST_LOG_SEV(lg, fine_debug) << "expected:" << expected
                                          << " actual: " << actual;
            BOOST_CHECK(expected == actual);
        });

    const std::string uml_large_package("UML - LargePackage");
    check_types(uml_large_package, object_types::uml_large_package);

    const std::string uml_class("UML - Class");
    check_types(uml_class, object_types::uml_class);
}

BOOST_AUTO_TEST_SUITE_END()
