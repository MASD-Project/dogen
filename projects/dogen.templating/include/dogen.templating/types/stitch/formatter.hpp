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
#ifndef DOGEN_TEMPLATING_TYPES_STITCH_FORMATTER_HPP
#define DOGEN_TEMPLATING_TYPES_STITCH_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen.extraction/types/meta_model/artefact.hpp"
#include "dogen.physical/types/location.hpp"
#include "dogen.templating/types/helpers/kvp_resolver.hpp"
#include "dogen.templating/types/stitch/line.hpp"
#include "dogen.templating/types/stitch/text_template.hpp"

namespace dogen::templating::stitch {

/**
 * @brief Format a text template into a file.
 */
class formatter final {
private:
    /**
     * @brief Formats a line with just a text block.
     */
    void format_text_block_line(
        const std::string& stream_name, const std::string& l,
        std::ostream& s) const;

    /**
     * @brief Formats a line with just an expression block.
     */
    void format_expression_block_line(const std::string& stream_name,
        const std::string& l, std::ostream& s) const;

    /**
     * @brief Formats a line with just a variable block.
     */
    void format_variable_block_line(const std::string& l,
        const helpers::kvp_resolver& rs, std::ostream& s) const;

    /**
     * @brief Formats a line with just a standard control block.
     */
    void format_standard_control_block_line(
        const std::string& l, std::ostream& s) const;

    /**
     * @brief Formats a line with mixed content.
     *
     * @pre Mixed content must be text blocks and expression blocks.
     */
    void format_mixed_content_line(const std::string& stream_name,
        const line& l, std::ostream& s) const;

    /**
     * @brief Formats a line with a single block.
     */
    void format_line_with_single_block(const std::string& stream_name,
        const line& l, const helpers::kvp_resolver& rs, std::ostream& s) const;

public:
    /**
     * @brief Archetype location for this formatter.
     */
    physical::location archetype_location() const;

    /**
     * @brief Formats the template into an artefact.
     */
    extraction::meta_model::artefact format(const text_template& tt) const;
};

}

#endif
