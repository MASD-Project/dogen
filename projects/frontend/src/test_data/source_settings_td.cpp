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
#include "dogen/frontend/test_data/source_settings_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace dogen {
namespace frontend {

source_settings_generator::source_settings_generator() : position_(0) { }

void source_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.save_pre_processed_input(create_bool(position + 0));
    v.pre_processed_input_path(create_boost_filesystem_path(position + 1));
    v.disable_model_module(create_bool(position + 2));
}

source_settings_generator::result_type
source_settings_generator::create(const unsigned int position) {
    source_settings r;
    source_settings_generator::populate(position, r);
    return r;
}
source_settings_generator::result_type*
source_settings_generator::create_ptr(const unsigned int position) {
    source_settings* p = new source_settings();
    source_settings_generator::populate(position, *p);
    return p;
}

source_settings_generator::result_type
source_settings_generator::operator()() {
    return create(position_++);
}

} }
