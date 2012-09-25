/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_GENERATE_CONTAINER_HPP
#define DOGEN_UTILITY_TEST_DATA_GENERATE_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/throw_exception.hpp>
#include "dogen/utility/exception/utility_exception.hpp"

namespace dogen {
namespace utility {
namespace test_data {

/**
 * @brief Error occurred during container generation.
 */
class container_generation_error :
        public dogen::utility::exception::exception {
public:
    container_generation_error(const char* message) :
        dogen::utility::exception::exception(message) { }
};

/**
 * @brief Generates a vector using the given sequence.
 *
 * @param size Number of elements to generate.
 *
 * @pre When using open ended sequences one must pass a non-zero size
 * value.
 * @pre when using a closed sequence, size must not exceed sequence
 * length.
 *
 * @post generate_vector shall never create an empty vector.
 */
template<typename Sequence>
std::vector<typename Sequence::value_type>
generate_vector(const unsigned int size = 0) {
    Sequence sequence;

    if (!size && !sequence.length()) {
        const char* message("Open ended sequences require size");
        BOOST_THROW_EXCEPTION(container_generation_error(message));
    }

    if (size && sequence.length() && (size > sequence.length())) {
        const char* message("Size exceeds closed sequence length");
        BOOST_THROW_EXCEPTION(container_generation_error(message));
    }

    const unsigned int actual_size(size ? size : sequence.length());
    std::vector<typename Sequence::value_type> container;
    container.reserve(actual_size);
    std::generate_n(std::back_inserter(container), actual_size, sequence);
    return(container);
}

} } }

#endif
