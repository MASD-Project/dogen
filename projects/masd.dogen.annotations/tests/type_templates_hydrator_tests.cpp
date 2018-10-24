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
#include "masd.dogen.utility/test/logging.hpp"
#include "masd.dogen.utility/io/list_io.hpp"
#include "masd.dogen.annotations/io/type_template_io.hpp"
#include "masd.dogen.annotations/types/type_templates_hydrator.hpp"

namespace {

const std::string empty;
const std::string test_module("annotations");
const std::string test_suite("type_templates_hydrator_tests");

const std::string simple_name("a simple name");
const std::string qualified_name("a qualified name");
const std::string backend("a backend");
const std::string archetype("an archetype");
const std::string facet("a facet");

const std::string trivial_type_template(R"([
    {
        "name" : {
            "simple" : "a simple name",
            "qualified" : "a qualified name"
        },
        "archetype_location" : {
            "backend" : "a backend",
            "archetype" : "an archetype",
            "facet" : "a facet"
        },
        "value_type" : "boolean",
        "template_kind" : "instance",
        "scope" : "not_applicable"
    }
])");

std::list<dogen::annotations::type_template>
hydrate(std::istream& s) {
    dogen::annotations::type_templates_hydrator h;
    return h.hydrate(s);
}

std::list<dogen::annotations::type_template>
hydrate(const std::string& content) {
    std::istringstream s(content);
    return hydrate(s);
}

}

using masd::dogen::annotations::scope_types;
using masd::dogen::annotations::value_types;
using masd::dogen::annotations::template_kinds;

BOOST_AUTO_TEST_SUITE(type_templates_hydrator_tests)

BOOST_AUTO_TEST_CASE(trivial_type_template_hydrates_into_expected_collection) {
    SETUP_TEST_LOG_SOURCE("trivial_type_template_hydrates_into_expected_collection");

    BOOST_LOG_SEV(lg, debug) << "input: " << trivial_type_template;
    const auto tts(hydrate(trivial_type_template));
    BOOST_LOG_SEV(lg, debug) << "template: " << tts;

    BOOST_REQUIRE(std::distance(tts.begin(), tts.end()) == 1);
    const auto& tt(*tts.begin());

    BOOST_CHECK(tt.name().simple() == simple_name);
    BOOST_CHECK(tt.name().qualified() == qualified_name);
    BOOST_CHECK(tt.archetype_location().backend() == backend);
    BOOST_CHECK(tt.archetype_location().facet() == facet);
    BOOST_CHECK(tt.archetype_location().archetype() == archetype);

    const auto st(scope_types::not_applicable);
    BOOST_CHECK(tt.scope() == st);

    const auto vt(value_types::boolean);
    BOOST_CHECK(tt.value_type() == vt);

    const auto tk(template_kinds::instance);
    BOOST_CHECK(tt.kind() == tk);
}

BOOST_AUTO_TEST_SUITE_END()
