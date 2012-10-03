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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"

namespace dogen {
namespace utility {
namespace test {

template<typename Exception>
class contains_checker {
public:
    contains_checker(const std::string expected) : expected_(expected) { }

    bool operator()(const Exception& e) {
        const std::string actual(e.what());

        using namespace dogen::utility::log;
        logger lg_(logger_factory("contains_checker"));

        BOOST_LOG_SEV(lg_, debug) <<"expected: " << expected_;
        BOOST_LOG_SEV(lg_, debug) <<"actual: " << actual;

        return boost::contains(actual, expected_);
    }

private:
    const std::string expected_;
};

} } }

#endif
