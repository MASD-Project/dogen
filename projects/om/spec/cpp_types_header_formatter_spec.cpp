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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/tag_router.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/property_cache_interface.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/abstract_object_io.hpp"
#include "dogen/sml/io/enumeration_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/om/types/cpp_types_header_formatter.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string test_module("om");
const std::string test_suite("cpp_types_header_formatter_spec");
const std::string empty_marker;
const dogen::om::licence empty_licence = dogen::om::licence();
const dogen::om::modeline empty_modeline = dogen::om::modeline();
const boost::filesystem::path empty_path;
const boost::filesystem::path non_empty_path("a/file.hpp");

const std::string enumeration_two_enumerators(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
enum class some_type_0 : unsigned int {
    some_type_0 = 0, ///< Some documentation
    some_type_1 = 1 ///< Some documentation
};

}
)");

const std::string object_no_properties(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_0 final {
};

}
)");

const std::string parent_object(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_1 {
};

}
)");

const std::string leaf_child_object(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_0 final : public some_type_1 {
};

}
)");

const std::string non_leaf_child_object(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_1 : public some_type_2 {
};

}
)");

const std::string all_explicitly_defaulted_functions(R"(namespace some_model_0 {

class some_type_0 final {
public:
    some_type_0() = default;
    some_type_0(const some_type_0&) = default;
    some_type_0(some_type_0&&) = default;
    ~some_type_0() = default;
    some_type_0& operator=(const some_type_0&) = default;
};

}
)");

const std::string manual_default_constructor(R"(namespace some_model_0 {

class some_type_0 final {
public:
    some_type_0(const some_type_0&) = default;
    some_type_0(some_type_0&&) = default;
    ~some_type_0() = default;
    some_type_0& operator=(const some_type_0&) = default;

public:
    some_type_0();
};

}
)");

const std::string manual_move_constructor(R"(namespace some_model_0 {

class some_type_0 final {
public:
    some_type_0() = default;
    some_type_0(const some_type_0&) = default;
    ~some_type_0() = default;
    some_type_0& operator=(const some_type_0&) = default;
};

}
)");

/*
  FIXME: remvoed for now
  public:
  some_type_0(some_type_0&&);
 */

class mock_property_cache : public dogen::sml::property_cache_interface {
public:
    mock_property_cache() = default;
    mock_property_cache(const mock_property_cache&) = default;
    mock_property_cache(mock_property_cache&&) = default;
    mock_property_cache& operator=(const mock_property_cache&) = default;

public:
    std::list<dogen::sml::property>
    get_all_properties(const dogen::sml::abstract_object&) const override {
        return std::list<dogen::sml::property> {};
    }

    std::list<dogen::sml::property>
    get_local_properties(const dogen::sml::abstract_object&) const override {
        return std::list<dogen::sml::property> {};
    }

    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >
    get_inehrited_properties(const dogen::sml::abstract_object&) const override {
        return std::unordered_map<dogen::sml::qname,
                                  std::list<dogen::sml::property> > {};
    }
};

const std::string element_not_found("element not found: ");

const dogen::sml::abstract_object&
find_object(const dogen::sml::model& m, const unsigned int n) {
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (mock_model_factory::simple_name(n) == qn.simple_name())
            return *pair.second;
    }

    BOOST_THROW_EXCEPTION(
        dogen::utility::exception::exception(element_not_found +
            boost::lexical_cast<std::string>(n)));
}

dogen::sml::abstract_object&
find_object(dogen::sml::model& m, const unsigned int n) {
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (mock_model_factory::simple_name(n) == qn.simple_name())
            return *pair.second;
    }

    BOOST_THROW_EXCEPTION(
        dogen::utility::exception::exception(element_not_found +
            boost::lexical_cast<std::string>(n)));
}

}

using namespace dogen::om;
using namespace dogen::utility::test;
typedef dogen::sml::test::mock_model_factory::object_types object_types;
typedef dogen::sml::test::mock_model_factory::property_types property_types;
typedef dogen::sml::test::mock_model_factory factory;

BOOST_AUTO_TEST_SUITE(cpp_types_header_formatter)

