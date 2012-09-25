/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_OBJECT_TYPES_HPP
#define DOGEN_DIA_DOMAIN_OBJECT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace dia {

/**
 * @brief Identifier for the type of Dia object.
 */
enum class object_types : unsigned int {
    invalid = 0,
    uml_large_package = 1, ///< A UML package
    uml_class = 2 ///< A UML class
};

} }

#endif
