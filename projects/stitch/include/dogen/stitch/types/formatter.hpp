/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_STITCH_TYPES_FORMATTER_HPP
#define DOGEN_STITCH_TYPES_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/formatters/types/file.hpp"
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/stitch/types/line.hpp"
#include "dogen/stitch/types/text_template.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Format a text template into a file.
 */
class formatter final {
private:
    /**
     * @brief Formats a line with just text.
     */
    void format_text_line(const std::string& stream_name, const std::string& l,
        std::ostream& s) const;

    /**
     * @brief Formats a line with just scriptlet.
     */
    void format_scriptlet_line(const std::string& l, std::ostream& s) const;

    /**
     * @brief Formats a line with mixed content.
     */
    void format_mixed_content_line(const std::string& stream_name,
        const line& l, std::ostream& s) const;

public:
    /**
     * @brief Ownership hierarchy for this formatter
     */
    dynamic::ownership_hierarchy ownership_hierarchy() const;

    /**
     * @brief Formats the text template.
     */
    dogen::formatters::file format(const text_template& tt) const;
};

} }

#endif
