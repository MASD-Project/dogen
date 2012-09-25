/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_LOG_SCOPED_LIFE_CYCLE_MANAGER_HPP
#define DOGEN_UTILITY_LOG_SCOPED_LIFE_CYCLE_MANAGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/log/life_cycle_manager.hpp"

namespace dogen {
namespace utility {
namespace log {

class scoped_life_cycle_manager {
public:
    scoped_life_cycle_manager() = delete;
    scoped_life_cycle_manager(const scoped_life_cycle_manager&) = delete;
    scoped_life_cycle_manager(scoped_life_cycle_manager&&) = default;
    scoped_life_cycle_manager& operator=(const scoped_life_cycle_manager&) =
        delete;

public:
    scoped_life_cycle_manager(std::string file_name,
        severity_level severity = severity_level::debug,
        bool log_to_console = false);
    ~scoped_life_cycle_manager();

private:
    life_cycle_manager manager_;
};

} } }

#endif
