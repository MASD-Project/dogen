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
#include "dogen.relational/test_data/tracing/io_type_td.hpp"
#include "dogen.relational/test_data/tracing/model_id_td.hpp"
#include "dogen.relational/test_data/tracing/transform_id_td.hpp"
#include "dogen.relational/test_data/tracing/transform_model_td.hpp"

namespace {

dogen::relational::tracing::transform_id
create_dogen_relational_tracing_transform_id(const unsigned int position) {
    return dogen::relational::tracing::transform_id_generator::create(position);
}

dogen::relational::tracing::model_id
create_dogen_relational_tracing_model_id(const unsigned int position) {
    return dogen::relational::tracing::model_id_generator::create(position);
}

dogen::relational::tracing::io_type
create_dogen_relational_tracing_io_type(const unsigned int position) {
    return dogen::relational::tracing::io_type_generator::create(position);
}

}

namespace dogen::relational::tracing {

transform_model_generator::transform_model_generator() : position_(0) { }

void transform_model_generator::
populate(const unsigned int position, result_type& v) {
    v.transform_id(create_dogen_relational_tracing_transform_id(position + 0));
    v.model_id(create_dogen_relational_tracing_model_id(position + 1));
    v.type(create_dogen_relational_tracing_io_type(position + 2));
}

transform_model_generator::result_type
transform_model_generator::create(const unsigned int position) {
    transform_model r;
    transform_model_generator::populate(position, r);
    return r;
}

transform_model_generator::result_type*
transform_model_generator::create_ptr(const unsigned int position) {
    transform_model* p = new transform_model();
    transform_model_generator::populate(position, *p);
    return p;
}

transform_model_generator::result_type
transform_model_generator::operator()() {
    return create(position_++);
}

}
