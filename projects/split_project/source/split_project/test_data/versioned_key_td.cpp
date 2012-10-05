/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/split_project/test_data/versioned_key_td.hpp"

namespace dogen {
namespace split_project {
namespace detail {

versioned_key_generator::value_type
versioned_key_generator::next_term(const unsigned int position) {
    versioned_key r;

    if (position == 0) {
        r.id(static_cast<unsigned int>(0));
        r.version(static_cast<unsigned int>(1));
    } else if (position == 1) {
        r.id(static_cast<unsigned int>(30));
        r.version(static_cast<unsigned int>(31));
    } else if (position == 2) {
        r.id(static_cast<unsigned int>(60));
        r.version(static_cast<unsigned int>(61));
    }

    return r;
}

unsigned int versioned_key_generator::length() const { return(3); }

} } }
