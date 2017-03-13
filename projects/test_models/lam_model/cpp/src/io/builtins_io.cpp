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
#include "dogen/test_models/lam_model/io/builtins_io.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {

std::ostream& operator<<(std::ostream& s, const builtins& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::lam_model::builtins\"" << ", "
      << "\"prop_0\": " << "\"" << v.prop_0() << "\"" << ", "
      << "\"prop_1\": " << "\"" << v.prop_1() << "\"" << ", "
      << "\"prop_2\": " << "\"" << v.prop_2() << "\"" << ", "
      << "\"prop_3\": " << v.prop_3() << ", "
      << "\"prop_4\": " << v.prop_4() << ", "
      << "\"prop_5\": " << v.prop_5() << ", "
      << "\"prop_6\": " << v.prop_6() << ", "
      << "\"prop_7\": " << v.prop_7() << ", "
      << "\"prop_8\": " << v.prop_8() << ", "
      << "\"prop_9\": " << v.prop_9()
      << " }";
    return(s);
}

} } }
