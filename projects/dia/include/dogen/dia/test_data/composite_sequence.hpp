/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
