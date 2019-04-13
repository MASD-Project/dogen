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
#include "masd.dogen.variability/io/meta_model/configuration_io.hpp"
#include "masd.dogen.variability/io/meta_model/configuration_template_io.hpp"
#include "masd.dogen.variability/io/transforms/configuration_processing_io.hpp"

namespace masd::dogen::variability::transforms {

std::ostream& operator<<(std::ostream& s, const configuration_processing& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"masd::dogen::variability::transforms::configuration_processing\"" << ", "
      << "\"configuration_template\": " << v.configuration_template() << ", "
      << "\"configuration\": " << v.configuration() << ", "
      << "\"merged\": " << v.merged()
      << " }";
    return(s);
}

}
