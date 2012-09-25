/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASSES_IN_A_PACKAGE_TEST_DATA_UNVERSIONED_KEY_SEQUENCE_HPP
#define DOGEN_CLASSES_IN_A_PACKAGE_TEST_DATA_UNVERSIONED_KEY_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/classes_in_a_package/domain/unversioned_key.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace classes_in_a_package {

namespace detail {

class unversioned_key_generator {
public:
    typedef dogen::classes_in_a_package::unversioned_key value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::unversioned_key_generator> unversioned_key_sequence;

} }

#endif
