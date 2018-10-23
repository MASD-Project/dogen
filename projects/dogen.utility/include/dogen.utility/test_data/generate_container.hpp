/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_UTILITY_TEST_DATA_GENERATE_CONTAINER_HPP
#define DOGEN_UTILITY_TEST_DATA_GENERATE_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/throw_exception.hpp>
#include "dogen.utility/exception/utility_exception.hpp"

namespace dogen::utility::test_data {

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
std::vector<typename Sequence::result_type>
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
    std::vector<typename Sequence::result_type> container;
    container.reserve(actual_size);
    std::generate_n(std::back_inserter(container), actual_size, sequence);
    return(container);
}

}

#endif
