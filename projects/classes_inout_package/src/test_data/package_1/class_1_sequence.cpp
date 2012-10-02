/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/classes_inout_package/test_data/package_1/class_1_sequence.hpp"
#include "dogen/classes_inout_package/test_data/versioned_key_sequence.hpp"

namespace dogen {
namespace classes_inout_package {
namespace package_1 {
namespace detail {

class_1_generator::value_type
class_1_generator::next_term(const unsigned int position) {
    class_1 r;

    if (position == 0) {
    } else if (position == 1) {
    } else if (position == 2) {
    }

    return r;
}

unsigned int class_1_generator::length() const { return(3); }

} } } }
