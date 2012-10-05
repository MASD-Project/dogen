/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DISABLE_CMAKELISTS_TEST_DATA_PACKAGE1_FIRST_CLASS_TD_HPP
#define DOGEN_DISABLE_CMAKELISTS_TEST_DATA_PACKAGE1_FIRST_CLASS_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/disable_cmakelists/domain/package1/first_class.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace disable_cmakelists {
namespace package1 {

namespace detail {

class first_class_generator {
public:
    typedef dogen::disable_cmakelists::package1::first_class value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::first_class_generator> first_class_sequence;

} } }

#endif
