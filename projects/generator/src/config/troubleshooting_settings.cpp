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
#include "dogen/generator/config/troubleshooting_settings.hpp"

namespace dogen {
namespace generator {
namespace config {

std::ostream& operator<<(std::ostream& stream, troubleshooting_settings value) {
    boost::io::ios_flags_saver ifs(stream);
    stream << std::boolalpha;

    stream << "\"troubleshooting_settings\": { "
           << "\"verbose\": " << value.verbose() << ", "
           << "\"debug_dir\": " << value.debug_dir() << ", "
           << "\"save_dia_model\": " << value.save_dia_model() << ", "
           << "\"save_sml_model\": " << value.save_sml_model() << ", "
           << "\"stop_after_formatting\": "
           << value.stop_after_formatting() << ", "
           << "\"stop_after_merging\": " << value.stop_after_merging()
           << " }";

    return stream;
}

} } }
