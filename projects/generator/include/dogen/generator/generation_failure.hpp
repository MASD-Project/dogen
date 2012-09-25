/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_GENERATION_FAILURE_HPP
#define DOGEN_GENERATOR_GENERATION_FAILURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/exception/utility_exception.hpp"

namespace dogen {
namespace generator {

/**
 * @brief A fatal error has occurred during code generation.
 */
class generation_failure : public utility::exception::exception {
public:
    generation_failure(std::string message)
        : utility::exception::exception(message) { }
    generation_failure() { }

    virtual ~generation_failure() throw() {}
};

} }

#endif
