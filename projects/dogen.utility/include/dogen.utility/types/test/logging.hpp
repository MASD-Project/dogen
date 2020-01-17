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
#ifndef DOGEN_UTILITY_TEST_LOGGING_HPP
#define DOGEN_UTILITY_TEST_LOGGING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/log/scoped_lifecycle_manager.hpp"

namespace dogen::utility::test {

void log_if_test_has_failed();

dogen::utility::log::scoped_lifecycle_manager
scoped_lifecycle_manager_factory(std::string test_module,
    std::string test_suite,
    std::string function_name,
    const bool logging_enabled_locally = false,
    const bool log_to_console = false);

}

#ifdef SETUP_TEST_LOG
#undef SETUP_TEST_LOG
#endif
#define SETUP_TEST_LOG(function_name)                                   \
    BOOST_TEST_CHECKPOINT(function_name);                               \
    auto sl(dogen::utility::test::scoped_lifecycle_manager_factory(     \
            test_module, test_suite, function_name));

#ifdef SETUP_TEST_LOG_DEBUG
#undef SETUP_TEST_LOG_DEBUG
#endif
#define SETUP_TEST_LOG_DEBUG(function_name)                            \
    BOOST_TEST_CHECKPOINT(function_name);                              \
    auto sl(dogen::utility::test::scoped_lifecycle_manager_factory(    \
            test_module, test_suite, function_name, true));

#ifdef SETUP_TEST_LOG_SOURCE
#undef SETUP_TEST_LOG_SOURCE
#endif
#define SETUP_TEST_LOG_SOURCE(function_name)                           \
    BOOST_TEST_CHECKPOINT(function_name);                              \
    auto sl(dogen::utility::test::scoped_lifecycle_manager_factory(    \
            test_module, test_suite, function_name));                  \
    using namespace dogen::utility::log;                               \
    dogen::utility::log::logger lg(                                    \
        dogen::utility::log::logger_factory(test_suite));


#ifdef SETUP_TEST_LOG_SOURCE_DEBUG
#undef SETUP_TEST_LOG_SOURCE_DEBUG
#endif
#define SETUP_TEST_LOG_SOURCE_DEBUG(function_name)                   \
    BOOST_TEST_CHECKPOINT(function_name);                            \
    auto sl(dogen::utility::test::scoped_lifecycle_manager_factory(  \
            test_module, test_suite, function_name, true));          \
    using namespace dogen::utility::log;                             \
    dogen::utility::log::logger lg(                                  \
        dogen::utility::log::logger_factory(test_suite));

#endif
