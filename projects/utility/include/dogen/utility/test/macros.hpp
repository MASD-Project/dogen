/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_MACROS_HPP
#define DOGEN_UTILITY_TEST_MACROS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Macro for compiling test code that should fail to compile.
 *
 * This is used for example for ensuring that certain classes are
 * non-copyable, etc.
 */

#ifdef DOGEN_TEST_COMPILATION
#define DOGEN_COMPILE_BROKEN_CODE
#else
#undef DOGEN_COMPILE_BROKEN_CODE
#endif

#ifdef BOOST_IGNORE_AUTO_TEST_CASE
#undef
#endif
#define BOOST_IGNORE_AUTO_TEST_CASE(test_name) void test_name()

#endif
