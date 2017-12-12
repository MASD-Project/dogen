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
