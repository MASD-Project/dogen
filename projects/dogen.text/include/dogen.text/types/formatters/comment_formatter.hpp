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
#ifndef DOGEN_TEXT_TYPES_FORMATTERS_COMMENT_FORMATTER_HPP
#define DOGEN_TEXT_TYPES_FORMATTERS_COMMENT_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include "dogen.text/types/formatters/comment_style.hpp"

namespace dogen::text::formatters {

/**
 * @brief Formats input according to commenting options.
 */
class comment_formatter {
    comment_formatter(const comment_formatter&) = default;
    comment_formatter& operator=(const comment_formatter&) = delete;
    comment_formatter(comment_formatter&& rhs) = default;

public:
    /**
     * @brief Initialises formatter with default formatting
     * configuration.
     */
    comment_formatter();

    /**
     * @brief Initialises the formatter.
     *
     * @param start_on_first_line if false, a blank line will be
     * added. Otherwise content will start on the first line.
     * @param use_documentation_tool_markup if true, where applicable
     * formatter will decorate comments with documentation tool
     * markup.
     * @param documenting_previous_identifier if true, the comments refer to
     * an identifier already defined.
     * @param style type of commenting to use.
     * @param blank_trailing_line if true, a blank line will be added
     * at the end.
     */
    comment_formatter(
        const bool start_on_first_line,
        const bool use_documentation_tool_markup,
        const bool documenting_previous_identifier,
        const comment_style style,
        const bool last_line_is_blank);

private:
    /**
     * @brief Ensures formatter is in a valid state.
     */
    void validate() const;

private:
    /**
     * @brief Adds any documentation tool specific markers (if any) to
     * denote the start of the overview.
     */
    void add_start_overview(std::ostream& s) const;

    /**
     * @brief Adds any documentation tool specific markers (if any) to
     * denote the end of the overview.
     */
    void add_end_overview(std::ostream& s,
        const bool add_new_line = false) const;

    /**
     * @brief Adds any documentation tool specific markers (if any) to
     * denote the start of the body of the documentation.
     */
    void add_start_body(std::ostream& s) const;

    /**
     * @brief Adds any documentation tool specific markers (if any) to
     * denote the start of the body of the documentation.
     */
    void add_end_body(std::ostream& s) const;

private:
    /**
     * @brief Starts the comment block.
     */
    void add_comment_start_marker(std::ostream& s) const;

    /**
     * @brief Any line in the middle between start and end.
     */
    void add_comment_middle_marker(std::ostream& s) const;

    /**
     * @brief Ends the comment block.
     */
    void add_comment_end_marker(std::ostream& s) const;

    /**
     * @brief Generic method for adding doxygen blocks.
     */
    void format_doxygen_block(std::ostream& s, const std::string& block,
        const std::string& content) const;

public:
    /**
     * @brief Formats content as a comment into the stream.
     */
    void format(std::ostream& s, const std::string& content) const;

    /**
     * @brief Formats each entry in content into the stream as a
     * comment.
     *
     * If @e line_between_blocks is true, a new line is inserted in
     * between each entry of content.
     */
    void format(std::ostream& s, const std::list<std::string>& content,
        const bool line_between_blocks = false) const;

    /**
     * @brief Adds a doxygen block start to the stream if content is
     * not empty.
     */
    void format_doxygen_start_block(std::ostream& s,
        const std::string& content) const;

    /**
     * @brief Adds a doxygen block end to the stream if content is
     * not empty.
     */
    void format_doxygen_end_block(std::ostream& s,
        const std::string& content) const;

private:
    const bool start_on_first_line_;
    const bool use_documentation_tool_markup_;
    const bool documenting_previous_identifier_;
    const comment_style style_;
    const bool last_line_is_blank_;
};

}

#endif
