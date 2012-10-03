/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_CONFIG_CONFIGURATION_ERROR_HPP
#define DOGEN_GENERATOR_CONFIG_CONFIGURATION_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/exception/utility_exception.hpp"

namespace dogen {
namespace generator {
namespace config {

/**
 * @brief The settings provided for the configuration of the generator
 * are invalid.
 */
class configuration_error : public utility::exception::exception {
public:
    configuration_error(std::string message)
        : utility::exception::exception(message) { }
    configuration_error() { }

    virtual ~configuration_error() throw() {}
};

} } }

#endif
