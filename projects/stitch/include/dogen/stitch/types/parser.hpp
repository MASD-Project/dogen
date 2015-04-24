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
#ifndef DOGEN_STITCH_TYPES_PARSER_HPP
#define DOGEN_STITCH_TYPES_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/stitch/types/text_template.hpp"
#include "dogen/dynamic/schema/types/workflow.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Converts a string that respects the grammer of a text
 * template into a object representation of the text template.
 */
class parser {
public:
    parser(const dynamic::schema::workflow& w, const bool use_new = false);

private:
    text_template parse_with_new(const std::string& s) const;
    text_template parse_with_legacy(const std::string& s) const;

public:
    /**
     * @brief Parse the string.
     */
    text_template parse(const std::string& s) const;

private:
    const dynamic::schema::workflow& schema_workflow_;
    const bool use_new_;
};

} }

#endif
