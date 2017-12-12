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
#define BOOST_TEST_MODULE yarn_tests
#include <boost/test/included/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/fixture.hpp"
#include "dogen/quilt.csharp/types/initializer.hpp"
#include "dogen/quilt.cpp/types/initializer.hpp"
#include "dogen/external.json/types/initializer.hpp"
#include "dogen.external.dia/types/initializer.hpp"

namespace  {

const std::string test_suite("initializer");
const std::string test_module("yarn");

struct initializer {
    initializer() {
        SETUP_TEST_LOG("initializer");
        dogen::external::json::initializer::initialize();
        dogen::external::dia::initializer::initialize();
        dogen::quilt::csharp::initializer::initialize();
        dogen::quilt::cpp::initializer::initialize();
    }
};

}

using namespace dogen::utility::test;
BOOST_GLOBAL_FIXTURE(exception_fixture);
BOOST_GLOBAL_FIXTURE(initializer);
