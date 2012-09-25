/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/classes_without_package/test_data/class_2_sequence.hpp"
#include "dogen/classes_without_package/test_data/versioned_key_sequence.hpp"

namespace dogen {
namespace classes_without_package {
namespace detail {

class_2_generator::value_type
class_2_generator::next_term(const unsigned int position) {
    class_2 r;

    if (position == 0) {
    } else if (position == 1) {
    } else if (position == 2) {
    }

    return r;
}

unsigned int class_2_generator::length() const { return(3); }

} } }
