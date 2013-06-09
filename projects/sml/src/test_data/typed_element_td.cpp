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
#include "dogen/sml/test_data/entity_td.hpp"
#include "dogen/sml/test_data/factory_td.hpp"
#include "dogen/sml/test_data/model_element_td.hpp"
#include "dogen/sml/test_data/property_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/repository_td.hpp"
#include "dogen/sml/test_data/service_td.hpp"
#include "dogen/sml/test_data/typed_element_td.hpp"
#include "dogen/sml/test_data/value_td.hpp"

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

boost::optional<dogen::sml::qname>
create_boost_optional_dogen_sml_qname(unsigned int position) {
    boost::optional<dogen::sml::qname> r(
        create_dogen_sml_qname(position));
    return r;
}

std::list<dogen::sml::qname> create_std_list_dogen_sml_qname(unsigned int position) {
    std::list<dogen::sml::qname> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_qname(position + i));
    }
    return r;
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace sml {


void typed_element_generator::
populate(const unsigned int position, result_type& v) {
    dogen::sml::model_element_generator::populate(position, v);
    v.properties(create_std_vector_dogen_sml_property(position + 0));
    v.parent_name(create_boost_optional_dogen_sml_qname(position + 1));
    v.original_parent_name(create_boost_optional_dogen_sml_qname(position + 2));
    v.leaves(create_std_list_dogen_sml_qname(position + 3));
    v.number_of_type_arguments(create_unsigned_int(position + 4));
    v.is_parent(create_bool(position + 5));
    v.is_visitable(create_bool(position + 6));
    v.is_immutable(create_bool(position + 7));
    v.is_versioned(create_bool(position + 8));
    v.is_comparable(create_bool(position + 9));
    v.is_fluent(create_bool(position + 10));
    v.modeled_concepts(create_std_list_dogen_sml_qname(position + 11));
}

typed_element_generator::result_type*
typed_element_generator::create_ptr(const unsigned int position) {
    if ((position % 4) == 0)
        return dogen::sml::entity_generator::create_ptr(position);
    if ((position % 4) == 1)
        return dogen::sml::service_generator::create_ptr(position);
    if ((position % 4) == 2)
        return dogen::sml::factory_generator::create_ptr(position);
    if ((position % 4) == 3)
        return dogen::sml::repository_generator::create_ptr(position);
    return dogen::sml::value_generator::create_ptr(position);
}


} }
