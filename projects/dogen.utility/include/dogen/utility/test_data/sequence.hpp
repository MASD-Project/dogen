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
#ifndef DOGEN_UTILITY_TEST_DATA_SEQUENCE_HPP
#define DOGEN_UTILITY_TEST_DATA_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/throw_exception.hpp>
#include "dogen/utility/exception/utility_exception.hpp"

namespace dogen {
namespace utility {
namespace test_data {

/**
 * @brief Attempting to generate more terms that those on the
 * sequence.
 */
class sequence_exhausted : public dogen::utility::exception::exception {
private:
    typedef dogen::utility::exception::exception exception;

public:
    sequence_exhausted() :
        exception("attempt to go beyond end of sequence.") { }
};

/**
 * @brief Generates sequences of Generator::result_type.
 *
 * sequence is designed to be plugged to STL algorithms such as
 * generate and generate_n.
 *
 * Note: Sequence cannot be made non-copyable due to some copying
 * performed by the algorithm.
 *
 * @section s_0_1 Generator concept
 *
 * @li Generator::result_type;
 * @li Generator::Generator(const bool use_default_version);
 * @li Generator::result_type Generator::next_term(const unsigned int term);
 * @li unsigned int Generator::length() const;
 *
 */
template<typename Generator>
class sequence {
public:
    typedef Generator generator_type;

public:
     sequence() : position_(0) { }

public:
    typedef typename Generator::result_type result_type;

public:
    /**
     * @brief Length of the entire sequence, for preallocation
     * purposes.
     *
     * If length is zero, the sequence is infinite (e.g. its up to the
     * user to stop the generation process).
     */
    unsigned int length() const { return(generator_.length()); }

    /**
     * @brief Reset sequence back to the first term.
     */
    void reset() { position_ = 0; }

public:
    result_type operator()() {
        if (length() && position_ >= length())
            BOOST_THROW_EXCEPTION(sequence_exhausted());
        return(generator_.next_term(position_++));
    }

private:
    unsigned int position_;
    generator_type generator_;
};

} } }

#endif
