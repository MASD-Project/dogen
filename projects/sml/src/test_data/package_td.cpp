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
#include <sstream>
#include "dogen/sml/test_data/package_td.hpp"
#include "dogen/sml/test_data/qualified_name_td.hpp"

namespace {

dogen::sml::qualified_name
create_dogen_sml_qualified_name(const unsigned int position) {
    return dogen::sml::qualified_name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace sml {

package_generator::package_generator() : position_(0) { }

void package_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_sml_qualified_name(position + 0));
    v.documentation(create_std_string(position + 1));
}

package_generator::result_type
package_generator::create(const unsigned int position) {
    package r;
    package_generator::populate(position, r);
    return r;
}
package_generator::result_type*
package_generator::create_ptr(const unsigned int position) {
    package* p = new package();
    package_generator::populate(position, *p);
    return p;
}

package_generator::result_type
package_generator::operator()() {
    return create(position_++);
}

} }
