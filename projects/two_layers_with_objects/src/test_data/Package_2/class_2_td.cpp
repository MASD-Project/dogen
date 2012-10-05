/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/two_layers_with_objects/test_data/Package_2/class_2_td.hpp"
#include "dogen/two_layers_with_objects/test_data/versioned_key_td.hpp"

namespace dogen {
namespace two_layers_with_objects {
namespace Package_2 {
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

} } } }
