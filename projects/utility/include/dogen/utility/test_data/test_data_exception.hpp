/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_EXCEPTION_HPP
#define DOGEN_UTILITY_TEST_DATA_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/exception/utility_exception.hpp"

namespace dogen {
namespace utility {
namespace test_data {

class exception : public dogen::utility::exception::exception {
public:
    /**
     * @param message Error message. Must be a string literal.
     */
    exception(std::string message)
        : dogen::utility::exception::exception(message) { }
    exception() { }

    virtual ~exception() throw() {}
};

} } }

#endif
