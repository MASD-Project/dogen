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
#ifndef DOGEN_CLI_TYPES_COMMAND_LINE_PARSER_HPP
#define DOGEN_CLI_TYPES_COMMAND_LINE_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <vector>
#include <string>
#include <boost/optional.hpp>
#include "dogen.cli/types/configuration.hpp"

namespace dogen::cli {

/**
 * @brief Interface for a command-line parser of the dogen options.
 */
class command_line_parser {
public:
    command_line_parser() = default;
    command_line_parser(const command_line_parser&) = delete;
    command_line_parser(command_line_parser&&) = delete;
    command_line_parser& operator=(const command_line_parser&) = delete;
    virtual ~command_line_parser() noexcept = default;

public:
    /**
     * @brief Transforms the supplied command line arguments into a dogen
     * configuration, if valid.
     *
     * @param arguments Command line arguments supplied by the user.
     * @param info stream in which to place informative text.
     * @param error stream in which to place errors.
     */
    virtual boost::optional<configuration>
    parse(const std::vector<std::string>& arguments, std::ostream& info,
        std::ostream& error) const = 0;
};

}

#endif
