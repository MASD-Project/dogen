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
#include <string>
#include <istream>
#include <iterator>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/annotations/io/field_definition_io.hpp"
#include "dogen/annotations/types/json_hydrator.hpp"

namespace {

const std::string empty;
const std::string test_module("annotations");
const std::string test_suite("json_hydrator_tests");

const std::string simple_name("a simple name");
const std::string qualified_name("a qualified name");
const std::string model_name("a model name");

const std::string trivial_field_definition(R"([
    {
        "name" : {
            "simple" : "a simple name",
            "qualified" : "a qualified name"
        },
        "ownership_hierarchy" : {
            "model_name" : "a model name"
        },
        "value_type" : "boolean",
        "definition_type" : "instance",
        "scope" : "not_applicable"
    }
])");

std::list<dogen::annotations::type>
hydrate(std::istream& s) {
    dogen::annotations::json_hydrator h;
    return h.hydrate(s);
}

std::list<dogen::annotations::type>
hydrate(const std::string& content) {
    std::istringstream s(content);
    return hydrate(s);
}

}

BOOST_AUTO_TEST_SUITE(json_hydrator_tests)

BOOST_AUTO_TEST_CASE(trivial_field_definition_hydrates_into_expected_collection) {
    SETUP_TEST_LOG_SOURCE("trivial_field_definition_hydrates_into_expected_collection");

    BOOST_LOG_SEV(lg, debug) << "input: " << trivial_field_definition;
    const auto fds(hydrate(trivial_field_definition));
    BOOST_LOG_SEV(lg, debug) << "field definitions: " << fds;

    BOOST_REQUIRE(std::distance(fds.begin(), fds.end()) == 1);
    const auto& fd(*fds.begin());

    BOOST_CHECK(fd.name().simple() == simple_name);
    BOOST_CHECK(fd.name().qualified() == qualified_name);
    BOOST_CHECK(fd.ownership_hierarchy().model_name() == model_name);

    const auto st(dogen::annotations::scope_types::not_applicable);
    BOOST_CHECK(fd.scope() == st);

    const auto vt(dogen::annotations::value_types::boolean);
    BOOST_CHECK(fd.value_type() == vt);
}

BOOST_AUTO_TEST_SUITE_END()
