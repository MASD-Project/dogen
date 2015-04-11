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
#include "dogen/utility/log/logger.hpp"

#include "dogen/stitch/types/parser.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.parser"));

const std::string start_scriptlet_block("<#+");
const std::string start_scriptlet_segment("<#=");
const std::string start_declaration("<#@");
// const std::string end_scriptlet_block("#>");
// const std::string end_scriptlet_segment("#>");
// const std::string end_declaration("#>");

}

namespace dogen {
namespace stitch {

bool parser::has_start_markers(const std::string& s) const {
    const auto npos(std::string::npos);
    return
        s.find_first_of(start_scriptlet_block) != npos ||
        s.find_first_of(start_scriptlet_segment) != npos ||
        s.find_first_of(start_declaration) != npos;
}

text_template parser::parse(const std::string& /*s*/) const {
    text_template r;
    return r;
}

} }
