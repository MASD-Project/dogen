/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/classes_in_a_package/test_data/package_1/class_4_td.hpp"
#include "dogen/classes_in_a_package/test_data/versioned_key_td.hpp"

namespace dogen {
namespace classes_in_a_package {
namespace package_1 {
namespace detail {

class_4_generator::value_type
class_4_generator::next_term(const unsigned int position) {
    class_4 r;

    if (position == 0) {
    } else if (position == 1) {
    } else if (position == 2) {
    }

    return r;
}

unsigned int class_4_generator::length() const { return(3); }

} } } }
