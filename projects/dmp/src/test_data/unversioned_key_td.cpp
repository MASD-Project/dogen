/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/dmp/test_data/unversioned_key_td.hpp"

namespace dogen {
namespace dmp {
namespace detail {

unversioned_key_generator::value_type
unversioned_key_generator::next_term(const unsigned int position) {
    unversioned_key r;

    if (position == 0) {
        r.id(static_cast<unsigned int>(0));
    } else if (position == 1) {
        r.id(static_cast<unsigned int>(30));
    } else if (position == 2) {
        r.id(static_cast<unsigned int>(60));
    }

    return r;
}

unsigned int unversioned_key_generator::length() const { return(3); }

} } }
