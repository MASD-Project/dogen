/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASSES_INSIDE_AND_OUTSIDE_PACKAGE_TEST_DATA_VERSIONED_KEY_SEQUENCE_HPP
#define DOGEN_CLASSES_INSIDE_AND_OUTSIDE_PACKAGE_TEST_DATA_VERSIONED_KEY_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/classes_inside_and_outside_package/domain/versioned_key.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace classes_inside_and_outside_package {

namespace detail {

class versioned_key_generator {
public:
    typedef dogen::classes_inside_and_outside_package::versioned_key value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::versioned_key_generator> versioned_key_sequence;

} }

#endif
