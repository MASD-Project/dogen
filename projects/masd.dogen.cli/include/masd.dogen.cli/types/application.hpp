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
#ifndef MASD_DOGEN_CLI_TYPES_APPLICATION_HPP
#define MASD_DOGEN_CLI_TYPES_APPLICATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <ostream>
#include "masd.dogen.cli/types/command_line_parser.hpp"

namespace masd::dogen::cli {

/**
 * Entry point for the dogen command line application.
 */
class application final {
public:
    application() = delete;
    application(const application&) = default;
    application(application&&) = default;
    ~application() = default;
    application& operator=(const application&) = delete;

public:
    application(const command_line_parser& clp);

private:
    /**
     * Executes the main workflow of the application.
     */
    void execute(const std::vector<std::string>& args,
        std::ostream& info, std::ostream& error) const;

public:
    /**
     * Executes the application and returns its exit code.
     *
     * @param args command line arguments.
     * @param info stream to use to output information.
     * @param error stream to use to output errors.
     */
    int run(const std::vector<std::string>& args,
        std::ostream& info, std::ostream& error) const;

private:
    const command_line_parser& command_line_parser_;
};

}

#endif
