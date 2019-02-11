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
#include "masd.dogen.utility/types/test_data/resolver.hpp"
#include "masd.dogen.utility/types/test_data/validating_resolver.hpp"
#include "masd.dogen.utility/types/test_data/northwind.hpp"

using boost::filesystem::path;

namespace {

path data_set("northwind");
path non_existent_file("northwind/input/non_existent_file.northwind");
path input("northwind/input");
path input_northwind_ascii_sql("northwind/input/northwind_ascii.sql");

}

namespace masd::dogen::utility::test_data {

path northwind::data_set() {
    return validating_resolver::resolve(::data_set);
}

path northwind::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path northwind::input() {
    return validating_resolver::resolve(::input);
}

path northwind::input_northwind_ascii_sql() {
    return validating_resolver::resolve(::input_northwind_ascii_sql);
}


}
