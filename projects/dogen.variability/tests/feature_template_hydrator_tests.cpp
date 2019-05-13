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
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.variability/io/meta_model/feature_template_io.hpp"
#include "dogen.variability/types/helpers/feature_template_hydrator.hpp"

namespace {

const std::string empty;
const std::string test_module("dogen.variability.tests");
const std::string test_suite("feature_template_hydrator_tests");

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
        "scope" : "entity"
    }
])");

std::list<dogen::variability::meta_model::feature_template>
hydrate(std::istream& s) {
    dogen::variability::helpers::feature_template_hydrator h;
    return h.hydrate(s);
}

std::list<dogen::variability::meta_model::feature_template>
hydrate(const std::string& content) {
    std::istringstream s(content);
    return hydrate(s);
}

}

using dogen::variability::meta_model::binding_point;
using dogen::variability::meta_model::value_type;
using dogen::variability::meta_model::template_kind;

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
    BOOST_CHECK(tt.location().backend() == backend);
    BOOST_CHECK(tt.location().facet() == facet);
    BOOST_CHECK(tt.location().archetype() == archetype);

    const auto bp(binding_point::element);
    BOOST_CHECK(tt.binding_point() == bp);

    const auto vt(value_type::boolean);
    BOOST_CHECK(tt.value_type() == vt);

    const auto tk(template_kind::instance);
    BOOST_CHECK(tt.kind() == tk);
}

BOOST_AUTO_TEST_SUITE_END()
