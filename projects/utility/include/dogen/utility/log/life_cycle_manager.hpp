/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
