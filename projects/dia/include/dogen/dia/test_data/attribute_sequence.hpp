/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_TEST_DATA_ATTRIBUTE_SEQUENCE_HPP
#define DOGEN_DIA_TEST_DATA_ATTRIBUTE_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dia/domain/attribute.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {

namespace detail {

/**
 * @brief Generates attributes with non-composite values.
 *
 * @see sequence.
 */
class simple_attribute_generator {
public:
    typedef dogen::dia::attribute value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const { return(3); }
};

/**
 * @brief Generates attributes with composite values.
 *
 * @see sequence.
 */
class composite_attribute_generator {
public:
    typedef dogen::dia::attribute value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<
    detail::simple_attribute_generator> simple_attribute_sequence;

typedef utility::test_data::sequence<
    detail::composite_attribute_generator> composite_attribute_sequence;

} } }

#endif
