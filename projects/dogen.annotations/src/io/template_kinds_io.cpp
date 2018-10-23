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
#include "dogen.annotations/io/template_kinds_io.hpp"

namespace dogen::annotations {

std::ostream& operator<<(std::ostream& s, const template_kinds& v) {
    s << "{ " << "\"__type__\": " << "\"template_kinds\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case template_kinds::invalid:
        attr = "\"invalid\"";
        break;
    case template_kinds::instance:
        attr = "\"instance\"";
        break;
    case template_kinds::recursive_template:
        attr = "\"recursive_template\"";
        break;
    case template_kinds::backend_template:
        attr = "\"backend_template\"";
        break;
    case template_kinds::facet_template:
        attr = "\"facet_template\"";
        break;
    case template_kinds::archetype_template:
        attr = "\"archetype_template\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for template_kinds");
    }
    s << attr << " }";
    return s;
}

}
