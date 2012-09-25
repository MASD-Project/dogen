/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE sml_spec
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/test/included/unit_test.hpp>
#include "dogen/utility/test/hash_tester.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/domain/sml_domain.hpp"
#include "dogen/sml/io/sml_io.hpp"
#include "dogen/sml/test_data/qualified_name_sequence.hpp"
#include "dogen/sml/hash/qualified_name_hash.hpp"
#include "dogen/utility/test/serialization_tester.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/sml/domain/sml_domain.hpp"
#include "dogen/sml/io/sml_io.hpp"
#include "dogen/sml/serialization/sml_ser.hpp"
#include "dogen/sml/test_data/sml_test_data.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("sml_spec");

/**
 * @brief Performs a serialisation round-trip using a test object
 * read from Sequence.
 */
template<typename Sequence>
void rountrip_type() {
    Sequence sequence;
    dogen::utility::test::serialization_tester<typename Sequence::value_type>::
        all_roundtrips_produce_the_same_entity(sequence());
}

template<typename Sequence>
void test_equality() {
    Sequence sequence;
    const typename Sequence::value_type a(sequence());
    const typename Sequence::value_type b(a);
    const typename Sequence::value_type c(sequence());

    typedef dogen::utility::test::equality_tester
        <typename Sequence::value_type> equality_tester;
    equality_tester::an_object_is_equal_to_itself(a);
    equality_tester::identical_objects_are_equal(a, b);
    equality_tester::distinct_objects_are_unequal(a, c);
}

template<typename Sequence>
void test_hashing() {
    dogen::utility::test::hash_tester<Sequence>::
        equal_objects_must_generate_the_same_hash();

    dogen::utility::test::hash_tester<Sequence>::
        unequal_objects_must_generate_different_hashes();
}

}

BOOST_AUTO_TEST_SUITE(sml)

BOOST_AUTO_TEST_CASE(exercise_meta_type_io) {
    SETUP_TEST_LOG_SOURCE("exercise_meta_type_io");
    BOOST_LOG_SEV(lg, info) << dogen::sml::meta_types::invalid;
    BOOST_LOG_SEV(lg, info) << dogen::sml::meta_types::pod;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(exercise_type_and_descendants_io) {
    SETUP_TEST_LOG_SOURCE("exercise_type_and_descendants_io");
    std::list<std::string> external_package_path;
    external_package_path.push_back("external_1");

    std::list<std::string> package_path;
    package_path.push_back("package_1");
    package_path.push_back("package_2");

    dogen::sml::qualified_name
        child_type_name("some_model", external_package_path,
            package_path, "child_pod", dogen::sml::meta_types::pod);

    boost::optional<dogen::sml::qualified_name> parent_type_name(
        dogen::sml::qualified_name("some_model",external_package_path,
            package_path, "parent_pod", dogen::sml::meta_types::pod));

    const std::vector<dogen::sml::property> p;
    const bool generate(true);

    dogen::sml::pod pod(child_type_name, p, parent_type_name, generate);
    BOOST_LOG_SEV(lg, info) << pod;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(exercise_qualified_name_and_property_io) {
    SETUP_TEST_LOG_SOURCE("exercise_qualified_name_and_property_io");
    std::list<std::string> external_package_path;
    external_package_path.push_back("0");

    std::list<std::string> package_path;
    package_path.push_back("1");
    package_path.push_back("2");

    dogen::sml::qualified_name qualified_name(
        "model_name", external_package_path, package_path,
        "type_name", dogen::sml::meta_types::invalid);

    BOOST_LOG_SEV(lg, info) << qualified_name;

    dogen::sml::property
        property("property_name", qualified_name, "property_default_value");
    BOOST_LOG_SEV(lg, info) << property;
}

BOOST_AUTO_TEST_CASE(validate_qualified_name_hashing) {
    SETUP_TEST_LOG("validate_qualified_name_hashing");
    test_hashing<dogen::sml::test_data::qualified_name_sequence>();
}

BOOST_AUTO_TEST_CASE(equality_operator_behaves_correctly) {
    SETUP_TEST_LOG("equality_operator_behaves_correctly");
    using namespace dogen::sml::test_data;

    test_equality<meta_types_sequence>();
    test_equality<qualified_name_sequence>();
    test_equality<property_sequence>();
    test_equality<pod_sequence>();
    test_equality<package_sequence>();
    test_equality<model_sequence>();
}

BOOST_AUTO_TEST_CASE(roundtrips_of_the_same_type_produce_the_same_entity) {
    SETUP_TEST_LOG("roundtrips_of_the_same_type_produce_the_same_entity");
    using namespace dogen::sml::test_data;

    rountrip_type<meta_types_sequence>();
    rountrip_type<qualified_name_sequence>();
    rountrip_type<property_sequence>();
    rountrip_type<pod_sequence>();
    rountrip_type<package_sequence>();
    rountrip_type<model_sequence>();
}

BOOST_AUTO_TEST_SUITE_END()
