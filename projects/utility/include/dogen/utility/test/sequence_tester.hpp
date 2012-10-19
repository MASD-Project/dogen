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
    typedef typename Sequence::result_type entity_type;
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
