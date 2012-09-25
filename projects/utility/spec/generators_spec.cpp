/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <functional>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test_data/xml_reader.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/test_data/test_data.hpp"
#include "dogen/utility/test_data/generate_container.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/utility/io/vector_io.hpp"

namespace {

const std::string test_module("utility");
const std::string test_suite("generators_spec");

const std::string non_existent_file_name("non_existent_file");

typedef dogen::utility::test_data::generator<int> int_generator;

/**
 * @brief Generator with a fixed number of terms.
 */
class finite_generator : public int_generator {
public:
    finite_generator() : int_generator(100) { }
    value_type next_term(const unsigned int position) { return (position); }
};

typedef dogen::utility::test_data::sequence<finite_generator> finite_sequence;

/**
 * @brief Generator for which there is always a next term.
 */
class infinite_generator : public int_generator {
public:
    infinite_generator() : int_generator(0) { }
    value_type next_term(const unsigned int position) { return (position); }
};

typedef dogen::utility::test_data::sequence<
    infinite_generator>
infinite_sequence;

}

BOOST_AUTO_TEST_SUITE(generators)

/**
 * @brief It shall be possible to create all terms of a finite
 * sequence using std::generate_n.
 */
BOOST_AUTO_TEST_CASE(generate_n_can_create_all_terms_in_a_finite_sequence) {
    SETUP_TEST_LOG_SOURCE("generate_n_can_create_all_terms_in_a_finite_sequence");
    std::vector<finite_sequence::value_type> terms;
    finite_sequence sequence;

    terms.reserve(sequence.length());
    std::generate_n(std::back_inserter(terms), sequence.length(), sequence);

    BOOST_CHECK(terms.size() == sequence.length());
    BOOST_LOG_SEV(lg, info) << "terms: " << terms;
}

/**
 * @brief It shall be possible to create n terms of a finite
 * sequence using std::generate_n, where n is smaller than the
 * number of terms in the sequence.
 */
BOOST_AUTO_TEST_CASE(generate_n_can_create_subset_of_terms_in_finite_sequence) {
    SETUP_TEST_LOG_SOURCE("generate_n_can_create_all_terms_in_a_finite_sequence");
    finite_sequence sequence;
    const unsigned int half_size(sequence.length() / 2);

    std::vector<finite_sequence::value_type> terms;
    terms.reserve(half_size);
    std::generate_n(std::back_inserter(terms), half_size, sequence);

    BOOST_CHECK(terms.size() == half_size);
    BOOST_LOG_SEV(lg, info) << "terms: " << terms;
}

/**
 * @brief It shall be possible to create n terms of an infinite
 * sequence using std::generate_n.
 */
BOOST_AUTO_TEST_CASE(generate_n_can_create_subset_of_terms_in_infinite_sequence) {
    SETUP_TEST_LOG_SOURCE("generate_n_can_create_subset_of_terms_in_infinite_sequence");
    infinite_sequence sequence;
    const unsigned int size(10);

    std::vector<infinite_sequence::value_type> terms;
    terms.reserve(size);
    std::generate_n(std::back_inserter(terms), size, sequence);

    BOOST_CHECK(terms.size() == size);
    BOOST_LOG_SEV(lg, info) << "terms: " << terms;
}

/**
 * @brief It shall not be possible to create more terms than those
 * supported by a finite sequence, using std::generate_n.
 */
BOOST_AUTO_TEST_CASE(generate_n_cannot_create_more_terms_than_sequence_length) {
    SETUP_TEST_LOG_SOURCE("generate_n_cannot_create_more_terms_than_sequence_length");
    finite_sequence sequence;
    const unsigned int beyond_end(sequence.length() + 1);

    std::vector<finite_sequence::value_type> terms;
    terms.reserve(beyond_end);
    try {
        std::generate_n(std::back_inserter(terms), beyond_end, sequence);
        BOOST_FAIL("Expected sequence_exhausted exception to be thrown.");
    } catch (const dogen::utility::test_data::sequence_exhausted& e) {
        BOOST_LOG_SEV(lg, info) << "Exception thrown as expected: " << e.what();
        BOOST_CHECK(true);
    }
}

