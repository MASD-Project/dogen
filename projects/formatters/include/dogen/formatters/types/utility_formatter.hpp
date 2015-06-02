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
#ifndef DOGEN_FORMATTERS_TYPES_UTILITY_FORMATTER_HPP
#define DOGEN_FORMATTERS_TYPES_UTILITY_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include "dogen/formatters/types/quote_types.hpp"
#include "dogen/formatters/types/spacing_types.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Mixed grab-bag of formatting utilities.
 */
class utility_formatter {
public:
    explicit utility_formatter(std::ostream& s);

private:
    /**
     * @brief Inserts a quote to the stream.
     */
    void insert_quote(const quote_types qt) const;

    /**
     * @brief Escapes a quote.
     */
    std::string escape_quote(const std::string& s, const quote_types qt) const;

public:
    /**
     * @brief Insert content to stream, using the supplied space
     * flags.
     */
    void insert(const std::string& content,
        const spacing_types st = spacing_types::no_space) const;

    /**
     * @brief Inserts the content, but escapes any quotes.
     */
    void insert_escaped(const std::string& content_to_escape,
        const quote_types quote_to_escape = quote_types::double_quote,
        const spacing_types st = spacing_types::no_space) const;

    /**
     * @brief Quotes the supplied content.
     */
    void insert_quoted(const std::string& content_to_quote,
        const bool escape_content = false,
        const quote_types qt = quote_types::double_quote,
        const spacing_types st = spacing_types::no_space) const;

public:
    std::ostream& stream_;
};

} }

#endif
