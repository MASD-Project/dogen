/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/disable_facet_folders/package1/first_class_sequence.hpp"
#include "dogen/disable_facet_folders/versioned_key_sequence.hpp"

namespace dogen {
namespace disable_facet_folders {
namespace package1 {
namespace detail {

first_class_generator::value_type
first_class_generator::next_term(const unsigned int position) {
    first_class r;

    if (position == 0) {
        r.public_attribute(static_cast<int>(0));
        r.private_attribute(static_cast<int>(1));
    } else if (position == 1) {
        r.public_attribute(static_cast<int>(30));
        r.private_attribute(static_cast<int>(31));
    } else if (position == 2) {
        r.public_attribute(static_cast<int>(60));
        r.private_attribute(static_cast<int>(61));
    }

    return r;
}

unsigned int first_class_generator::length() const { return(3); }

} } } }
