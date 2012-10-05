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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
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
