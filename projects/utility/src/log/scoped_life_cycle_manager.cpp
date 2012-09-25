/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/log/scoped_life_cycle_manager.hpp"

namespace dogen {
namespace utility {
namespace log {

scoped_life_cycle_manager::scoped_life_cycle_manager(std::string file_name,
    severity_level severity, bool log_to_console) {
    manager_.initialise(file_name, severity, log_to_console);
}

scoped_life_cycle_manager::~scoped_life_cycle_manager() {
    manager_.shutdown();
}

} } }
