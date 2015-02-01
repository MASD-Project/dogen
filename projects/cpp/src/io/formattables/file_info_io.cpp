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
#include <boost/algorithm/string.hpp>
#include <ostream>
#include "dogen/cpp/io/formattables/content_descriptor_io.hpp"
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/io/formattables/file_info_io.hpp"
#include "dogen/cpp/io/formattables/includes_io.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::cpp::formattables::entity>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s<< " }";
    return s;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

std::ostream& operator<<(std::ostream& s, const file_info& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::file_info\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(v.documentation()) << "\"" << ", "
      << "\"includes\": " << v.includes() << ", "
      << "\"descriptor\": " << v.descriptor() << ", "
      << "\"header_guard\": " << "\"" << tidy_up_string(v.header_guard()) << "\"" << ", "
      << "\"file_path\": " << "\"" << v.file_path().generic_string() << "\"" << ", "
      << "\"relative_path\": " << "\"" << v.relative_path().generic_string() << "\"" << ", "
      << "\"entity\": " << v.entity()
      << " }";
    return(s);
}

} } }