BOOST_AUTO_TEST_CASE(enumeration_with_two_enumerators_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("enumeration_with_two_enumerators_produces_expected_types_header");

    const auto ot(object_types::enumeration);
    const auto m(factory::build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    std::ostringstream s;
    dogen::om::cpp_types_header_formatter f;
    mock_property_cache c;
    const auto e(m.enumerations().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "enumeration: " << e;

    f.format(s, e, empty_licence, empty_modeline, empty_marker, c);
    const auto r(s.str());
    BOOST_CHECK(r == enumeration_two_enumerators);
    BOOST_LOG_SEV(lg, debug) << "expected: " << enumeration_two_enumerators
                             << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r << "<end>";
}

BOOST_AUTO_TEST_CASE(object_with_no_properties_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("object_with_no_properties_produces_expected_types_header");

    const auto m(factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    std::ostringstream s;
    dogen::om::cpp_types_header_formatter f;
    mock_property_cache c;
    const auto& o(find_object(m, 0));
    BOOST_LOG_SEV(lg, debug) << "object: " << o;

    f.format(s, o, empty_licence, empty_modeline, empty_marker, c);
    const auto r(s.str());
    BOOST_CHECK(r == object_no_properties);
    BOOST_LOG_SEV(lg, debug) << "expected: " << object_no_properties << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r << "<end>";
}

BOOST_AUTO_TEST_CASE(parent_object_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("parent_object_produces_expected_types_header");

    const auto m(mock_model_factory::object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.objects().size() == 2);

    const auto& o(find_object(m, 1));
    BOOST_LOG_SEV(lg, debug) << "object: " << o;

    std::ostringstream s;
    dogen::om::cpp_types_header_formatter f;
    mock_property_cache c;
    f.format(s, o, empty_licence, empty_modeline, empty_marker, c);
    const auto r(s.str());
    BOOST_CHECK(r == parent_object);
    BOOST_LOG_SEV(lg, debug) << "expected: " << parent_object << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r << "<end>";
}

BOOST_AUTO_TEST_CASE(leaf_child_object_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("leaf_child_object_produces_expected_types_header");

    const auto m(mock_model_factory::object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 2);

    const auto& o(find_object(m, 0));
    BOOST_LOG_SEV(lg, debug) << "object: " << o;

    std::ostringstream s;
    dogen::om::cpp_types_header_formatter f;
    mock_property_cache c;

    f.format(s, o, empty_licence, empty_modeline, empty_marker, c);
    const auto r(s.str());
    BOOST_CHECK(r == leaf_child_object);
    BOOST_LOG_SEV(lg, debug) << "expected: " << leaf_child_object << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r << "<end>";
}

BOOST_AUTO_TEST_CASE(non_leaf_child_object_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("non_leaf_child_object_produces_expected_types_header");

    const auto m(mock_model_factory::
        object_with_third_degree_parent_in_same_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.objects().size() == 4);

    const auto& o(find_object(m, 1));
    BOOST_LOG_SEV(lg, debug) << "object: " << o;

    std::ostringstream s;
    dogen::om::cpp_types_header_formatter f;
    mock_property_cache c;

    f.format(s, o, empty_licence, empty_modeline, empty_marker, c);
    const auto r(s.str());
    BOOST_CHECK(r == non_leaf_child_object);
    BOOST_LOG_SEV(lg, debug) << "expected: " << non_leaf_child_object << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r << "<end>";
}

BOOST_AUTO_TEST_CASE(generating_explicitly_defaulted_functions_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("generating_explicitly_defaulted_functions_produces_expected_types_header");

    auto m(factory::build_single_type_model());
    BOOST_CHECK(m.objects().size() == 1);
    auto& o(find_object(m, 0));
    o.documentation().clear();
    auto router(dogen::sml::make_tag_router(o));
    router.route(
        dogen::sml::tags::cpp::types::generate_defaulted_functions,
        dogen::sml::tags::bool_true);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    std::ostringstream s;
    dogen::om::cpp_types_header_formatter f;
    mock_property_cache c;

    f.format(s, o, empty_licence, empty_modeline, empty_marker, c);
    const auto r(s.str());
    BOOST_CHECK(r == all_explicitly_defaulted_functions);
    BOOST_LOG_SEV(lg, debug) << "expected: "
                             << all_explicitly_defaulted_functions << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r << "<end>";
}

BOOST_AUTO_TEST_CASE(generating_manual_default_constructor_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("generating_manual_default_constructor_produces_expected_types_header");

    auto m(factory::build_single_type_model());
    BOOST_CHECK(m.objects().size() == 1);
    auto& o(find_object(m, 0));
    o.documentation().clear();
    auto router(dogen::sml::make_tag_router(o));
    router.route(
        dogen::sml::tags::cpp::types::generate_defaulted_functions,
        dogen::sml::tags::bool_true);
    router.route(
        dogen::sml::tags::cpp::types::generate_explicit_default_constructor,
        dogen::sml::tags::bool_true);

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    std::ostringstream s;
    dogen::om::cpp_types_header_formatter f;
    mock_property_cache c;

    f.format(s, o, empty_licence, empty_modeline, empty_marker, c);
    const auto r(s.str());
    BOOST_CHECK(r == manual_default_constructor);
    BOOST_LOG_SEV(lg, debug) << "expected: "
                             << manual_default_constructor << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r << "<end>";
}

BOOST_AUTO_TEST_CASE(generating_manual_move_constructor_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("generating_manual_move_constructor_produces_expected_types_header");

    auto m(factory::build_single_type_model());
    BOOST_CHECK(m.objects().size() == 1);
    auto& o(find_object(m, 0));
    o.documentation().clear();
    auto router(dogen::sml::make_tag_router(o));
    router.route(
        dogen::sml::tags::cpp::types::generate_defaulted_functions,
        dogen::sml::tags::bool_true);
    router.route(
        dogen::sml::tags::cpp::types::generate_explicit_move_constructor,
        dogen::sml::tags::bool_true);

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    std::ostringstream s;
    dogen::om::cpp_types_header_formatter f;
    mock_property_cache c;

    f.format(s, o, empty_licence, empty_modeline, empty_marker, c);
    const auto r(s.str());
    BOOST_CHECK(r == manual_move_constructor);
    BOOST_LOG_SEV(lg, debug) << "expected: "
                             << manual_move_constructor << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r << "<end>";
}

BOOST_AUTO_TEST_SUITE_END()
