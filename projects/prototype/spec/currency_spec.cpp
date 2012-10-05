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
#include "dogen/config/version.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/prototype/test_data/currency_td.hpp"
#include "dogen/prototype/serialization/currency_ser.hpp"
#include "dogen/prototype/io/currency_io.hpp"
#include "dogen/prototype/io/versioned_key_io.hpp"
#include "dogen/prototype/io/unversioned_key_io.hpp"
#include "dogen/prototype/domain/currency.hpp"
#include "dogen/prototype/hash/currency_hash.hpp"
#include "dogen/prototype/database/currency_db.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/utility/test/serialization_tester.hpp"
#include "dogen/utility/test/hash_tester.hpp"
#include "dogen/utility/test/construction.hpp"
#include "dogen/utility/test/less_than.hpp"
#include "dogen/utility/test/database_spec.hpp"
#include "dogen/utility/io/jsonify_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/prototype/io/currency_io.hpp"

namespace  {

const std::string test_module("prototype");
const std::string test_suite("currency_spec");

}

BOOST_AUTO_TEST_SUITE(currency)

BOOST_AUTO_TEST_CASE(roundtrips_of_the_same_type_produce_the_same_entity) {
    SETUP_TEST_LOG("roundtrips_of_the_same_type_produce_the_same_entity");
    dogen::prototype::majors_currency_sequence sequence;
    using dogen::prototype::currency;
    const currency a(sequence());

    dogen::utility::test::serialization_tester<dogen::prototype::currency>::
        roundtrips_of_the_same_type_produce_the_same_entity(a);
}

BOOST_AUTO_TEST_CASE(equal_objects_must_generate_the_same_hash) {
    SETUP_TEST_LOG("equal_objects_must_generate_the_same_hash");
    dogen::utility::test::hash_tester<
        dogen::prototype::majors_currency_sequence>::
        equal_objects_must_generate_the_same_hash();
}

BOOST_AUTO_TEST_CASE(unequal_objects_must_generate_different_hashes) {
    SETUP_TEST_LOG("unequal_objects_must_generate_different_hashes");
    dogen::utility::test::hash_tester<
        dogen::prototype::majors_currency_sequence>::
        unequal_objects_must_generate_different_hashes();
}

BOOST_AUTO_TEST_CASE(objects_with_only_one_field_different_are_unequal) {
    SETUP_TEST_LOG_SOURCE("objects_with_only_one_field_different_are_unequal");
    dogen::prototype::majors_currency_sequence sequence;
    using dogen::prototype::currency;
    const currency a(sequence());

    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);

    currency b(a);
    b.name("test");
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
    BOOST_CHECK(a != b && !(a == b));

    b = a;
    b.alpha_code("AAA");
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
    BOOST_CHECK(a != b && !(a == b));

    b = a;
    b.decimal_places(15);
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
    BOOST_CHECK(a != b && !(a == b));

    b = a;
    using dogen::prototype::versioned_key;
    b.versioned_key(versioned_key(1, 0));
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
    BOOST_CHECK(a != b && !(a == b));
}

BOOST_AUTO_TEST_CASE(objects_with_same_state_but_different_ids_are_unequal) {
    SETUP_TEST_LOG_SOURCE("objects_with_same_state_but_different_ids_are_unequal");
    dogen::prototype::majors_currency_sequence sequence;
    using dogen::prototype::currency;
    const currency a(sequence());
    currency b(a);

    using dogen::prototype::versioned_key;
    const auto avk(a.versioned_key());
    const versioned_key bvk(avk.id() + 100, avk.version());
    b.versioned_key(bvk);

    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);

    BOOST_CHECK(a.versioned_key() != b.versioned_key());
    BOOST_CHECK(a != b);
    BOOST_CHECK(a.is_equivalent(b));
}

BOOST_AUTO_TEST_CASE(identical_objects_are_equal) {
    SETUP_TEST_LOG("identical_objects_are_equal");
    dogen::prototype::majors_currency_sequence sequence;
    const dogen::prototype::currency a(sequence());
    const dogen::prototype::currency b(a);

    dogen::utility::test::equality_tester<
        dogen::prototype::currency>::identical_objects_are_equal(a, b);
}

BOOST_AUTO_TEST_CASE(an_object_is_equal_to_itself) {
    SETUP_TEST_LOG("an_object_is_equal_to_itself");
    dogen::prototype::majors_currency_sequence sequence;
    const dogen::prototype::currency a(sequence());

    dogen::utility::test::equality_tester<
        dogen::prototype::currency>::an_object_is_equal_to_itself(a);
}

BOOST_AUTO_TEST_CASE(distinct_objects_are_unequal) {
    SETUP_TEST_LOG("distinct_objects_are_unequal");
    dogen::prototype::majors_currency_sequence sequence;
    const dogen::prototype::currency a(sequence());
    const dogen::prototype::currency b(sequence());

    dogen::utility::test::equality_tester<
        dogen::prototype::currency>::distinct_objects_are_unequal(a, b);
}

