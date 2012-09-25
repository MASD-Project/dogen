/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE dia_spec
#include <boost/test/included/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/utility/dia_utility.hpp"
#include "dogen/dia/domain/dia_domain.hpp"
#include "dogen/dia/io/dia_io.hpp"

namespace {

const std::string test_module("dia");
const std::string test_suite("dia_spec");

}

BOOST_AUTO_TEST_SUITE(dia)

BOOST_AUTO_TEST_CASE(valid_dia_object_types_are_converted_to_the_correct_enum) {
    SETUP_TEST_LOG_SOURCE("valid_dia_object_types_are_converted_to_the_correct_enum");
    using dogen::dia::object_types;
    auto check_types([&](std::string dia_type, object_types expected) {
            using dogen::dia::utility::parse_object_type;
            object_types actual(parse_object_type(dia_type));

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
