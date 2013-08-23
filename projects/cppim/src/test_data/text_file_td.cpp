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
#include "dogen/cppim/test_data/feature_td.hpp"
#include "dogen/cppim/test_data/text_file_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::cppim::feature*
create_dogen_cppim_feature_ptr(const unsigned int position) {
    return dogen::cppim::feature_generator::create_ptr(position);
}

boost::shared_ptr<dogen::cppim::feature>
create_boost_shared_ptr_dogen_cppim_feature(unsigned int position) {
    boost::shared_ptr<dogen::cppim::feature> r(
        create_dogen_cppim_feature_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::cppim::feature> > create_std_list_boost_shared_ptr_dogen_cppim_feature_(unsigned int position) {
    std::list<boost::shared_ptr<dogen::cppim::feature> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_cppim_feature(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cppim {

text_file_generator::text_file_generator() : position_(0) { }

void text_file_generator::
populate(const unsigned int position, result_type& v) {
    v.full_path(create_boost_filesystem_path(position + 0));
    v.relative_path(create_boost_filesystem_path(position + 1));
    v.features(create_std_list_boost_shared_ptr_dogen_cppim_feature_(position + 2));
}

text_file_generator::result_type
text_file_generator::create(const unsigned int position) {
    text_file r;
    text_file_generator::populate(position, r);
    return r;
}
text_file_generator::result_type*
text_file_generator::create_ptr(const unsigned int position) {
    text_file* p = new text_file();
    text_file_generator::populate(position, *p);
    return p;
}

text_file_generator::result_type
text_file_generator::operator()() {
    return create(position_++);
}

} }
