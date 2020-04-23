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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.templating/types/helpers/stitch_template_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("templating.stitch.parser"));

const std::string equals("=");
const std::string space(" ");
const std::string start_expression_block_marker("<#=");
const std::string start_standard_control_block_marker("<#+");
const std::string start_directive_marker("<#@");
const std::string start_variable_marker("<#$");
const std::string end_block_marker("#>");

}

namespace dogen::templating::helpers {

stitch_template_builder::stitch_template_builder(std::ostream& os)
    : stream_(os) {}

void stitch_template_builder::
add_directive_block(const std::string& name, const std::string& value) {
    stream_ << start_directive_marker << space
            << name << equals << value << space
            << end_block_marker << std::endl;
}

void stitch_template_builder::
add_variable_block(const std::string& name) {
    stream_ << start_variable_marker << space
            << name << space
            << end_block_marker << std::endl;
}

void stitch_template_builder::add_expression_block(const std::string& expression) {
    stream_ << start_expression_block_marker << space
            << expression << space
            << end_block_marker << std::endl;
}

void stitch_template_builder::add_start_standard_control_block() {
    stream_ << start_standard_control_block_marker << std::endl;

}

void stitch_template_builder::add_end_standard_control_block() {
    stream_ << end_block_marker << std::endl;
}

}