BOOST_AUTO_TEST_CASE(equal_objects_are_not_smaller_or_greater_than_each_other) {
    SETUP_TEST_LOG("equal_objects_are_not_smaller_or_greater_than_each_other");
    dogen::utility::test::less_than<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence>::
        equal_objects_are_not_smaller_or_greater_than_each_other();
}

BOOST_AUTO_TEST_CASE(unequal_objects_are_not_both_smaller_and_greater_than_each_other) {
    SETUP_TEST_LOG("unequal_objects_are_not_both_smaller_and_greater_than_each_other");
    dogen::utility::test::less_than<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence>::
        unequal_objects_are_not_both_smaller_and_greater_than_each_other();
}

BOOST_AUTO_TEST_CASE(assigning_an_object_to_itself_results_in_the_same_object) {
    SETUP_TEST_LOG("assigning_an_object_to_itself_results_in_the_same_object");
    dogen::utility::test::construction<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence>::
        assigning_an_object_to_itself_results_in_the_same_object();
}

BOOST_AUTO_TEST_CASE(default_constructor_initialises_all_properties) {
    SETUP_TEST_LOG_SOURCE("default_constructor_initialises_all_properties");
    dogen::prototype::currency a;

    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);

    BOOST_CHECK(a.name().empty());
    BOOST_CHECK(a.alpha_code().empty());
    BOOST_CHECK(a.decimal_places() == 0);
    BOOST_CHECK(a.versioned_key() == dogen::prototype::versioned_key());
}

BOOST_AUTO_TEST_CASE(complete_constructor_initialises_all_properties) {
    SETUP_TEST_LOG_SOURCE("complete_constructor_initialises_all_properties");
    dogen::prototype::majors_currency_sequence sequence;
    const dogen::prototype::currency a(sequence());

    dogen::prototype::currency b;
    b.name(a.name());
    b.numeric_code(a.numeric_code());
    b.alpha_code(a.alpha_code());
    b.decimal_places(a.decimal_places());
    b.versioned_key(a.versioned_key());

    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
    BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(saving_zero_entities_shall_do_nothing) {
    SETUP_TEST_LOG("complete_constructor_initialises_all_properties");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::saving_zero_entities_shall_do_nothing();
}

BOOST_AUTO_TEST_CASE(saving_one_entity_shall_increment_revision) {
    SETUP_TEST_LOG("saving_one_entity_shall_increment_revision");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::saving_one_entity_shall_increment_revision();
}

BOOST_AUTO_TEST_CASE(saving_n_entities_shall_increment_revision) {
    SETUP_TEST_LOG("saving_n_entities_shall_increment_revision");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::saving_n_entities_shall_increment_revision();
}

BOOST_AUTO_TEST_CASE(saving_with_wrong_version_shall_fail) {
    SETUP_TEST_LOG("saving_with_wrong_version_shall_fail");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::saving_with_wrong_version_shall_fail();
}

BOOST_AUTO_TEST_CASE(loading_by_existing_key_shall_load_one_entity) {
    SETUP_TEST_LOG("loading_by_existing_key_shall_load_one_entity");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::loading_by_existing_key_shall_load_one_entity();
}

BOOST_AUTO_TEST_CASE(loading_by_non_existing_key_shall_load_zero_entities) {
    SETUP_TEST_LOG("loading_by_non_existing_key_shall_load_zero_entities");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::loading_by_non_existing_key_shall_load_zero_entities();
}

BOOST_AUTO_TEST_CASE(loading_all_when_none_exist_shall_load_zero_entities) {
    SETUP_TEST_LOG("loading_all_when_none_exist_shall_load_zero_entities");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::loading_all_when_none_exist_shall_load_zero_entities();
}

BOOST_AUTO_TEST_CASE(erasing_all_when_none_exist_shall_do_nothing) {
    SETUP_TEST_LOG("erasing_all_when_none_exist_shall_do_nothing");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::erasing_all_when_none_exist_shall_do_nothing();
}

BOOST_AUTO_TEST_CASE(roundtrip_shall_produce_equal_entities) {
    SETUP_TEST_LOG("roundtrip_shall_produce_equal_entities");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::roundtrip_shall_produce_equal_entities();
}

BOOST_AUTO_TEST_CASE(loading_entity_by_key_shall_be_supported) {
    SETUP_TEST_LOG("loading_entity_by_key_shall_be_supported");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::loading_entity_by_key_shall_be_supported();
}

BOOST_AUTO_TEST_CASE(erasing_entity_by_key_shall_be_supported) {
    SETUP_TEST_LOG("erasing_entity_by_key_shall_be_supported");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::erasing_entity_by_key_shall_be_supported();
}

BOOST_AUTO_TEST_CASE(erasing_all_entities_shall_be_supported) {
    SETUP_TEST_LOG("erasing_all_entities_shall_be_supported");
    dogen::utility::test::database<
        dogen::prototype::currency,
        dogen::prototype::majors_currency_sequence,
        dogen::prototype::currency_data_exchanger
        >::erasing_all_entities_shall_be_supported();
}

BOOST_AUTO_TEST_SUITE_END()
