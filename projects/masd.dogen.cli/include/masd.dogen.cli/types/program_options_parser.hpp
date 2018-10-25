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
#ifndef MASD_DOGEN_CLI_TYPES_PROGRAM_OPTIONS_PARSER_HPP
#define MASD_DOGEN_CLI_TYPES_PROGRAM_OPTIONS_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "masd.dogen.cli/types/command_line_parser.hpp"

namespace masd::dogen::cli {

class program_options_parser final : public masd::dogen::cli::command_line_parser {
public:
    program_options_parser() = default;
    program_options_parser(const program_options_parser&) = default;
    program_options_parser(program_options_parser&&) = default;
    program_options_parser& operator=(const program_options_parser&) = default;

    virtual ~program_options_parser() noexcept { }

public:
    bool operator==(const program_options_parser& rhs) const;
    bool operator!=(const program_options_parser& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::cli::command_line_parser& other) const override;

};

}

#endif
