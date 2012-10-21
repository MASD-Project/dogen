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
#include "dogen/split_project/io/package/a_class_io.hpp"
#include "dogen/split_project/io/versioned_key_io.hpp"

namespace dogen {
namespace split_project {
namespace package {

std::ostream& operator<<(std::ostream& s, const a_class& v) {
    s << " { "
      << "\"__type__\": " << "\"a_class\"" << ", "
      << "\"versioned_key\": " << v.versioned_key()
      << " }";
    return(s);
}

} } }