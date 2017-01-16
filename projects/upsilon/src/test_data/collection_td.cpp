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
#include "dogen/upsilon/test_data/name_td.hpp"
#include "dogen/upsilon/test_data/type_td.hpp"
#include "dogen/upsilon/test_data/collection_td.hpp"

namespace {

dogen::upsilon::name
create_dogen_upsilon_name(const unsigned int position) {
    return dogen::upsilon::name_generator::create(position);
}

}

namespace dogen {
namespace upsilon {

collection_generator::collection_generator() : position_(0) { }

void collection_generator::
populate(const unsigned int position, result_type& v) {
    dogen::upsilon::type_generator::populate(position, v);
    v.type_name(create_dogen_upsilon_name(position + 0));
}

collection_generator::result_type
collection_generator::create(const unsigned int position) {
    collection r;
    collection_generator::populate(position, r);
    return r;
}

collection_generator::result_type*
collection_generator::create_ptr(const unsigned int position) {
    collection* p = new collection();
    collection_generator::populate(position, *p);
    return p;
}

collection_generator::result_type
collection_generator::operator()() {
    return create(position_++);
}

} }
