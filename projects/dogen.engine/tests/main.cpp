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
#define BOOST_TEST_MODULE dogen.engine.tests
#include <boost/test/unit_test.hpp>
#include "dogen/config.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/fixture.hpp"
#include "dogen.utility/types/test_data/dogen_generation.hpp"
#include "dogen.utility/types/test_data/cpp_ref_impl_generation.hpp"
#include "dogen.utility/types/test_data/csharp_ref_impl_generation.hpp"
#include "dogen.generation.csharp/types/initializer.hpp"
#include "dogen.generation.cpp/types/initializer.hpp"
#include "dogen.injection.json/types/initializer.hpp"
#include "dogen.injection.dia/types/initializer.hpp"
#ifdef DOGEN_HAVE_RELATIONAL_MODEL
#include "dogen.relational/types/initializer.hpp"
#endif // DOGEN_HAVE_RELATIONAL_MODEL
#include "dogen.tracing/types/initializer.hpp"

namespace  {

const std::string test_suite("initializer");
const std::string test_module("dogen.engine.tests");

struct initializer {
    initializer() {
        SETUP_TEST_LOG("initializer");

#if defined (_WIN32)
#if defined(DEBUG) || defined(_DEBUG)
        /*
         * To enable the debug dumps, uncomment the two lines below
         * and comment the last line. Leave it commented out as it
         * causes builds to time out and we can't really investigate
         * the problem.
         */
// #define _CRTDBG_MAP_ALLOC
//        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_CRT_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //_CRTDBG_CHECK_ALWAYS_DF)
        _CrtSetDbgFlag(0);
#endif
#endif

        dogen::injection::json::initializer::initialize();
        dogen::injection::dia::initializer::initialize();
        dogen::generation::csharp::initializer::initialize();
        dogen::generation::cpp::initializer::initialize();
        dogen::utility::test_data::dogen_generation::initialize();
        dogen::tracing::initializer::initialize();
#ifdef ENABLE_CPP_REF_IMPL_TESTS
        dogen::utility::test_data::cpp_ref_impl_generation::initialize();
#endif // ENABLE_CPP_REF_IMPL_TESTS
#ifdef ENABLE_CSHARP_REF_IMPL_TESTS
        dogen::utility::test_data::csharp_ref_impl_generation::initialize();
#endif // ENABLE_CSHARP_REF_IMPL_TESTS
#ifdef DOGEN_HAVE_RELATIONAL_MODEL
        dogen::relational::initializer::initialize();
#endif // DOGEN_HAVE_RELATIONAL_MODEL
    }
};

}

using namespace dogen::utility::test;
BOOST_GLOBAL_FIXTURE(exception_fixture);
BOOST_GLOBAL_FIXTURE(initializer);
