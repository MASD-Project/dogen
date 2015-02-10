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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/config/io/archive_types_io.hpp"
#include "dogen/config/io/troubleshooting_options_io.hpp"

namespace dogen {
namespace config {

std::ostream& operator<<(std::ostream& s, const troubleshooting_options& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::config::troubleshooting_options\"" << ", "
      << "\"debug_dir\": " << "\"" << v.debug_dir().generic_string() << "\"" << ", "
      << "\"save_dia_model\": " << v.save_dia_model() << ", "
      << "\"save_sml_model\": " << v.save_sml_model() << ", "
      << "\"stop_after_formatting\": " << v.stop_after_formatting() << ", "
      << "\"stop_after_merging\": " << v.stop_after_merging()
      << " }";
    return(s);
}

} }