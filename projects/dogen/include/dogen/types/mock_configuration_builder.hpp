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
#ifndef DOGEN_TYPES_MOCK_CONFIGURATION_BUILDER_HPP
#define DOGEN_TYPES_MOCK_CONFIGURATION_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/types/configuration.hpp"

namespace dogen {

/**
 * @brief Creates configurations for testing purposes.
 */
/**
 * @brief Creates a configuration suitable for use in tests.
 */
class mock_configuration_builder final {
private:
    std::string read_variability_override() const;

public:
    mock_configuration_builder&
    target(const boost::filesystem::path& target);

    mock_configuration_builder& activity(const std::string& activity);
    mock_configuration_builder& enable_tracing();
    mock_configuration_builder& enable_reporting();
    mock_configuration_builder& enable_diffing();
    mock_configuration_builder& read_environment();
    mock_configuration_builder& use_fixed_activity_timestamp();

public:
    configuration build() const;

private:
    boost::filesystem::path target_;
    std::string activity_;
    bool enable_tracing_locally_{};
    bool enable_reporting_locally_{};
    bool enable_diffing_locally_{};
    bool read_environment_locally_{};
    bool use_fixed_activity_timestamp_{};
};

}

#endif
