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
#include "dogen/sml/test_data/type_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/enumerator_td.hpp"
#include "dogen/sml/test_data/enumeration_td.hpp"

namespace {

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

dogen::sml::enumerator
create_dogen_sml_enumerator(const unsigned int position) {
    return dogen::sml::enumerator_generator::create(position);
}

std::vector<dogen::sml::enumerator> create_std_vector_dogen_sml_enumerator(unsigned int position) {
    std::vector<dogen::sml::enumerator> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_sml_enumerator(position + i));
    }
    return r;
}

}

namespace dogen {
namespace sml {

enumeration_generator::enumeration_generator() : position_(0) { }

void enumeration_generator::
populate(const unsigned int position, result_type& v) {
    dogen::sml::type_generator::populate(position, v);
    v.underlying_type(create_dogen_sml_qname(position + 0));
    v.enumerators(create_std_vector_dogen_sml_enumerator(position + 1));
}

enumeration_generator::result_type
enumeration_generator::create(const unsigned int position) {
    enumeration r;
    enumeration_generator::populate(position, r);
    return r;
}
enumeration_generator::result_type*
enumeration_generator::create_ptr(const unsigned int position) {
    enumeration* p = new enumeration();
    enumeration_generator::populate(position, *p);
    return p;
}

enumeration_generator::result_type
enumeration_generator::operator()() {
    return create(position_++);
}

} }
