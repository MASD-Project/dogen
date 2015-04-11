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
#include "dogen/stitch/test_data/block_td.hpp"
#include "dogen/stitch/test_data/text_template_td.hpp"
#include "dogen/dynamic/schema/test_data/object_td.hpp"

namespace {

dogen::dynamic::schema::object
create_dogen_dynamic_schema_object(const unsigned int position) {
    return dogen::dynamic::schema::object_generator::create(position);
}

dogen::stitch::block*
create_dogen_stitch_block_ptr(const unsigned int position) {
    return dogen::stitch::block_generator::create_ptr(position);
}

boost::shared_ptr<dogen::stitch::block>
create_boost_shared_ptr_dogen_stitch_block(unsigned int position) {
    boost::shared_ptr<dogen::stitch::block> r(
        create_dogen_stitch_block_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::stitch::block> > create_std_list_boost_shared_ptr_dogen_stitch_block_(unsigned int position) {
    std::list<boost::shared_ptr<dogen::stitch::block> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_stitch_block(position + i));
    }
    return r;
}

}

namespace dogen {
namespace stitch {

text_template_generator::text_template_generator() : position_(0) { }

void text_template_generator::
populate(const unsigned int position, result_type& v) {
    v.extensions(create_dogen_dynamic_schema_object(position + 0));
    v.content(create_std_list_boost_shared_ptr_dogen_stitch_block_(position + 1));
}

text_template_generator::result_type
text_template_generator::create(const unsigned int position) {
    text_template r;
    text_template_generator::populate(position, r);
    return r;
}
text_template_generator::result_type*
text_template_generator::create_ptr(const unsigned int position) {
    text_template* p = new text_template();
    text_template_generator::populate(position, *p);
    return p;
}

text_template_generator::result_type
text_template_generator::operator()() {
    return create(position_++);
}

} }
