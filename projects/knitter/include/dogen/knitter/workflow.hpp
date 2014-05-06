/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2014 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_KNITTER_WORKFLOW_HPP
#define DOGEN_KNITTER_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen/config/types/settings.hpp"

namespace dogen {
namespace knitter {

/**
 * @brief Encapsulates the entire knitter tool workflow.
 */
class workflow {
private:
    /**
     * @brief Given the main arguments, generates the Dogen settings.
     */
    boost::optional<dogen::config::settings>
    generate_settings_activity(const int argc, const char* argv[]) const;

    /**
     * @brief Performs the initialisation of logging system.
     */
    void initialise_logging_activity(const dogen::config::settings& s) const;

    /**
     * @brief Executes the code generation workflow for the given the
     * application settings.
     */
     void knit_activity(const dogen::config::settings& s) const;

public:
    /**
     * @brief Executes the entire knitter workflow.
     *
     * @return false if the workflow failed for whatever reason, true
     * otherwise.
     */
    int execute(const int argc, const char* argv[]) const;
};

} }

#endif
