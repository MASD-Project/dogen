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
#include <string>
#include <ostream>
#include <stdexcept>
#include "dogen.coding/io/meta_model/mapping/action_io.hpp"

namespace dogen::coding::meta_model::mapping {

std::ostream& operator<<(std::ostream& s, const action& v) {
    s << "{ " << "\"__type__\": " << "\"action\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case action::invalid:
        attr = "\"invalid\"";
        break;
    case action::translate:
        attr = "\"translate\"";
        break;
    case action::erase:
        attr = "\"erase\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for action");
    }
    s << attr << " }";
    return s;
}

}
