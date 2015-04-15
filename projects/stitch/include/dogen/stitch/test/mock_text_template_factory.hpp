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
    text_template make_text_template_with_trivial_settings() const;

    /**
     * @brief Makes a mixed content block with @code how_many text lines.
     */
    mixed_content_block make_text_only_mixed_content_block(
        const unsigned int how_many = 1) const;

    /**
     * @brief Makes a mixed content block with @code how_many lines of
     * mixed content. All lines have the following mix: text, text
     * with scriptlet, text.
     */
    mixed_content_block make_mixed_content_only_mixed_content_block(
        const unsigned int how_many = 1) const;

    /**
     * @brief Makes a scriptlet block with @code how_many lines.
     */
    scriptlet_block make_scriptlet_block(const unsigned int how_many = 1) const;

public:
    /**
     * @brief Creates a template with no content.
     */
    text_template make_empty_template() const;

    /**
     * @brief Creates a text template with a single text line.
     */
    text_template make_single_text_line() const;

    /**
     * @brief Creates a text template with @code how_many text lines.
     */
    text_template make_multiple_text_lines(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with a single-line scriptlet.
     */
    text_template make_single_line_scriptlet_block() const;

    /**
     * @brief Creates a text template with @code how_many scriptlet
     * lines.
     */
    text_template make_multi_line_scriptlet_block(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with text, followed by a
     * scriptlet, followed by text, all single lined.
     */
    text_template make_text_scriptlet_text_single_line() const;

    /**
     * @brief Creates a text template with scriptlet, followed by
     * text, followed scriptlet, all single lined.
     */
    text_template make_scriptlet_text_scriptlet_single_line() const;

    /**
     * @brief Creates a text template with text, followed by a
     * scriptlet, followed by text, all with @code how_many lines.
     */
    text_template make_text_scriptlet_text_multi_line(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template with scriptlet, followed by
     * text, followed by scriptlet, all with @code how_many lines.
     */
    text_template make_scriptlet_text_scriptlet_multi_line(
        const unsigned int how_many = 2) const;

    /**
     * @brief Creates a text template a mixed content block a mix of
     * text and scriptlet.
     */
    text_template make_mixed_content_single_line() const;

    /**
     * @brief Creates a text template a mixed content block a mix of
     * text and scriptlet. The block is composed of @code how_many
     * lines.
     */
    text_template make_mixed_content_multi_line(
        const unsigned int how_many = 2) const;

public:
    /**
     * @brief Creates a text template a complex structure: multi-line
     * text, followed by multi-line scriptlet, followed by mixed
     * content text, followed by followed by single-line scriptlet,
     * followed by single-line text.
     */
    text_template make_complex_structure() const;

    /**
     * @brief Populate general settings in the template. Also includes
     * a single line of text.
     */
    text_template make_with_general_settings() const;

private:
};

} } }

#endif
