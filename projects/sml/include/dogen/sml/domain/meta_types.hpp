/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_DOMAIN_META_TYPES_HPP
#define DOGEN_SML_DOMAIN_META_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml {

/**
 * @brief Set of all available types of types in SML.
 */
enum class meta_types : unsigned int {
    invalid = 0, ///< we don't yet know the type's type
    enumeration = 1, ///< Type is an enumeration
    pod = 2, ///< Type is Plain Old Data
    attribute = 3, ///< Type is an attribute
    package = 4, ///< Type is a package
    primitive = 5 ///< Type is a package
};

} }

#endif
