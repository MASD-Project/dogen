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
#ifndef DOGEN_TEXT_TYPES_FORMATTERS_DECORATION_FORMATTER_HPP
#define DOGEN_TEXT_TYPES_FORMATTERS_DECORATION_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker.hpp"
#include "dogen.text/types/formatters/comment_style.hpp"

namespace dogen::text::formatters {

/**
 * @brief Formats decorations into a stream.
 */
class decoration_formatter final {
private:
    /**
     * @brief Adds the formatted modeline to the content.
     */
    void add_modeline(std::list<std::string>& content,
        const boost::shared_ptr<logical::entities::decoration::modeline> ml
        ) const;

    /**
     * @brief Adds the formatted modeline to the content.
     */
    void add_marker(std::list<std::string>& content,
        const std::string& generation_timestamp,
        const std::string& origin_shah1_hash,
        const boost::shared_ptr<
        logical::entities::decoration::generation_marker> gm) const;

    /**
     * @brief Adds the copyright notices to the content.
     */
    void add_copyright_notices(std::list<std::string>& content,
        std::list<std::string> copyright_notices) const;

    /**
     * @brief Adds the licence text to the content.
     */
    void add_licence(std::list<std::string>& content,
        const std::string& licence_text) const;

public:
    void format_preamble(std::ostream& s, const comment_style& single_line_cs,
        const comment_style& multi_line_cs, const std::string& licence_text,
        const std::list<std::string>& copyright_notices,
        const std::string& generation_timestamp,
        const std::string& origin_shah1_hash,
        const boost::shared_ptr<
        logical::entities::decoration::modeline> ml, const
        boost::shared_ptr<
        logical::entities::decoration::generation_marker> gm) const;

    void format_preamble(std::ostream& s, const comment_style& cs,
        const std::string& licence_text,
        const std::list<std::string>& copyright_notices,
        const std::string& generation_timestamp,
        const std::string& origin_shah1_hash,
        const boost::shared_ptr<
        logical::entities::decoration::modeline> ml, const
        boost::shared_ptr<
        logical::entities::decoration::generation_marker> gm) const;

    void format_postamble(std::ostream& s, const comment_style& cs,
        const boost::shared_ptr<
        logical::entities::decoration::modeline> ml) const;
};

}

#endif
