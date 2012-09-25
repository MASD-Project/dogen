/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_MODELING_VALIDATION_ERROR_HPP
#define DOGEN_GENERATOR_MODELING_VALIDATION_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/exception/utility_exception.hpp"

namespace dogen {
namespace generator {
namespace modeling {


/**
 * @brief A fatal error has occurred during code generation.
 */
class validation_error : public utility::exception::exception {
public:
    validation_error(std::string message)
        : utility::exception::exception(message) { }
    validation_error() { }

    virtual ~validation_error() throw() {}
};

} } }

#endif
