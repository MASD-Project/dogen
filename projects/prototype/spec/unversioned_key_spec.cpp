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
#include "dogen/utility/test/logging.hpp"
#include "dogen/prototype/domain/unversioned_key.hpp"
#include "dogen/prototype/serialization/unversioned_key_ser.hpp"
#include "dogen/prototype/hash/unversioned_key_hash.hpp"
#include "dogen/prototype/test_data/unversioned_key_td.hpp"
#include "dogen/utility/test/serialization_tester.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/utility/test/hash_tester.hpp"
#include "dogen/utility/test/construction.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/prototype/io/unversioned_key_io.hpp"
#include "dogen/prototype/serialization/unversioned_key_ser.hpp"

namespace  {

const std::string test_module("prototype");
const std::string test_suite("unversioned_key_spec");

}

BOOST_AUTO_TEST_SUITE(unversioned_key)

BOOST_AUTO_TEST_CASE(roundtrips_of_the_same_type_produce_the_same_entity) {
    SETUP_TEST_LOG("roundtrips_of_the_same_type_produce_the_same_entity");
    dogen::prototype::unversioned_key_sequence sequence;
    const dogen::prototype::unversioned_key a(sequence());;
    dogen::utility::test::serialization_tester<dogen::prototype::unversioned_key>::
        roundtrips_of_the_same_type_produce_the_same_entity(a);
}

BOOST_AUTO_TEST_CASE(assigning_an_object_to_itself_results_in_the_same_object) {
    SETUP_TEST_LOG("assigning_an_object_to_itself_results_in_the_same_object");
    dogen::utility::test::construction<
        dogen::prototype::unversioned_key,
        dogen::prototype::unversioned_key_sequence>::
        assigning_an_object_to_itself_results_in_the_same_object();
}

BOOST_AUTO_TEST_CASE(default_constructed_object_has_all_properties_initialised) {
    SETUP_TEST_LOG_SOURCE("default_constructed_object_has_all_properties_initialised");
    dogen::prototype::unversioned_key a;
    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
    BOOST_CHECK(!a.id());
}

BOOST_AUTO_TEST_CASE(complete_constructed_object_matches_properties_set_object) {
    SETUP_TEST_LOG_SOURCE("complete_constructed_object_matches_properties_set_object");
    dogen::prototype::unversioned_key_sequence sequence;
    const dogen::prototype::unversioned_key a(sequence());
    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);

    dogen::prototype::unversioned_key b;
    b.id(a.id());
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
    BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(objects_with_only_one_field_different_are_unequal) {
    SETUP_TEST_LOG_SOURCE("objects_with_only_one_field_different_are_unequal");
    dogen::prototype::unversioned_key_sequence sequence;
    using dogen::prototype::unversioned_key;
    const unversioned_key a(sequence());
    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);

    unversioned_key b(a);
    b.id(999);
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
    BOOST_CHECK(a != b && !(a == b));
}

BOOST_AUTO_TEST_CASE(objects_with_same_state_but_different_ids_are_unequal) {
    SETUP_TEST_LOG("objects_with_same_state_but_different_ids_are_unequal");
    BOOST_CHECK(true); // test doesn't apply to version.
}

BOOST_AUTO_TEST_CASE(identical_objects_are_equal) {
    SETUP_TEST_LOG("identical_objects_are_equal");
    dogen::prototype::unversioned_key_sequence sequence;
    const dogen::prototype::unversioned_key a(sequence());
    const dogen::prototype::unversioned_key b(a);

    dogen::utility::test::equality_tester<
        dogen::prototype::unversioned_key>::identical_objects_are_equal(a, b);
}

BOOST_AUTO_TEST_CASE(an_object_is_equal_to_itself) {
    SETUP_TEST_LOG("an_object_is_equal_to_itself");
    dogen::prototype::unversioned_key_sequence sequence;
    const dogen::prototype::unversioned_key a(sequence());

    dogen::utility::test::equality_tester<
        dogen::prototype::unversioned_key>::an_object_is_equal_to_itself(a);
}

BOOST_AUTO_TEST_CASE(distinct_objects_are_unequal) {
    SETUP_TEST_LOG("distinct_objects_are_unequal");
    dogen::prototype::unversioned_key_sequence sequence;
    const dogen::prototype::unversioned_key a(sequence());
    const dogen::prototype::unversioned_key b(sequence());

    dogen::utility::test::equality_tester<
        dogen::prototype::unversioned_key>::distinct_objects_are_unequal(a, b);
}

BOOST_AUTO_TEST_CASE(equal_objects_must_generate_the_same_hash) {
    SETUP_TEST_LOG("equal_objects_must_generate_the_same_hash");
    dogen::utility::test::hash_tester<
        dogen::prototype::unversioned_key_sequence>::
        equal_objects_must_generate_the_same_hash();
}

BOOST_AUTO_TEST_CASE(unequal_objects_must_generate_different_hashes) {
    SETUP_TEST_LOG("unequal_objects_must_generate_different_hashes");
    dogen::utility::test::hash_tester<
        dogen::prototype::unversioned_key_sequence>::
        unequal_objects_must_generate_different_hashes();
}

BOOST_AUTO_TEST_SUITE_END()