/**
 * @brief It shall possible to create all terms in a finite
 * sequence using generate_vector.
 */
BOOST_AUTO_TEST_CASE(generate_vector_can_create_all_terms_in_finite_sequence) {
    SETUP_TEST_LOG_SOURCE("generate_vector_can_create_all_terms_in_finite_sequence");
    using dogen::utility::test_data::generate_vector;
    finite_sequence sequence;
    std::vector<finite_sequence::value_type>
        terms(generate_vector<finite_sequence>());
    BOOST_CHECK(terms.size() == sequence.length());
    BOOST_LOG_SEV(lg, info) << "terms: " << terms;
}

/**
 * @brief It shall possible to create all terms in a finite
 * sequence using generate_vector.
 */
BOOST_AUTO_TEST_CASE(generate_vector_can_create_subset_of_terms_in_finite_sequence) {
    SETUP_TEST_LOG_SOURCE("generate_vector_can_create_subset_of_terms_in_finite_sequence");
    finite_sequence sequence;
    const unsigned int half_size(sequence.length() / 2);

    using dogen::utility::test_data::generate_vector;
    std::vector<finite_sequence::value_type>
        terms(generate_vector<finite_sequence>(half_size));
    BOOST_CHECK(terms.size() == half_size);
    BOOST_LOG_SEV(lg, info) << "terms: " << terms;
}

/**
 * @brief It shall not be possible to create more terms than those
 * supported by a finite sequence, using std::generate_n.
 */
BOOST_AUTO_TEST_CASE(generate_vector_can_create_subset_of_terms_in_infinite_sequence) {
    SETUP_TEST_LOG_SOURCE("generate_vector_can_create_subset_of_terms_in_finite_sequence");
    infinite_sequence sequence;
    const unsigned int size(10);

    using dogen::utility::test_data::generate_vector;
    std::vector<infinite_sequence::value_type>
        terms(generate_vector<infinite_sequence>(size));
    BOOST_CHECK(terms.size() == size);
    BOOST_LOG_SEV(lg, info) << "terms: " << terms;
}

/**
 * @brief It shall not be possible to create more terms than those
 * supported by a finite sequence, using std::generate_n.
 */
BOOST_AUTO_TEST_CASE(generate_vector_cannot_create_more_terms_than_sequence_length) {
    SETUP_TEST_LOG_SOURCE("generate_vector_can_create_subset_of_terms_in_finite_sequence");
    finite_sequence sequence;
    const unsigned int beyond_end(sequence.length() + 1);

    try {
        using dogen::utility::test_data::generate_vector;
        std::vector<infinite_sequence::value_type>
            terms(generate_vector<finite_sequence>(beyond_end));
        BOOST_FAIL("Expected container_generation_error exception.");
    } catch (const dogen::utility::test_data::container_generation_error& e) {
        BOOST_LOG_SEV(lg, info) << "Exception thrown as expected: " << e.what();
        BOOST_CHECK(true);
    }
}

/**
 * @brief It shall not be possible to create more terms than those
 * supported by a finite sequence, using std::generate_n.
 */
BOOST_AUTO_TEST_CASE(generate_vector_throws_when_generating_all_terms_for_infinite_sequence) {
    SETUP_TEST_LOG_SOURCE("generate_vector_throws_when_generating_all_terms_for_infinite_sequence");
    infinite_sequence sequence;
    try {
        using dogen::utility::test_data::generate_vector;
        std::vector<infinite_sequence::value_type>
            terms(generate_vector<infinite_sequence>());
        BOOST_FAIL("Expected container_generation_error exception.");
    } catch (const dogen::utility::test_data::container_generation_error& e) {
        BOOST_LOG_SEV(lg, info) << "Exception thrown as expected: " << e.what();
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_SUITE_END()
