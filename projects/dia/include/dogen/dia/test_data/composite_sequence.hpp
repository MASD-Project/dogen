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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_DIA_TEST_DATA_COMPOSITE_SEQUENCE_HPP
#define DOGEN_DIA_TEST_DATA_COMPOSITE_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dia/domain/composite.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/dia/test_data/attribute_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {

namespace detail {

/**
 * @brief Generates composites with non-composite values.
 *
 * @see sequence.
 */
class simple_composite_generator {
public:
    typedef dogen::dia::composite value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const { return(3); }
};

/**
 * @brief Generates composites with composite values.
 *
 * @see sequence.
 */
class composite_composite_generator {
public:
    typedef dogen::dia::composite value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<
    detail::simple_composite_generator> simple_composite_sequence;

typedef utility::test_data::sequence<
    detail::composite_composite_generator> composite_composite_sequence;

} } }

#endif
