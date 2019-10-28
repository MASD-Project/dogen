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
#include <sstream>
#include "dogen.relational/test_data/tracing/xml_td.hpp"
#include "dogen.relational/test_data/tracing/json_td.hpp"
#include "dogen.relational/test_data/tracing/model_td.hpp"
#include "dogen.relational/test_data/tracing/model_id_td.hpp"
#include "dogen.relational/test_data/tracing/model_type_td.hpp"
#include "dogen.relational/test_data/tracing/model_set_id_td.hpp"

namespace {

dogen::relational::tracing::json
create_dogen_relational_tracing_json(const unsigned int position) {
    return dogen::relational::tracing::json_generator::create(position);
}

dogen::relational::tracing::xml
create_dogen_relational_tracing_xml(const unsigned int position) {
    return dogen::relational::tracing::xml_generator::create(position);
}

dogen::relational::tracing::model_id
create_dogen_relational_tracing_model_id(const unsigned int position) {
    return dogen::relational::tracing::model_id_generator::create(position);
}

dogen::relational::tracing::model_set_id
create_dogen_relational_tracing_model_set_id(const unsigned int position) {
    return dogen::relational::tracing::model_set_id_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::relational::tracing::model_type
create_dogen_relational_tracing_model_type(const unsigned int position) {
    return dogen::relational::tracing::model_type_generator::create(position);
}

}

namespace dogen::relational::tracing {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.json_content(create_dogen_relational_tracing_json(position + 0));
    v.xml_content(create_dogen_relational_tracing_xml(position + 1));
    v.id(create_dogen_relational_tracing_model_id(position + 2));
    v.model_set_id(create_dogen_relational_tracing_model_set_id(position + 3));
    v.qualified_name(create_std_string(position + 4));
    v.qualified_meta_name(create_std_string(position + 5));
    v.type(create_dogen_relational_tracing_model_type(position + 6));
    v.source_file(create_std_string(position + 7));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

}
