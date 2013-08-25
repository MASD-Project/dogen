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
#include "dogen/om/test_data/odb_option_td.hpp"
#include "dogen/om/test_data/odb_options_file_td.hpp"
#include "dogen/om/test_data/text_file_td.hpp"

namespace {

dogen::om::odb_option*
create_dogen_om_odb_option_ptr(const unsigned int position) {
    return dogen::om::odb_option_generator::create_ptr(position);
}

boost::shared_ptr<dogen::om::odb_option>
create_boost_shared_ptr_dogen_om_odb_option(unsigned int position) {
    boost::shared_ptr<dogen::om::odb_option> r(
        create_dogen_om_odb_option_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::om::odb_option> > create_std_list_boost_shared_ptr_dogen_om_odb_option_(unsigned int position) {
    std::list<boost::shared_ptr<dogen::om::odb_option> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_om_odb_option(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om {

odb_options_file_generator::odb_options_file_generator() : position_(0) { }

void odb_options_file_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::text_file_generator::populate(position, v);
    v.features(create_std_list_boost_shared_ptr_dogen_om_odb_option_(position + 0));
}

odb_options_file_generator::result_type
odb_options_file_generator::create(const unsigned int position) {
    odb_options_file r;
    odb_options_file_generator::populate(position, r);
    return r;
}
odb_options_file_generator::result_type*
odb_options_file_generator::create_ptr(const unsigned int position) {
    odb_options_file* p = new odb_options_file();
    odb_options_file_generator::populate(position, *p);
    return p;
}

odb_options_file_generator::result_type
odb_options_file_generator::operator()() {
    return create(position_++);
}

} }
