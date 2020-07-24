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
#ifndef DOGEN_TEMPLATING_TYPES_STITCH_PARSER_HPP
#define DOGEN_TEMPLATING_TYPES_STITCH_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <utility>
#include <boost/exception/info.hpp>
#include "dogen.identification/types/entities/tagged_value.hpp"
#include "dogen.templating/types/stitch/line.hpp"
#include "dogen.templating/types/stitch/block.hpp"
#include "dogen.templating/types/stitch/text_template_body.hpp"

namespace dogen::templating::stitch {

/**
 * @brief Provides line number information on errors.
 */
typedef boost::error_info<struct tag_line_number, std::string> error_at_line;

/**
 * @brief Converts a string that respects the grammer of a text
 * template into a object representation of the text template.
 */
class parser {
private:
    /**
     * @brief Creates a block with the supplied properties.
     */
    block create_block(const block_types bt, const std::string& c,
        const bool trim) const;

    /**
     * @brief Creates a block of type text.
     */
    block create_text_block(const std::string& c,
        const bool trim = false) const;

    /**
     * @brief Creates an expression block.
     */
    block create_expression_block(const std::string& c,
        const bool trim = false) const;

    /**
     * @brief Creates a standard control block.
     */
    block create_standard_control_block(const std::string& c,
        const bool trim = false) const;

private:
    /**
     * @brief Parses a line that contains an expression block.
     */
    line parse_expression_block(const std::string& input_line) const;

    /**
     * @brief Parses a line that contains an inline standard control
     * block.
     */
    line parse_inline_standard_control_block(
        const std::string& input_line) const;

    /**
     * @brief Parse a line with a directive into a tagged value.
     */
    identification::entities::tagged_value
    parse_directive(const std::string& input_line) const;

    /**
     * @brief Parse a line with a variable.
     */
    line parse_variable(const std::string& input_line) const;

public:
    /**
     * @brief Parse the string.
     */
    text_template_body parse(const std::string& s) const;
};

}

#endif
