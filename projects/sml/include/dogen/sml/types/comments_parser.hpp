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
#ifndef DOGEN_SML_TYPES_COMMENTS_PARSER_HPP
#define DOGEN_SML_TYPES_COMMENTS_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <utility>

namespace dogen {
namespace sml {

class comments_parser {
public:
    comments_parser() = default;
    comments_parser(const comments_parser&) = default;
    ~comments_parser() = default;
    comments_parser(comments_parser&&) = default;
    comments_parser& operator=(const comments_parser&) = default;

public:
    typedef std::vector<std::pair<std::string, std::string> > kvp_vector_type;

public:
    std::pair<std::string, kvp_vector_type> parse(const std::string& c) const;
};

} }

#endif
