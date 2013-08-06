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
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml_to_cpp/io/relationships_io.hpp"
#include "dogen/sml_to_cpp/types/extraction_error.hpp"
#include "dogen/sml_to_cpp/types/extractor.hpp"

using dogen::sml::test::mock_model_factory;
typedef mock_model_factory::object_types object_types;
typedef mock_model_factory::property_types property_types;

namespace {

const std::string empty;
const std::string test_module("sml_to_cpp");
const std::string test_suite("extractor_spec");
const std::string object_not_found("Could not find QName in object container");

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::simple_name(0) == qn.simple_name();
}

bool is_type_one(const dogen::sml::qname& qn) {
    return mock_model_factory::simple_name(1) == qn.simple_name();
}

bool is_type_two(const dogen::sml::qname& qn) {
    return mock_model_factory::simple_name(2) == qn.simple_name();
}

bool is_type_three(const dogen::sml::qname& qn) {
    return mock_model_factory::simple_name(3) == qn.simple_name();
}

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(extractor)

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_no_properties_and_no_inheritance_has_no_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_no_properties_and_no_inheritance_has_no_names_in_relationships");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 1);

    dogen::sml_to_cpp::extractor x(m);
    const auto r(x.extract_dependency_graph(*m.objects().begin()->second));
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

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_parent_has_one_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_parent_has_one_name_in_relationships");

    const auto m(mock_model_factory::object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(!m.objects().empty());

    dogen::sml_to_cpp::extractor x(m);

    std::array<bool, 2> found({{ false, false }});
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child object: " << pair.first;

            found[0] = true;
            const auto r(x.extract_dependency_graph(*pair.second));
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
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[1] = true;
            const auto r(x.extract_dependency_graph(*pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().empty());
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().size() == 1);
            BOOST_REQUIRE(is_type_zero(*r.leaves().begin()));
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        }
    }
    BOOST_CHECK(found[0] && found[1]);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_unsigned_int_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_unsigned_int_property_has_expected_name_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::unsigned_int);
    const auto m(mock_model_factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);
    BOOST_REQUIRE(m.objects().begin()->second->properties().size() == 1);

    dogen::sml_to_cpp::extractor x(m);
    const auto r(x.extract_dependency_graph(*m.objects().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 1);
    BOOST_CHECK(r.names().begin()->simple_name() == "unsigned int");
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

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_boolean_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_boolean_property_has_expected_name_in_relationships");


    const auto ot(object_types::value_object);
    const auto pt(property_types::boolean);
    const auto m(mock_model_factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);
    BOOST_REQUIRE(m.objects().begin()->second->properties().size() == 1);

    dogen::sml_to_cpp::extractor x(m);
    const auto r(x.extract_dependency_graph(*m.objects().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 1);
    BOOST_CHECK(r.names().begin()->simple_name() == "bool");
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

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_other_object_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_other_object_property_has_expected_names_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::value_object);
    const auto m(mock_model_factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    dogen::sml_to_cpp::extractor x(m);
    bool found(false);
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child object: " << pair.first;
            BOOST_REQUIRE(pair.second->properties().size() == 1);
            const auto r(x.extract_dependency_graph(*pair.second));

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

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_missing_object_property_throws) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_missing_object_property_throws");

    const auto m(mock_model_factory::object_with_missing_property_type());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    dogen::sml_to_cpp::extractor x(m);
    const auto& p(*m.objects().begin()->second);

    using dogen::sml_to_cpp::extraction_error;
    contains_checker<extraction_error> c(object_not_found);
    BOOST_CHECK_EXCEPTION(x.extract_dependency_graph(p), extraction_error, c);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_pair_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_pair_property_has_expected_names_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::std_pair);
    const auto m(mock_model_factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    bool found(false);
    dogen::sml_to_cpp::extractor x(m);
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child object: " << pair.first;
            BOOST_REQUIRE(pair.second->properties().size() == 1);
            const auto r(x.extract_dependency_graph(*pair.second));
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
            found = true;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_variant_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_variant_property_has_expected_names_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::boost_variant);
    const auto m(mock_model_factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);
    BOOST_REQUIRE(m.primitives().size() == 2);

    bool found(false);
    dogen::sml_to_cpp::extractor x(m);
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << pair.first;
            BOOST_REQUIRE(pair.second->properties().size() == 1);
            const auto r(x.extract_dependency_graph(*pair.second));
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
            found = true;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_std_string_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_std_string_property_has_expected_name_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::std_string);
    const auto m(mock_model_factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    bool found(false);
    dogen::sml_to_cpp::extractor x(m);
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << pair.first;
            BOOST_REQUIRE(pair.second->properties().size() == 1);
            const auto r(x.extract_dependency_graph(*pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_CHECK(r.names().begin()->simple_name() == "string");
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(r.has_std_string());
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

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_boost_shared_ptr_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_boost_shared_ptr_property_has_expected_name_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::boost_shared_ptr);
    const auto m(mock_model_factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 3);

    bool found(false);
    dogen::sml_to_cpp::extractor x(m);
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << pair.first;
            BOOST_REQUIRE(pair.second->properties().size() == 1);

            found = true;
            const auto r(x.extract_dependency_graph(*pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_CHECK(r.forward_decls().size() == 1);
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(inheritance_graph_of_object_with_no_parents_has_one_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("inheritance_graph_of_object_with_no_parents_has_one_name_in_relationships");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 1);

    dogen::sml_to_cpp::extractor x(m);
    const auto r(
        x.extract_inheritance_graph(m.objects().begin()->second->name()));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_CHECK(r.names().size() == 1);
    BOOST_REQUIRE(is_type_zero(*r.names().begin()));

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

BOOST_AUTO_TEST_CASE(inheritance_graph_of_object_with_no_parents_and_one_property_has_one_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("inheritance_graph_of_object_with_no_parents_and_one_property_has_one_name_in_relationships");

    const auto m(mock_model_factory::object_with_property());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 2);

    dogen::sml_to_cpp::extractor x(m);
    std::array<bool, 2> found({{ false, false }});
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child object: " << pair.first;

            found[0] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_REQUIRE(is_type_zero(*r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_one(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[1] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_CHECK(r.names().size() == 1);
            BOOST_REQUIRE(is_type_one(*r.names().begin()));

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
    }
    BOOST_CHECK(found[0] && found[1]);
}

BOOST_AUTO_TEST_CASE(inheritance_graph_of_object_with_parent_has_two_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("inheritance_graph_of_object_with_parent_has_two_names_in_relationships");

    const auto m(mock_model_factory::object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 2);

    dogen::sml_to_cpp::extractor x(m);

    std::array<bool, 2> found({{ false, false }});
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child object: " << pair.first;

            found[0] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_REQUIRE(is_type_zero(*r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_one(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[1] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_CHECK(r.names().size() == 2);
            bool found_0(false), found_1(false);
            for (const auto n : r.names()) {
                found_0 = found_0 || is_type_zero(n);
                found_1 = found_1 || is_type_one(n);
            }
            BOOST_REQUIRE(found_0 && found_1);

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
    }
    BOOST_CHECK(found[0] && found[1]);
}

BOOST_AUTO_TEST_CASE(inheritance_graph_of_object_with_missing_parent_throws) {
    SETUP_TEST_LOG_SOURCE("inheritance_graph_of_object_with_missing_parent_throws");

    const auto m(
        mock_model_factory::object_with_missing_child_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 1);

    dogen::sml_to_cpp::extractor x(m);

    const auto qn(m.objects().begin()->second->name());
    using dogen::sml_to_cpp::extraction_error;
    contains_checker<extraction_error> c(object_not_found);
    BOOST_CHECK_EXCEPTION(x.extract_inheritance_graph(qn), extraction_error, c);
}

BOOST_AUTO_TEST_CASE(inheritance_graph_of_object_with_third_degree_children_has_four_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("inheritance_graph_of_object_with_third_degree_children_has_four_names_in_relationships");

    const auto m(
        mock_model_factory::object_with_third_degree_parent_in_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 4);

    dogen::sml_to_cpp::extractor x(m);

    std::array<bool, 4> found({{ false, false, false, false }});
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[0] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_REQUIRE(is_type_zero(*r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_one(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[1] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 2);
            bool found_0(false), found_1(false);
            for (const auto n : r.names()) {
                found_0 = found_0 || is_type_zero(n);
                found_1 = found_1 || is_type_one(n);
            }
            BOOST_REQUIRE(found_0 && found_1);

            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_two(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[2] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 3);
            bool found_0(false), found_1(false), found_2(false);
            for (const auto n : r.names()) {
                found_0 = found_0 || is_type_zero(n);
                found_1 = found_1 || is_type_one(n);
                found_2 = found_2 || is_type_two(n);
            }
            BOOST_REQUIRE(found_0 && found_1 && found_2);

            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_three(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[3] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 4);
            bool found_0(false), found_1(false), found_2(false), found_3(false);
            for (const auto n : r.names()) {
                found_0 = found_0 || is_type_zero(n);
                found_1 = found_1 || is_type_one(n);
                found_2 = found_2 || is_type_two(n);
                found_3 = found_3 || is_type_three(n);
            }
            BOOST_REQUIRE(found_0 && found_1 && found_2 && found_3);

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
    }
    BOOST_CHECK(found[0] && found[1] && found[2] && found[3]);
}

BOOST_AUTO_TEST_CASE(inheritance_graph_of_object_with_three_children_has_four_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("inheritance_graph_of_object_with_three_children_has_four_names_in_relationships");

    const auto m(
        mock_model_factory::object_with_three_children_in_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 4);

    dogen::sml_to_cpp::extractor x(m);

    std::array<bool, 4> found({{ false, false, false, false }});
    for (const auto pair : m.objects()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[0] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_REQUIRE(is_type_zero(*r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_one(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[1] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_REQUIRE(is_type_one(*r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_two(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[2] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_REQUIRE(is_type_two(*r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (is_type_three(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: " << pair.first;

            found[3] = true;
            const auto r(x.extract_inheritance_graph(pair.second->name()));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 4);
            bool found_0(false), found_1(false), found_2(false), found_3(false);
            for (const auto n : r.names()) {
                found_0 = found_0 || is_type_zero(n);
                found_1 = found_1 || is_type_one(n);
                found_2 = found_2 || is_type_two(n);
                found_3 = found_3 || is_type_three(n);
            }
            BOOST_REQUIRE(found_0 && found_1 && found_2 && found_3);

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
    }
    BOOST_CHECK(found[0] && found[1] && found[2] && found[3]);
}

BOOST_AUTO_TEST_SUITE_END()
