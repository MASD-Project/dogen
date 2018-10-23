/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_UTILITY_TEST_IO_TESTER_HPP
#define DOGEN_UTILITY_TEST_IO_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.utility/test/json_validator.hpp"

namespace dogen::utility::test {

/**
 * @brief Ensures the inserter operator produces valid JSON.
 */
template<typename Entity>
class io_tester {
public:
    typedef Entity entity_type;

public:
    static void inserter_operator_produces_valid_json(const Entity& a) {
        using namespace dogen::utility::log;
        logger lg(logger_factory("utility.test.io_tester"));
        BOOST_LOG_SEV(lg, debug) << "json: " << a;

        std::stringstream s;
        s << a;
        BOOST_CHECK(json_validator::validate(s));
        log_if_test_has_failed();
    }
};

}

#endif
