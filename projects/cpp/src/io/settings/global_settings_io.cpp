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
#include "dogen/cpp/io/settings/cpp_settings_io.hpp"
#include "dogen/cpp/io/settings/facet_settings_io.hpp"
#include "dogen/cpp/io/settings/formatter_settings_io.hpp"
#include "dogen/cpp/io/settings/global_settings_io.hpp"
#include "dogen/formatters/io/general_settings_io.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::cpp::settings::facet_settings>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::cpp::settings::formatter_settings>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen {
namespace cpp {
namespace settings {

std::ostream& operator<<(std::ostream& s, const global_settings& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::settings::global_settings\"" << ", "
      << "\"general_settings\": " << v.general_settings() << ", "
      << "\"cpp_settings\": " << v.cpp_settings() << ", "
      << "\"facet_settings\": " << v.facet_settings() << ", "
      << "\"formatter_settings\": " << v.formatter_settings()
      << " }";
    return(s);
}

} } }