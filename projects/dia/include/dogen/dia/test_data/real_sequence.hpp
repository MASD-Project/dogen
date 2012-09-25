/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_TEST_DATA_REAL_SEQUENCE_HPP
#define DOGEN_DIA_TEST_DATA_REAL_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dia/domain/real.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class real_generator {
public:
    typedef dogen::dia::real value_type;

public:
    value_type next_term(const unsigned int position) {
        if (position == 0)
            return dogen::dia::real("29.6875");
        else if (position == 1)
            return dogen::dia::real("16.5");

        return dogen::dia::real("0.10000000149011612");
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<detail::real_generator> real_sequence;

} } }

#endif
