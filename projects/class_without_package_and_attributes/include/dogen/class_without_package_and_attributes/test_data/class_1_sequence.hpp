/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASS_WITHOUT_PACKAGE_AND_ATTRIBUTES_TEST_DATA_CLASS_1_SEQUENCE_HPP
#define DOGEN_CLASS_WITHOUT_PACKAGE_AND_ATTRIBUTES_TEST_DATA_CLASS_1_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/class_without_package_and_attributes/domain/class_1.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace class_without_package_and_attributes {

namespace detail {

class class_1_generator {
public:
    typedef dogen::class_without_package_and_attributes::class_1 value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::class_1_generator> class_1_sequence;

} }

#endif
