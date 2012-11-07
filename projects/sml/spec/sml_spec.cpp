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
#include "dogen/sml/serialization/registrar_ser.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/sml/domain/sml_domain.hpp"
#include "dogen/sml/io/sml_io.hpp"
#include "dogen/sml/serialization/sml_ser.hpp"
#include "dogen/sml/test_data/sml_test_data.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::sml::register_types<Archive>(ar);
}

namespace {

const std::string test_module("sml");
const std::string test_suite("sml_spec");

const std::string documentation("@brief sample doc");

/**
 * @brief Performs a serialisation round-trip using a test object
 * read from Sequence.
 */
template<typename Sequence>
void rountrip_type() {
    Sequence sequence;
    dogen::utility::test::serialization_tester<typename Sequence::result_type>::
        all_roundtrips_produce_the_same_entity(sequence());
}

template<typename Sequence>
void test_equality() {
    Sequence sequence;
    const typename Sequence::result_type a(sequence());
    const typename Sequence::result_type b(a);
    const typename Sequence::result_type c(sequence());

    typedef dogen::utility::test::equality_tester
        <typename Sequence::result_type> equality_tester;
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
