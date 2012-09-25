/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_UTILITY_UTILITY_HPP
#define DOGEN_DIA_UTILITY_UTILITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia/domain/object_types.hpp"

namespace dogen {
namespace dia {

/**
 * @brief Helper functions and classes for the Dia domain object.
 */

namespace utility {

object_types parse_object_type(const std::string& dia_type);

} } }

#endif
