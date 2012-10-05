/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DISABLE_FACET_FOLDERS_VERSIONED_KEY_TD_HPP
#define DOGEN_DISABLE_FACET_FOLDERS_VERSIONED_KEY_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/disable_facet_folders/versioned_key.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace disable_facet_folders {

namespace detail {

class versioned_key_generator {
public:
    typedef dogen::disable_facet_folders::versioned_key value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::versioned_key_generator> versioned_key_sequence;

} }

#endif
