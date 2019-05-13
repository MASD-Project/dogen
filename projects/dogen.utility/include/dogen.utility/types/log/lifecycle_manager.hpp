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
#ifndef DOGEN_UTILITY_LOG_LIFE_CYCLE_MANAGER_HPP
#define DOGEN_UTILITY_LOG_LIFE_CYCLE_MANAGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.utility/types/log/severity_level.hpp"
#include "dogen.utility/types/log/logging_configuration.hpp"

namespace dogen::utility::log {

/**
 * @brief Manages the starting and stopping of logging for an
 * application.
 */
class lifecycle_manager {
public:
    lifecycle_manager() = delete;
    lifecycle_manager(const lifecycle_manager&) = delete;
    ~lifecycle_manager() = delete;
    lifecycle_manager(lifecycle_manager&&) = delete;
    lifecycle_manager& operator=(const lifecycle_manager&) = delete;

private:
    /**
     * @brief Creates a boost log file backend.
     *
     * @note path is non-const by ref by design.
     */
    static void create_file_backend(boost::filesystem::path path,
        const severity_level severity);

    /**
     * @brief Creates a boost log console backend.
     */
    static void create_console_backend(const severity_level severity);

public:
    /**
     * @brief Initialise logging for the entire application.
     *
     * If no configuration is supplied, logging is disabled.
     *
     * @note Must be done in a thread-safe context.
     */
    static void initialise(const boost::optional<logging_configuration>& ocfg);

    /**
     * @brief Shutdown logging for the entire application.
     *
     * Should be done in a thread-safe context.
     */
    static void shutdown();
};

}

#endif
