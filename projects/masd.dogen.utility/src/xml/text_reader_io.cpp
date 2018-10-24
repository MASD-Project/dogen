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
#include <iomanip>
#include <boost/io/ios_state.hpp>
#include "masd.dogen.utility/xml/node_types_io.hpp"
#include "masd.dogen.utility/xml/text_reader_io.hpp"

namespace masd::dogen::utility::xml {

std::ostream& operator<<(std::ostream& stream, const text_reader& value) {
    boost::io::ios_flags_saver ifs(stream);

    stream << std::boolalpha;
    return stream << "\"text_reader\": {"
                  << "\"file_name\": \"" << value.file_name().string() << "\","
                  << "\"node_name\": \"" << value.name() << "\","
                  << "\"has_value\": " << value.has_value() << ","
                  << "\"value\": \"" << value.value_as_string() << "\","
                  << "\"type\": \"" << value.node_type() << "\""
                  << " }";
}

}
