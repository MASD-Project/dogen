/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_PROTOTYPE_TEST_DATA_CURRENCY_TD_HPP
#define DOGEN_PROTOTYPE_TEST_DATA_CURRENCY_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/prototype/domain/currency.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace prototype {

namespace detail {

typedef dogen::utility::test_data::generator<
    dogen::prototype::currency> currency_generator;

/**
 * @brief Generates a sequence with all of ISO 4217 currencies.
 *
 * @see kitanda::test_data::sequence.
 */
class complete_currency_generator : public currency_generator {
public:
    complete_currency_generator() : currency_generator(178) { }

public:
    value_type next_term(const unsigned int position);
};

/**
 * @brief Generates a sequence with the currencies of the major
 * countries in ISO 4217.
 *
 * @see sequence.
 */
class majors_currency_generator : public currency_generator {
public:
    majors_currency_generator() : currency_generator(8) { }

public:
    value_type next_term(const unsigned int position);
};

/**
 * @brief Generates an invalid but very large sequence of currencies.
 *
 * @see sequence.
 */
class unrealistic_currency_generator : public currency_generator {
public:
    unrealistic_currency_generator() :
        currency_generator(26 * 26 * 26/*permutations with 3 letters*/) { }

public:
    value_type next_term(const unsigned int position);
};

}

typedef dogen::utility::test_data::sequence<
    detail::complete_currency_generator>
complete_currency_sequence;

typedef dogen::utility::test_data::sequence<
    detail::majors_currency_generator>
majors_currency_sequence;

typedef dogen::utility::test_data::sequence<
    detail::unrealistic_currency_generator>
unrealistic_currency_sequence;

} }

#endif
