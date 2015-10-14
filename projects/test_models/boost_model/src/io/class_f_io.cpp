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
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen/test_models/boost_model/io/class_f_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::gregorian::date>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << *i << "\"";
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::posix_time::ptime>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << *i << "\"";
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::posix_time::time_duration>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << *i << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

std::ostream& operator<<(std::ostream& s, const class_f& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::boost_model::class_f\"" << ", "
      << "\"prop_0\": " << "\"" << v.prop_0() << "\"" << ", "
      << "\"prop_1\": " << "\"" << v.prop_1() << "\"" << ", "
      << "\"prop_2\": " << "\"" << v.prop_2() << "\"" << ", "
      << "\"prop_3\": " << v.prop_3() << ", "
      << "\"prop_4\": " << v.prop_4() << ", "
      << "\"prop_5\": " << v.prop_5()
      << " }";
    return(s);
}

} } }
