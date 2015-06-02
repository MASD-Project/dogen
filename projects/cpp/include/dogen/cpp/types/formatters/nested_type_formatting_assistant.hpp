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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_NESTED_TYPE_FORMATTING_ASSISTANT_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_NESTED_TYPE_FORMATTING_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/cpp/types/formattables/nested_type_info.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Provides a number of utilities to formatters that generate
 * helper methods for nested types.
 */
class nested_type_formatting_assistant {
public:
    nested_type_formatting_assistant(std::ostream& s,
        const formattables::nested_type_info& nt);

public:
    /**
     * @brief Returns a scoped namespace formatter.
     */
    dogen::formatters::cpp::scoped_namespace_formatter
    make_scoped_namespace_formatter();

    /**
     * @brief Writes the string into the stream surrounded by quotes.
     */
    void quote(const std::string& s) const;

    /**
     * @brief Writes the string into the stream, first quoted and then
     * followed by escaped quotes.
     */
    void quote_and_quote_escaped(const std::string& s) const;

private:
    std::ostream& stream_;
    const formattables::nested_type_info& nested_type_;
};

} } }

#endif
