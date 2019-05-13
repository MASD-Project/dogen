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
#ifndef DOGEN_CLI_TYPES_PROGRAM_OPTIONS_PARSER_HPP
#define DOGEN_CLI_TYPES_PROGRAM_OPTIONS_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.cli/types/command_line_parser.hpp"

namespace dogen::cli {

/**
 * Command-line parser implementation using boost program options.
 *
 * Note on logging: we are NOT logging any of the exceptions to the
 * log in this class. This is by design. The logger is only
 * initialised after the options have been parsed; were we to log
 * prior to this, we would dump all the messages into the console. The
 * output is very confusing users that are accustomed to normal
 * console applications.
 */
class program_options_parser final : public command_line_parser {
public:
    boost::optional<configuration>
    parse(const std::vector<std::string>& arguments, std::ostream& info,
        std::ostream& error) const override;
};

}

#endif
