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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"
#include "dogen/sml/io/nested_qualified_name_io.hpp"
#include "dogen/sml/domain/nested_qualified_name.hpp"

namespace dogen {
namespace sml {

bool nested_qualified_name::operator==(const nested_qualified_name& rhs) const {
    return
        type_ == rhs.type_ &&
        children_ == rhs.children_;
}

void nested_qualified_name::to_stream(std::ostream& stream) const {
    stream << "\"nested_qualified_name\": {"
           << "\"type\":\"" << type_ << "\", "
           << "\"children\":" << children_
           << " }";
}

} }
