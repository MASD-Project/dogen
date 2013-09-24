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
#ifndef DOGEN_DIA_TO_SML_TYPES_COMMENTS_PARSER_HPP
#define DOGEN_DIA_TO_SML_TYPES_COMMENTS_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Parses comments in dia diagrams.
 *
 * Comments can be stored in class objects, member functions, note
 * objects, etc.
 *
 * Any line starting with the well defined marker @e #DOGEN - known as
 * the opaque parameter marker - will be interpreted as carrying an
 * opaque parameter in a key-value pair form, where the key and the
 * value are separated by the assignment operator @e =.
 */
class comments_parser {
public:
    comments_parser() = default;
    comments_parser(const comments_parser&) = default;
    ~comments_parser() = default;
    comments_parser(comments_parser&&) = default;
    comments_parser& operator=(const comments_parser&) = default;

public:
    typedef std::list<std::pair<std::string, std::string> > kvp_container_type;

public:
    /**
     * @brief Parses a string carrying the comments in the dia object.
     *
     * Note that the @e # markers used by dia are expected to have
     * already been removed.
     *
     * @return pair where the first element contains all the text
     * which does not start with the opaque parameter marker, and the
     * second element is a key-value pair container with all of the
     * keys and values of the lines that start with the opaque
     * parameter marker.
     *
     * @pre lines starting with the opaque parameter marker must
     * follow the defined syntax or else a parsing_error is thrown.
     */
    std::pair<std::string, kvp_container_type>
    parse(const std::string& c) const;
};

} }

#endif
