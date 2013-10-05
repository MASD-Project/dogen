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
#include <array>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/tag_error.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/value_object_io.hpp"
#include "dogen/sml/io/service_io.hpp"
#include "dogen/sml/io/abstract_object_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/tagger.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string test_module("sml");
const std::string test_suite("tagger_spec");

}

using dogen::utility::test::contains_checker;
using dogen::sml::tag_error;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(tagger)

BOOST_AUTO_TEST_CASE(not_enabling_any_facets_results_in_expected_tags) {
    SETUP_TEST_LOG_SOURCE("not_enabling_any_facets_results_in_expected_tags");

    auto m(mock_model_factory::build_single_type_model());
    BOOST_REQUIRE(m.objects().size() == 1);

    dogen::sml::tagger t;
    t.tag(m);
    BOOST_LOG_SEV(lg, debug) << "m: " << m;

    BOOST_CHECK(m.complex_tags().empty());
    // BOOST_CHECK(m.simple_tags().size() == 2);

    const auto& st(m.simple_tags());
    using dogen::sml::tags;
    BOOST_CHECK(st.find(tags::cpp::types::status) != st.end());
    BOOST_CHECK(st.find(tags::generate_preamble) != st.end());
}

BOOST_AUTO_TEST_SUITE_END()
