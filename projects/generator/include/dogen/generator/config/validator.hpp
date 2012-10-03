/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_CONFIG_VALIDATOR_HPP
#define DOGEN_GENERATOR_CONFIG_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/generator/config/settings.hpp"

namespace dogen {
namespace generator {
namespace config {

class validator {
public:
    validator() = delete;
    validator(const validator&) = delete;
    ~validator() = delete;
    validator(validator&&) = delete;
    validator& operator=(const validator&) = delete;

public:
    static void validate(const settings& s);
};

} } }

#endif
