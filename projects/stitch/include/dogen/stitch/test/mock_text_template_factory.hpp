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
#ifndef DOGEN_STITCH_MOCK_TEXT_TEMPLATE_FACTORY_HPP
#define DOGEN_STITCH_MOCK_TEXT_TEMPLATE_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/stitch/types/text_template.hpp"

namespace dogen {
namespace stitch {
namespace test {

/**
 * @brief Generates text templates for testing purposes.
 */
class mock_text_template_factory {
private:
    /**
     * @brief Creates an empty text template, with the exception of
     * the key settings.
     */
    text_template make_text_template_with_trivial_configuration() const;

    /**
     * @brief Makes @code how_many lines, each with a single text block.
     */
    std::list<line> make_text_block_only_lines(const unsigned int how_many = 1,
        const bool empty_content = false) const;

    /**
     * @brief Makes @code how_many lines, each with the following
     * composition: text block, expression block, text block.
     */
    std::list<line>
    make_mixed_content_lines(const unsigned int how_many = 1) const;

    /**
     * @brief Makes @code how_many lines with a single standard
     * control block.
     */
    std::list<line>
    make_standard_control_block_only_lines(
        const unsigned int how_many = 1) const;

    /**
     * @brief Makes @code how_many lines with a single expression block.
     */
    std::list<line>
    make_expression_block_only_lines(const unsigned int how_many = 1) const;

public:
    /**
     * @brief Creates a template with no content.
     */
    text_template make_empty_template() const;

    /**
     * @brief Creates a text template with a single line, composed of
     * a text block.
     */
    text_template make_single_text_block_line() const;

    /**
     * @brief Creates a text template with @code how_many lines, each
     * made up of a single text block.
     */
    text_template make_multiple_text_block_lines(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with one line composed of a
     * single-line expression block.
     */
    text_template make_single_expression_block_line() const;

    /**
     * @brief Creates a text template with @code how_many lines, each
     * made up of a single-line expression block.
     */
    text_template make_multiple_expression_block_lines(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with one line composed of a
     * single-line standard control block.
     */
    text_template make_single_standard_control_block_line() const;

    /**
     * @brief Creates a text template with @code how_many lines, each
     * made up of a single-line standard control block.
     */
    text_template make_multiple_standard_control_block_lines(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with three lines, each composed
     * of a single block. The blocks are as follows: a text block,
     * followed by a expression block, followed by a text block.
     */
    text_template make_text_expression_text_single_line() const;

    /**
     * @brief Creates a text template with three lines, each composed
     * of a single block. The blocks are as follows: an expression
     * block, followed by a text block, followed by an expression
     * block.
     */
    text_template make_expression_text_expression_single_line() const;

    /**
     * @brief Creates a text template with three "groups", each of
     * size @code how_many lines. Each group is composed of a text
     * block, followed by an expression block, followed by a text
     * block.
     */
    text_template make_text_expression_text_multi_line(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with three "groups", each of
     * size @code how_many lines. Each group is composed of an
     * expression block, followed by a text block, followed by an
     * expression block.
     */
    text_template make_expression_text_expression_multi_line(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with three lines, each composed
     * of a single block. The blocks are as follows: a text block,
     * followed by a standard control block, followed by a text block.
     */
    text_template make_text_standard_control_text_single_line() const;

    /**
     * @brief Creates a text template with three lines, each composed
     * of a single block. The blocks are as follows: a standard
     * control block, followed by a text block, followed by a standard
     * control block.
     */
    text_template
    make_standard_control_text_standard_control_single_line() const;

    /**
     * @brief Creates a text template with three "groups", each of
     * size @code how_many lines. Each group is composed of a text
     * block, followed by a standard control block, followed by a text
     * block.
     */
    text_template make_text_standard_control_text_multi_line(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with three "groups", each of
     * size @code how_many lines. Each group is composed of a standard
     * control block, followed by a text block, followed by a standard
     * control block.
     */
    text_template make_standard_control_text_standard_control_multi_line(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with a line that is composed of
     * a text block, followed by an expression block, followed by a
     * text block.
     */
    text_template make_mixed_content_single_line() const;

    /**
     * @brief Creates a text template with @code how_many lines,
     * composed of a text block, followed by an expression block,
     * followed by a text block.
     */
    text_template make_mixed_content_multi_line(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with a line composed of a text
     * block with single and double quotes.
     */
    text_template make_text_line_with_quotes() const;

public:
    /**
     * @brief Creates a text template a complex structure: multi-line
     * text blocks, followed by multi-line standard control blocks,
     * followed by several lines of mixed content (text blocks and
     * expression blocks in the same line), followed by followed by
     * single-line expression blocks, and finishing with a single-line
     * text block.
     */
    text_template make_complex_structure() const;

    /**
     * @brief Populate decoration configuration in the template. Also
     * includes a single line of text.
     */
    text_template make_with_decoration_configuration() const;

    /**
     * @brief Populate containing namespace in the text template.
     */
    text_template make_with_containing_namespace() const;

    /**
     * @brief Text template with lines that have empty text blocks.
     */
    text_template make_empty_text_lines(const unsigned int how_many = 2) const;

private:
};

} } }

#endif
