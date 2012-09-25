/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_TWO_LAYERS_WITH_OBJECTS_TEST_DATA_UNVERSIONED_KEY_SEQUENCE_HPP
#define DOGEN_TWO_LAYERS_WITH_OBJECTS_TEST_DATA_UNVERSIONED_KEY_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/two_layers_with_objects/domain/unversioned_key.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace two_layers_with_objects {

namespace detail {

class unversioned_key_generator {
public:
    typedef dogen::two_layers_with_objects::unversioned_key value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::unversioned_key_generator> unversioned_key_sequence;

} }

#endif
