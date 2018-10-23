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
#include "dogen.modeling/io/meta_model/orm_database_systems_io.hpp"

namespace dogen::modeling::meta_model {

std::ostream& operator<<(std::ostream& s, const orm_database_systems& v) {
    s << "{ " << "\"__type__\": " << "\"orm_database_systems\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case orm_database_systems::invalid:
        attr = "\"invalid\"";
        break;
    case orm_database_systems::mysql:
        attr = "\"mysql\"";
        break;
    case orm_database_systems::postgresql:
        attr = "\"postgresql\"";
        break;
    case orm_database_systems::oracle:
        attr = "\"oracle\"";
        break;
    case orm_database_systems::sql_server:
        attr = "\"sql_server\"";
        break;
    case orm_database_systems::sqllite:
        attr = "\"sqllite\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for orm_database_systems");
    }
    s << attr << " }";
    return s;
}

}
