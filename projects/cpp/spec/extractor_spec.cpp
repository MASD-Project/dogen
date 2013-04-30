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
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/cpp/types/extraction_error.hpp"
#include "dogen/cpp/types/extractor.hpp"

using dogen::sml::test::mock_model_factory;
typedef mock_model_factory::property_types property_types;

namespace {

const std::string empty;
const std::string test_module("cpp");
const std::string test_suite("extractor_spec");
const std::string pod_not_found("Could not find QName in pod container");

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::pod_name(0) == qn.type_name();
}

bool is_type_one(const dogen::sml::qname& qn) {
    return mock_model_factory::pod_name(1) == qn.type_name();
}

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(extractor)

BOOST_AUTO_TEST_CASE(pod_with_no_properties_and_no_inheritance_has_no_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_no_properties_and_no_inheritance_has_no_names_in_relationships");

    const auto m(mock_model_factory::build_single_pod_model(0));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.pods().size() == 1);

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
            BOOST_LOG_SEV(lg, debug) << "found child pod: " << pair.first;

            found = true;
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_REQUIRE(is_type_one(*r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_one(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent pod: " << pair.first;

            found = true;
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().empty());
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(pod_with_unsigned_int_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_unsigned_int_property_has_expected_name_in_relationships");

    const auto pt(property_types::unsigned_int);
    const auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);
    BOOST_REQUIRE(m.pods().begin()->second.properties().size() == 1);

    dogen::cpp::extractor x(m.pods());
    const auto r(x.extract_dependency_graph(m.pods().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 1);
    BOOST_CHECK(r.names().begin()->type_name() == "unsigned int");
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

BOOST_AUTO_TEST_CASE(pod_with_boolean_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_boolean_property_has_expected_name_in_relationships");

    const auto pt(property_types::boolean);
    const auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);
    BOOST_REQUIRE(m.pods().begin()->second.properties().size() == 1);

    dogen::cpp::extractor x(m.pods());
    const auto r(x.extract_dependency_graph(m.pods().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 1);
    BOOST_CHECK(r.names().begin()->type_name() == "bool");
    BOOST_CHECK(r.forward_decls().empty());
    BOOST_CHECK(r.keys().empty());
    BOOST_CHECK(r.leaves().empty());
    BOOST_CHECK(!r.has_std_string());
    BOOST_CHECK(!r.has_variant());
    BOOST_CHECK(!r.is_parent());
    BOOST_CHECK(!r.is_child());
    BOOST_CHECK(r.requires_stream_manipulators());
    BOOST_CHECK(!r.has_std_pair());
}

BOOST_AUTO_TEST_CASE(pod_with_other_pod_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_other_pod_property_has_expected_names_in_relationships");

    const auto pt(property_types::other_pod);
    const auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.pods().size() == 2);

    dogen::cpp::extractor x(m.pods());
    bool found(false);
    for (const auto pair : m.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child pod: " << pair.first;
            const auto r(x.extract_dependency_graph(pair.second));

            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_CHECK(is_type_one(*r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());

            found = true;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(pod_with_missing_pod_property_throws) {
    SETUP_TEST_LOG_SOURCE("pod_with_missing_pod_property_throws");

    const auto m(mock_model_factory::pod_with_missing_property_type());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);

    dogen::cpp::extractor x(m.pods());
    const auto p(m.pods().begin()->second);

    using dogen::cpp::extraction_error;
    contains_checker<extraction_error> c(pod_not_found);
    BOOST_CHECK_EXCEPTION(x.extract_dependency_graph(p), extraction_error, c);
}

BOOST_AUTO_TEST_CASE(pod_with_pair_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_pair_has_expected_names_in_relationships");

    const auto pt(property_types::std_pair);
    const auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);
    BOOST_REQUIRE(m.pods().begin()->second.properties().size() == 1);

    dogen::cpp::extractor x(m.pods());
    const auto r(x.extract_dependency_graph(m.pods().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 2);
    BOOST_CHECK(r.forward_decls().empty());
    BOOST_CHECK(r.keys().empty());
    BOOST_CHECK(r.leaves().empty());
    BOOST_CHECK(!r.has_std_string());
    BOOST_CHECK(!r.has_variant());
    BOOST_CHECK(!r.is_parent());
    BOOST_CHECK(!r.is_child());
    BOOST_CHECK(r.requires_stream_manipulators());
    BOOST_CHECK(r.has_std_pair());
}

BOOST_AUTO_TEST_CASE(pod_with_variant_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_variant_has_expected_names_in_relationships");

    const auto pt(property_types::boost_variant);
    const auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);
    BOOST_REQUIRE(m.pods().begin()->second.properties().size() == 1);

    dogen::cpp::extractor x(m.pods());
    const auto r(x.extract_dependency_graph(m.pods().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 3);
    BOOST_CHECK(r.forward_decls().empty());
    BOOST_CHECK(r.keys().empty());
    BOOST_CHECK(r.leaves().empty());
    BOOST_CHECK(!r.has_std_string());
    BOOST_CHECK(r.has_variant());
    BOOST_CHECK(!r.is_parent());
    BOOST_CHECK(!r.is_child());
    BOOST_CHECK(r.requires_stream_manipulators());
    BOOST_CHECK(!r.has_std_pair());
}

BOOST_AUTO_TEST_CASE(pod_with_std_string_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("pod_with_std_string_property_has_expected_name_in_relationships");

    const auto pt(property_types::std_string);
    const auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);
    BOOST_REQUIRE(m.pods().begin()->second.properties().size() == 1);

    dogen::cpp::extractor x(m.pods());
    const auto r(x.extract_dependency_graph(m.pods().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 1);
    BOOST_CHECK(r.names().begin()->type_name() == "string");
    BOOST_CHECK(r.forward_decls().empty());
    BOOST_CHECK(r.keys().empty());
    BOOST_CHECK(r.leaves().empty());
    BOOST_CHECK(r.has_std_string());
    BOOST_CHECK(!r.has_variant());
    BOOST_CHECK(!r.is_parent());
    BOOST_CHECK(!r.is_child());
    BOOST_CHECK(!r.requires_stream_manipulators());
    BOOST_CHECK(!r.has_std_pair());
}

// BOOST_IGNORE_AUTO_TEST_CASE(pod_with_boost_shared_ptr_property_has_expected_name_in_relationships) {
//     SETUP_TEST_LOG_SOURCE("pod_with_boost_shared_ptr_property_has_expected_name_in_relationships");

//     const auto pt(property_types::boost_shared_ptr);
//     const auto m(mock_model_factory::pod_with_property(pt));
//     BOOST_LOG_SEV(lg, debug) << "input model: " << m;
//     BOOST_REQUIRE(m.pods().size() == 1);
//     BOOST_REQUIRE(m.pods().begin()->second.properties().size() == 1);

//     dogen::cpp::extractor x(m.pods());
//     const auto r(x.extract_dependency_graph(m.pods().begin()->second));
//     BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

//     BOOST_REQUIRE(r.names().size() == 2);
//     BOOST_CHECK(r.forward_decls().size() == 1);
//     BOOST_CHECK(r.keys().empty());
//     BOOST_CHECK(r.leaves().empty());
//     BOOST_CHECK(!r.has_std_string());
//     BOOST_CHECK(!r.has_variant());
//     BOOST_CHECK(!r.is_parent());
//     BOOST_CHECK(!r.is_child());
//     BOOST_CHECK(!r.requires_stream_manipulators());
//     BOOST_CHECK(!r.has_std_pair());
// }

BOOST_AUTO_TEST_SUITE_END()
