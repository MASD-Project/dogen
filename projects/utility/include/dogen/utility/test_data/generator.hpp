/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_GENERATOR_HPP
#define DOGEN_UTILITY_TEST_DATA_GENERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace utility {
namespace test_data {

/**
 * @brief Base class for generators.
 *
 * @see sequence.
 */
template<typename Entity>
class generator {
public:
    typedef Entity value_type;

public:
    generator(const unsigned int length) : length_(length) { }
    virtual ~generator() { }

public:
    virtual value_type next_term(const unsigned int position) = 0;
    unsigned int length() const { return(length_); }

private:
    const unsigned int length_;
};

} } }

#endif
