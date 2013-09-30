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
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/hydration_error.hpp"
#include "dogen/sml/types/json_hydrator.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("json_hydrator_spec");

const std::string model_name("a_model");
const std::string documentation("a_doc");
const std::string type_name("a_type");
const std::string model_key("model_key");
const std::string model_value("model_value");
const std::string odb_pragma_key("type_key");
const std::string odb_pragma_value("odb_pragma_value");
const std::string type_key("type_key");
const std::string type_value("type_value");

const std::string trivial_model(R"({
    "model_name" : "a_model",
    "documentation" : "a_doc",
    "origin" : "system",
    "types" : [
        {
            "meta_type" : "value_object",
            "simple_name" : "a_type"
        }
     ]
  }
)");

const std::string tagged_model(R"({
    "model_name" : "a_model",
    "documentation" : "a_doc",
    "origin" : "system",
    "tags" : [
        {
            "model_key" : "model_value",
            "ODB_PRAGMA" : "odb_pragma"
        }
    ],
    "types" : [
        {
            "meta_type" : "value_object",
            "simple_name" : "a_type",
            "tags" : [
                {
                    "type_key" : "type_value",
                    "ODB_PRAGMA" : "type_odb_pragma"
                }
            ]
       }
   ]
}
)");


}

using dogen::utility::test::contains_checker;
using dogen::sml::hydration_error;

BOOST_AUTO_TEST_SUITE(json_hydrator)

BOOST_AUTO_TEST_CASE(trivial_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("trivial_model_hydrates_into_expected_model");

    std::istringstream s(trivial_model);
    dogen::sml::json_hydrator h;
    const auto m(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.name().model_name() == model_name);
    BOOST_CHECK(m.name().module_path().empty());
    BOOST_CHECK(m.name().external_module_path().empty());

    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& pair(*m.objects().begin());
    const auto& qn(pair.second->name());

    BOOST_CHECK(pair.first == qn);
    BOOST_CHECK(qn.simple_name() == type_name);
    BOOST_CHECK(qn.model_name() == m.name().model_name());
    BOOST_CHECK(qn.module_path().empty());
    BOOST_CHECK(qn.external_module_path().empty());
}

BOOST_AUTO_TEST_CASE(tagged_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("tagged_model_hydrates_into_expected_model");

    std::istringstream s(tagged_model);
    dogen::sml::json_hydrator h;
    const auto m(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.name().model_name() == model_name);
    BOOST_CHECK(m.name().module_path().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
    // BOOST_CHECK(m.complex_tags().size() == 1);

    // const auto i(m.complex_tags().find(odb_pragma_key));
    // BOOST_REQUIRE(i != m.complex_tags().end());
    // BOOST_CHECK(i->second.size() != 0);
    // BOOST_CHECK(i->second.front() == odb_pragma_value);

    // BOOST_CHECK(m.simple_tags().size() == 1);
    // const auto j(m.simple_tags().find(model_key));
    // BOOST_REQUIRE(j != m.simple_tags().end());
    // BOOST_CHECK(j->first != model_key);
    // BOOST_CHECK(j->second == model_value);

    BOOST_REQUIRE(m.objects().size() == 1);

    const auto& pair(*m.objects().begin());
    const auto& qn(pair.second->name());

    BOOST_CHECK(pair.first == qn);
    BOOST_CHECK(qn.simple_name() == type_name);
    BOOST_CHECK(qn.model_name() == m.name().model_name());
    BOOST_CHECK(qn.module_path().empty());
    BOOST_CHECK(qn.external_module_path().empty());
}

BOOST_AUTO_TEST_SUITE_END()
