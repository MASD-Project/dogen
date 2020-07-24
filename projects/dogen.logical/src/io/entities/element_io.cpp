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
#include <ostream>
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/label_io.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/io/entities/origin_types_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.identification/io/entities/stereotype_io.hpp"
#include "dogen.variability/io/entities/configuration_io.hpp"
#include "dogen.logical/io/entities/static_stereotypes_io.hpp"
#include "dogen.logical/io/entities/generability_status_io.hpp"
#include "dogen.logical/io/entities/decoration/element_properties_io.hpp"

namespace dogen::logical::entities {

std::ostream& operator<<(std::ostream& s, const element& v) {
    v.to_stream(s);
    return(s);
}

}
