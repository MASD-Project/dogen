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
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/pod_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/io/relationships_io.hpp"
#include "dogen/cpp/types/extractor.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string empty;
const std::string test_module("cpp");
const std::string test_suite("extractor_spec");

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::pod_name(0) == qn.type_name();
}

// bool is_type_one(const dogen::sml::qname& qn) {
//     return mock_model_factory::pod_name(1) == qn.type_name();
// }

}

BOOST_AUTO_TEST_SUITE(extractor)

BOOST_AUTO_TEST_CASE(pod_with_no_properties_and_no_inheritance_has_no_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_no_properties_and_no_inheritance_has_no_relationships");

    const auto m(mock_model_factory::build_single_pod_model(0));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(!m.pods().empty());

    dogen::cpp::extractor x(m.pods());
    const auto r(x.extract_dependency_graph(m.pods().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_CHECK(r.names().empty());
    BOOST_CHECK(r.forward_decls().empty());
    BOOST_CHECK(r.keys().empty());
    BOOST_CHECK(r.leaves().empty());
    BOOST_CHECK(!r.has_std_string());
    BOOST_CHECK(!r.has_variant());
    BOOST_CHECK(!r.is_parent());
    BOOST_CHECK(!r.is_child());
    BOOST_CHECK(!r.requires_stream_manipulators());
    BOOST_CHECK(!r.has_std_pair());
}

BOOST_AUTO_TEST_CASE(pod_with_parent_has_one_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_parent_has_one_name_in_relationships");

    const auto m(mock_model_factory::pod_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(!m.pods().empty());

    dogen::cpp::extractor x(m.pods());

    bool found(false);
    for (const auto pair : m.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;

            found = true;
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;
        }
    }
    BOOST_CHECK(found);
}

// pod with primitive
// pod with bool
// pod with other pod
// pod with missing relationship
// pod with pair
// pod with variant
// 3 levels deep pod
// pod with shared_ptr -> fwd decls


BOOST_AUTO_TEST_SUITE_END()
