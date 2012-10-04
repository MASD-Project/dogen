/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_EXCEPTION_CHECKERS_HPP
#define DOGEN_UTILITY_EXCEPTION_CHECKERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/utility/test/asserter.hpp"

namespace dogen {
namespace utility {
namespace test {

template<typename Exception>
class contains_checker {
public:
    contains_checker(const std::string expected) : expected_(expected) { }

    bool operator()(const Exception& e) {
        const std::string actual(e.what());
        return asserter::assert_contains(expected_, actual);
    }

private:
    const std::string expected_;
};

} } }

#endif
