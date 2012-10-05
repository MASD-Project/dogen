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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <ostream>
#include <string>
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"

namespace  {
const std::string one_indent("    ");
}


namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

void cpp_indenter::to_stream(std::ostream& stream) const {
    for (unsigned int i(0); i < indent_level_; ++i)
        stream << one_indent;
}

std::ostream& operator<<(std::ostream& stream, cpp_indenter indenter) {
    indenter.to_stream(stream);
    return stream;
}

} } } } }
