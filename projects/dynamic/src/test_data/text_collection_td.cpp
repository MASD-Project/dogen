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
#include "dogen/dynamic/test_data/text_collection_td.hpp"
#include "dogen/dynamic/test_data/text_td.hpp"
#include "dogen/dynamic/test_data/value_td.hpp"

namespace {

dogen::dynamic::text
create_dogen_dynamic_text(const unsigned int position) {
    return dogen::dynamic::text_generator::create(position);
}

std::list<dogen::dynamic::text> create_std_list_dogen_dynamic_text(unsigned int position) {
    std::list<dogen::dynamic::text> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_dynamic_text(position + i));
    }
    return r;
}

}

namespace dogen {
namespace dynamic {

text_collection_generator::text_collection_generator() : position_(0) { }

void text_collection_generator::
populate(const unsigned int position, result_type& v) {
    dogen::dynamic::value_generator::populate(position, v);
    v.content(create_std_list_dogen_dynamic_text(position + 0));
}

text_collection_generator::result_type
text_collection_generator::create(const unsigned int position) {
    text_collection r;
    text_collection_generator::populate(position, r);
    return r;
}
text_collection_generator::result_type*
text_collection_generator::create_ptr(const unsigned int position) {
    text_collection* p = new text_collection();
    text_collection_generator::populate(position, *p);
    return p;
}

text_collection_generator::result_type
text_collection_generator::operator()() {
    return create(position_++);
}

} }
