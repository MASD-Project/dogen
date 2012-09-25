/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_ASPECT_TYPES_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_ASPECT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

/**
 * @brief An aspect in a facet.
 *
 * Facets represent different ways of looking at domain objects.
 * However, not everything in a facet is related to the domain type;
 * some plumbing is required in order to fully implement a facet. This
 * enum allows us to distinguish between the different types of @e
 * components a facet has, which we choose to call @e aspects.
 */
enum class cpp_aspect_types : unsigned int {
    invalid = 0,
    main = 1, ///< The representation of the domain type for this facet
    includers = 2, ///< Header file with includes for all headers in facet
    versioned_key = 3, ///< A Key with version
    unversioned_key = 4 ///< A key without version
};

std::ostream& operator<<(std::ostream& stream, cpp_aspect_types value);

} } } }

#endif
