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
#include "dogen/sml/test_data/concept_td.hpp"
#include "dogen/sml/test_data/model_element_td.hpp"
#include "dogen/sml/test_data/property_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"

namespace {

dogen::sml::property
create_dogen_sml_property(const unsigned int position) {
    return dogen::sml::property_generator::create(position);
}

std::vector<dogen::sml::property> create_std_vector_dogen_sml_property(unsigned int position) {
    std::vector<dogen::sml::property> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_property(position + i));
    }
    return r;
}

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

std::list<dogen::sml::qname> create_std_list_dogen_sml_qname(unsigned int position) {
    std::list<dogen::sml::qname> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_qname(position + i));
    }
    return r;
}

}

namespace dogen {
namespace sml {

concept_generator::concept_generator() : position_(0) { }

void concept_generator::
populate(const unsigned int position, result_type& v) {
    v.properties(create_std_vector_dogen_sml_property(position + 0));
    v.refines(create_std_list_dogen_sml_qname(position + 1));
}

concept_generator::result_type
concept_generator::create(const unsigned int position) {
    concept r;
    dogen::sml::model_element_generator::populate(position, r);
    concept_generator::populate(position, r);
    return r;
}
concept_generator::result_type*
concept_generator::create_ptr(const unsigned int position) {
    concept* p = new concept();
    concept_generator::populate(position, *p);
    return p;
}

concept_generator::result_type
concept_generator::operator()() {
    return create(position_++);
}

} }
