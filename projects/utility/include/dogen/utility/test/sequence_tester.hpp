/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_SEQUENCE_TESTER_HPP
#define DOGEN_UTILITY_TEST_DATA_SEQUENCE_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/generate_container.hpp"

namespace dogen {
namespace utility {
namespace test {

/**
 * @brief Tester for domain specific sequences.
 */
template<typename Sequence>
class sequence_tester {
public:
    typedef typename Sequence::value_type entity_type;
    typedef Sequence sequence_type;

public:
    /**
     * @brief Exercises sequence code, ensuring number of generated
     * elements matches sequence size.
     */
    static void validate_sequence_length() {
        Sequence sequence;

        // ensure we have a size if dealing with infinite sequences.
        const unsigned int size(sequence.length() ? sequence.length() : 10000);
        std::vector<entity_type> result(
            dogen::utility::test_data::generate_vector<sequence_type>(size));
        BOOST_CHECK(size == result.size());

        using namespace dogen::utility::log;
        logger lg(logger_factory("sequence_tester"));
        const unsigned int output_size(20);
        if (result.size() < output_size) {
            BOOST_LOG_SEV(lg, debug) << result;
        } else {
            std::vector<entity_type> result_subset;
            result_subset.reserve(output_size);
            std::copy(result.begin(),
                result.begin() + output_size,
                std::back_inserter(result_subset));
            BOOST_LOG_SEV(lg, debug) << result_subset;
        }
    }
};

} } }

#endif
