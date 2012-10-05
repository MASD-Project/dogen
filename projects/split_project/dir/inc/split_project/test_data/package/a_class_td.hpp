/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SPLIT_PROJECT_TEST_DATA_PACKAGE_A_CLASS_TD_HPP
#define DOGEN_SPLIT_PROJECT_TEST_DATA_PACKAGE_A_CLASS_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/split_project/domain/package/a_class.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace split_project {
namespace package {

namespace detail {

class a_class_generator {
public:
    typedef dogen::split_project::package::a_class value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::a_class_generator> a_class_sequence;

} } }

#endif
