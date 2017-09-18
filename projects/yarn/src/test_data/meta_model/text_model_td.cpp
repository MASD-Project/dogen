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
#include "dogen/formatters/test_data/artefact_td.hpp"
#include "dogen/yarn/test_data/meta_model/text_model_td.hpp"

namespace {

dogen::formatters::artefact
create_dogen_formatters_artefact(const unsigned int position) {
    return dogen::formatters::artefact_generator::create(position);
}

std::list<dogen::formatters::artefact> create_std_list_dogen_formatters_artefact(unsigned int position) {
    std::list<dogen::formatters::artefact> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_formatters_artefact(position + i));
    }
    return r;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::list<boost::filesystem::path> create_std_list_boost_filesystem_path(unsigned int position) {
    std::list<boost::filesystem::path> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_filesystem_path(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

text_model_generator::text_model_generator() : position_(0) { }

void text_model_generator::
populate(const unsigned int position, result_type& v) {
    v.artefacts(create_std_list_dogen_formatters_artefact(position + 0));
    v.managed_directories(create_std_list_boost_filesystem_path(position + 1));
}

text_model_generator::result_type
text_model_generator::create(const unsigned int position) {
    text_model r;
    text_model_generator::populate(position, r);
    return r;
}

text_model_generator::result_type*
text_model_generator::create_ptr(const unsigned int position) {
    text_model* p = new text_model();
    text_model_generator::populate(position, *p);
    return p;
}

text_model_generator::result_type
text_model_generator::operator()() {
    return create(position_++);
}

} } }
