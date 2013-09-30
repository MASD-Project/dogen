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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/types/boost_model_factory.hpp"
#include "dogen/sml/types/std_model_factory.hpp"
#include "dogen/sml/types/primitive_model_factory.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("factories");
const std::string boost_model("boost");
const std::string primitive_model("primitive_model");
const std::string std_model("std");

}

using dogen::sml::origin_types;

BOOST_AUTO_TEST_SUITE(factories)

BOOST_AUTO_TEST_CASE(producing_boost_model_generates_expected_types) {
    SETUP_TEST_LOG_SOURCE("producing_boost_model_generates_expected_types");

    const auto m(dogen::sml::boost_model_factory::create());
    BOOST_LOG_SEV(lg, debug) << m;
    BOOST_CHECK(m.name().model_name() == boost_model);
    BOOST_CHECK(m.origin_type() == origin_types::system);

    const auto& objects(m.objects());
    BOOST_CHECK(!objects.empty());
    for (const auto& pair : objects) {
        const auto& o(*pair.second);
        const auto qn(o.name());
        BOOST_CHECK(qn.model_name() == boost_model);
        BOOST_CHECK(qn.external_module_path().empty());
        if (!qn.module_path().empty()) {
            bool module_found(false);
            for (const auto& pair : m.modules()) {
                const auto mod(pair.second);
                auto pp(mod.name().module_path());
                pp.push_back(mod.name().simple_name());
                BOOST_LOG_SEV(lg, info) << "Converted path: " << pp;
                if (qn.module_path() == pp) {
                    module_found = true;
                    break;
                }
            }

            if (!module_found)
                BOOST_LOG_SEV(lg, error) << "Object has undefined module: "
                                         << qn;
            BOOST_CHECK(module_found);
        }
    }
    BOOST_CHECK(m.primitives().empty());
    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(!m.modules().empty());
    BOOST_CHECK(m.references().empty());
    BOOST_CHECK(m.leaves().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
}

BOOST_AUTO_TEST_CASE(producing_std_model_generates_expected_types) {
    SETUP_TEST_LOG_SOURCE("producing_std_model_generates_expected_types");

    const auto m(dogen::sml::std_model_factory::create());
    BOOST_LOG_SEV(lg, debug) << m;
    BOOST_CHECK(m.name().model_name() == std_model);
    BOOST_CHECK(m.origin_type() == origin_types::system);

    const auto& objects(m.objects());
    BOOST_CHECK(!objects.empty());
    for (const auto& pair : objects) {
        const auto& o(*pair.second);
        const auto qn(o.name());
        BOOST_CHECK(qn.model_name() == std_model);
        BOOST_CHECK(qn.external_module_path().empty());
    }

    const auto primitives(m.primitives());
    BOOST_CHECK(!m.primitives().empty());
    for (const auto& pair : primitives) {
        const auto p(pair.second);
        const auto qn(p.name());
        BOOST_CHECK(qn.model_name() == std_model);
        BOOST_CHECK(qn.external_module_path().empty());
    }

    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
    BOOST_CHECK(m.references().empty());
    BOOST_CHECK(m.leaves().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
}

BOOST_AUTO_TEST_CASE(producing_primitive_model_generates_expected_types) {
    SETUP_TEST_LOG_SOURCE("producing_primitive_model_generates_expected_types");

    const auto m(dogen::sml::primitive_model_factory::create());
    BOOST_LOG_SEV(lg, debug) << m;
    BOOST_CHECK(m.name().model_name() == primitive_model);
    BOOST_CHECK(m.origin_type() == origin_types::system);

    BOOST_CHECK(m.objects().empty());
    const auto primitives(m.primitives());
    BOOST_CHECK(!primitives.empty());
    for (const auto& pair : primitives) {
        const auto p(pair.second);
        const auto qn(p.name());
        BOOST_CHECK(qn.model_name().empty());
        BOOST_CHECK(qn.external_module_path().empty());
    }

    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
    BOOST_CHECK(m.references().empty());
    BOOST_CHECK(m.leaves().empty());
    BOOST_CHECK(m.name().external_module_path().empty());
}

BOOST_AUTO_TEST_SUITE_END()
