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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia_to_sml/types/object_transformer.hpp"
#include "dogen/dia/test/mock_object_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("object_transformer_spec");

}

using dogen::utility::test::contains_checker;
using dogen::dia::test::mock_object_factory;

BOOST_AUTO_TEST_SUITE(object_transformer)

BOOST_AUTO_TEST_CASE(transforming_uml_class_with_no_stereotype_results_in_expected_pod) {
    SETUP_TEST_LOG("transforming_uml_class_with_no_stereotype_results_in_expected_pod");
    dogen::dia_to_sml::context c;
    dogen::dia_to_sml::object_transformer t(c);
    // t.transform(mock_object_factory::build_class(0));
}

BOOST_AUTO_TEST_SUITE_END()
