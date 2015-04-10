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
#include <ostream>
#include "dogen/sml/io/model_io.hpp"
#include "dogen/config/io/cpp_options_io.hpp"
#include "dogen/dynamic/schema/io/repository_io.hpp"
#include "dogen/dynamic/expansion/io/expansion_context_io.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

std::ostream& operator<<(std::ostream& s, const expansion_context& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::dynamic::expansion::expansion_context\"" << ", "
      << "\"model\": " << v.model() << ", "
      << "\"repository\": " << v.repository() << ", "
      << "\"cpp_options\": " << v.cpp_options()
      << " }";
    return(s);
}

} } }