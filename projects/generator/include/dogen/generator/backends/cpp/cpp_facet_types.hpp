/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FACET_TYPES_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FACET_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

/**
 * @brief Facets are different aspects of the domain objects we're
 * interested in.
 */
enum class cpp_facet_types : unsigned int {
    invalid = 0,
    domain = 1, ///< The definition of the domain type itself
    hash = 2, ///< Hashing for the domain type
    serialization = 3, ///< Serialisation for the domain type
    io = 4, ///< IO (streaming) for the domain type
    test_data, ///< Test data generators for all domain types
    database ///< Database code for the domain types
};

std::ostream& operator<<(std::ostream& stream, cpp_facet_types value);

} } } }

#endif
