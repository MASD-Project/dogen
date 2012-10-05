/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/split_project/test_data/package/a_class_td.hpp"
#include "dogen/split_project/test_data/versioned_key_td.hpp"

namespace dogen {
namespace split_project {
namespace package {
namespace detail {

a_class_generator::value_type
a_class_generator::next_term(const unsigned int position) {
    a_class r;

    if (position == 0) {
    } else if (position == 1) {
    } else if (position == 2) {
    }

    return r;
}

unsigned int a_class_generator::length() const { return(3); }

} } } }
