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
#include "dogen/upsilon/types/hydrator.hpp"

namespace dogen {
namespace upsilon {

config hydrator::hydrate_config(boost::filesystem::path /*f*/) {
    config r;
    return r;
}

schema hydrator::hydrate_schema(boost::filesystem::path /*f*/) {
    schema r;
    return r;
}

type_information hydrator::
hydrate_type_information(boost::filesystem::path /*f*/) {
    type_information r;
    return r;
}

model hydrator::hydrate(boost::filesystem::path /*config_file*/) {
    model r;
    return r;
}

} }
