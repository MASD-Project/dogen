/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef MASD_DOGEN_TYPES_CONFIGURATION_VALIDATOR_HPP
#define MASD_DOGEN_TYPES_CONFIGURATION_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "masd.dogen/types/configuration.hpp"

namespace masd::dogen {

/**
 * @brief Validates the Dogen configuration at the API level.
 */
class configuration_validator final {
public:
    configuration_validator() = delete;
    configuration_validator(const configuration_validator&) = delete;
    configuration_validator(configuration_validator&&) = delete;
    ~configuration_validator() = delete;
    configuration_validator& operator=(
        const configuration_validator&) = delete;

public:
    static void validate(
        const boost::optional<error_handling_configuration>& ocfg);
    static void validate(const boost::optional<tracing_configuration>& ocfg);
    static void validate(const boost::optional<diffing_configuration>& ocfg);

public:
    static void validate(const configuration& cfg);
};

}

#endif
