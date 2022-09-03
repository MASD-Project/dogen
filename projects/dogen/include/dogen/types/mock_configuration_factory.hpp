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
#ifndef DOGEN_TYPES_MOCK_CONFIGURATION_FACTORY_HPP
#define DOGEN_TYPES_MOCK_CONFIGURATION_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/types/configuration.hpp"

namespace dogen {

/**
 * @brief Creates a configuration suitable for use in tests.
 */
class mock_configuration_factory final {
public:
    mock_configuration_factory(const bool enable_tracing,
        const bool enable_reporting, const bool enable_diffing,
        const std::string& variability_override = std::string());

public:
    configuration make(const boost::filesystem::path& target,
        const std::string& activity) const;

private:
    const bool enable_tracing_;
    const bool enable_reporting_;
    const bool enable_diffing_;
    const std::string variability_override_;
};

}

#endif
