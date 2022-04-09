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
#define BOOST_TEST_MODULE masd.codec.tests
#include <boost/test/unit_test.hpp>
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/fixture.hpp"
#include "dogen.utility/types/test/fixture.hpp"
#include "dogen.utility/types/test_data/dogen_product.hpp"

namespace  {

const std::string test_suite("initializer");
const std::string test_module("dogen.codec.tests");

struct initializer {
    initializer() {
        SETUP_TEST_LOG_SOURCE("initializer");
        BOOST_LOG_SEV(lg, debug) << "Started initialisation.";

        dogen::utility::test_data::dogen_product::initialize();
    }
};

}

using namespace dogen::utility::test;
BOOST_GLOBAL_FIXTURE(exception_fixture);
BOOST_GLOBAL_FIXTURE(initializer);
