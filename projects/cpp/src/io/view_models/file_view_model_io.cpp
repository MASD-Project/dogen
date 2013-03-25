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
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/cpp/io/aspect_types_io.hpp"
#include "dogen/cpp/io/file_types_io.hpp"
#include "dogen/cpp/io/view_models/class_view_model_io.hpp"
#include "dogen/cpp/io/view_models/enumeration_view_model_io.hpp"
#include "dogen/cpp/io/view_models/exception_view_model_io.hpp"
#include "dogen/cpp/io/view_models/file_view_model_io.hpp"
#include "dogen/cpp/io/view_models/registrar_view_model_io.hpp"
#include "dogen/sml/io/category_types_io.hpp"
#include "dogen/sml/io/meta_types_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::cpp::view_models::class_view_model>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s<< " }";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::cpp::view_models::enumeration_view_model>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s<< " }";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::cpp::view_models::exception_view_model>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s<< " }";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::cpp::view_models::registrar_view_model>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s<< " }";
    return s;
}

}


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace cpp {
namespace view_models {

std::ostream& operator<<(std::ostream& s, const file_view_model& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::view_models::file_view_model\"" << ", "
      << "\"facet_type\": " << v.facet_type() << ", "
      << "\"file_type\": " << v.file_type() << ", "
      << "\"aspect_type\": " << v.aspect_type() << ", "
      << "\"category_type\": " << v.category_type() << ", "
      << "\"meta_type\": " << v.meta_type() << ", "
      << "\"class_vm\": " << v.class_vm() << ", "
      << "\"enumeration_vm\": " << v.enumeration_vm() << ", "
      << "\"exception_vm\": " << v.exception_vm() << ", "
      << "\"registrar_vm\": " << v.registrar_vm() << ", "
      << "\"header_guard\": " << "\"" << tidy_up_string(v.header_guard()) << "\"" << ", "
      << "\"system_includes\": " << v.system_includes() << ", "
      << "\"user_includes\": " << v.user_includes() << ", "
      << "\"file_path\": " << "\"" << v.file_path().generic_string() << "\""
      << " }";
    return(s);
}

} } }