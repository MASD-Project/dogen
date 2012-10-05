/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_TWO_LAYERS_WITH_OBJECTS_TEST_DATA_PACKAGE_1_CLASS_1_TD_HPP
#define DOGEN_TWO_LAYERS_WITH_OBJECTS_TEST_DATA_PACKAGE_1_CLASS_1_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/two_layers_with_objects/domain/package_1/class_1.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace two_layers_with_objects {
namespace package_1 {

namespace detail {

class class_1_generator {
public:
    typedef dogen::two_layers_with_objects::package_1::class_1 value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::class_1_generator> class_1_sequence;

} } }

#endif
