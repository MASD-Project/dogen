/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_TEST_DATA_PACKAGE_SEQUENCE_HPP
#define DOGEN_SML_TEST_DATA_PACKAGE_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/sml/domain/package.hpp"
#include "dogen/sml/test_data/qualified_name_sequence.hpp"

namespace dogen {
namespace sml {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class package_generator {
public:
    typedef dogen::sml::package value_type;

public:
    value_type next_term(const unsigned int position) {
        dogen::sml::package result;
        qualified_name_sequence seq;

        if (position == 0) {
            result.name(seq());
        } else if (position == 1) {
            seq();
            result.name(seq());
        }
        else {
            seq();
            seq();
            result.name(seq());
        }

        return result;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<
    detail::package_generator> package_sequence;

} } }


#endif
