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
#ifndef DOGEN_STITCH_TYPES_TOKENIZER_HPP
#define DOGEN_STITCH_TYPES_TOKENIZER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/stitch/types/token_types.hpp"

namespace dogen {
namespace stitch {

class tokenizer {
public:
    tokenizer(const std::string& original_string);

private:
    bool handle_new_line();
    std::string obtain_current_line();
    bool handle_directive(const std::string& line);

public:
    bool advance();
    token_types current_token_type() const;
    std::string current_token_content() const;

private:
    const std::string& original_string_;
    token_types current_token_type_;
    std::string current_token_content_;
    unsigned int position_;
};

} }

#endif
