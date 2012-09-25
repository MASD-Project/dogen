/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FILE_TYPES_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FILE_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

/**
 * @brief Types of files used by the C++ backend.
 */
enum class cpp_file_types : unsigned int {
    invalid = 0,
    header = 1, ///< A C++ header file.
    implementation = 2, ///< A C++ implementation file.
};

std::ostream& operator<<(std::ostream& stream, cpp_file_types value);

} } } }

#endif
