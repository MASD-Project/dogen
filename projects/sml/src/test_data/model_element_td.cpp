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
#include "dogen/sml/test_data/entity_td.hpp"
#include "dogen/sml/test_data/factory_td.hpp"
#include "dogen/sml/test_data/model_element_td.hpp"
#include "dogen/sml/test_data/module_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/repository_td.hpp"
#include "dogen/sml/test_data/service_td.hpp"
#include "dogen/sml/test_data/value_td.hpp"

namespace {

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::vector<std::pair<std::string, std::string> > create_std_vector_std_pair_std_string_std_string_(unsigned int position) {
    std::vector<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace sml {


void model_element_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_sml_qname(position + 0));
    v.documentation(create_std_string(position + 1));
    v.implementation_specific_parameters(create_std_vector_std_pair_std_string_std_string_(position + 2));
    v.is_external(create_bool(position + 3));
}

model_element_generator::result_type*
model_element_generator::create_ptr(const unsigned int position) {
    if ((position % 5) == 0)
        return dogen::sml::value_generator::create_ptr(position);
    if ((position % 5) == 1)
        return dogen::sml::entity_generator::create_ptr(position);
    if ((position % 5) == 2)
        return dogen::sml::service_generator::create_ptr(position);
    if ((position % 5) == 3)
        return dogen::sml::factory_generator::create_ptr(position);
    if ((position % 5) == 4)
        return dogen::sml::repository_generator::create_ptr(position);
    return dogen::sml::module_generator::create_ptr(position);
}


} }
