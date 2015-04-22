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
#include "dogen/stitch/types/builder.hpp"

namespace dogen {
namespace stitch {

builder::builder() : in_standard_control_block_(false),
                     in_expression_control_block_(false),
                     in_directive_(false) {}

void builder::start_standard_control_block() {
    in_standard_control_block_ = true;
}

void builder::start_expression_control_block() {
    in_expression_control_block_ = true;
}

void builder::start_directive() {
    in_directive_ = true;
}

void builder::add_content(const std::string& /*content*/) {
    // std::string input_line;
    // std::istringstream is(content);
    // while (std::getline(is, input_line)) {
    //     line l;
    //     if (in_standard_control_block_) {
    //     }
    // }
}

void builder::end_control_block() {
    in_standard_control_block_ = false;
    in_expression_control_block_ = false;
    in_directive_ = false;
}

text_template builder::build() {
    return text_template_;
}

} }
