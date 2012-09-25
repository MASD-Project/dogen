/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASSES_WITHOUT_PACKAGE_TEST_DATA_CLASS_5_SEQUENCE_HPP
#define DOGEN_CLASSES_WITHOUT_PACKAGE_TEST_DATA_CLASS_5_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/classes_without_package/domain/class_5.hpp"
#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"

namespace dogen {
namespace classes_without_package {

namespace detail {

class class_5_generator {
public:
    typedef dogen::classes_without_package::class_5 value_type;

public:
    value_type next_term(const unsigned int position);
    unsigned int length() const;
};

}

typedef dogen::utility::test_data::sequence<
    detail::class_5_generator> class_5_sequence;

} }

#endif
