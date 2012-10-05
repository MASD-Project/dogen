/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
 * You should have received a copy of the GNU General PublicLicense
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
#include <boost/shared_ptr.hpp>
#include <boost/log/core/core.hpp>
#include "dogen/utility/log/severity_level.hpp"

namespace dogen {
namespace utility {
namespace log {

/**
 * @brief Manages the starting and stopping of logging for an
 * application.
 */
class life_cycle_manager {
public:
    life_cycle_manager() = default;
    life_cycle_manager(const life_cycle_manager&) = default;
    ~life_cycle_manager() = default;
    life_cycle_manager(life_cycle_manager&&) = default;
    life_cycle_manager& operator=(const life_cycle_manager&) = default;

private:
    /**
     * @brief Creates a boost log file backend.
     */
    void create_file_backend(std::string file_name, severity_level severity);

    /**
     * @brief Creates a boost log console backend.
     */
    void create_console_backend(severity_level severity);

public:
    /**
     * @brief Initialise logging for the entire application.
     *
     * Must be done in a thread-safe context.
     */
    void initialise(std::string file_name,
        severity_level severity = severity_level::debug,
        bool log_to_console = false);

    /**
     * @brief Shutdown logging for the entire application.
     *
     * Should be done in a thread-safe context.
     */
    void shutdown();

private:
    static std::list<boost::shared_ptr<boost::log::core::sink_type> > sinks_;
};

} } }

#endif
