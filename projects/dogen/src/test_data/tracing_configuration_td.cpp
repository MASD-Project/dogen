/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen/test_data/tracing_level_td.hpp"
#include "dogen/test_data/tracing_format_td.hpp"
#include "dogen/test_data/tracing_backend_td.hpp"
#include "dogen/test_data/tracing_configuration_td.hpp"

namespace {

dogen::tracing_level
create_dogen_tracing_level(const unsigned int position) {
    return dogen::tracing_level_generator::create(position);
}

dogen::tracing_format
create_dogen_tracing_format(const unsigned int position) {
    return dogen::tracing_format_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::tracing_backend
create_dogen_tracing_backend(const unsigned int position) {
    return dogen::tracing_backend_generator::create(position);
}

std::vector<std::string> create_std_vector_std_string(unsigned int position) {
    std::vector<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {

tracing_configuration_generator::tracing_configuration_generator() : position_(0) { }

void tracing_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.level(create_dogen_tracing_level(position + 0));
    v.format(create_dogen_tracing_format(position + 1));
    v.guids_enabled(create_bool(position + 2));
    v.logging_impact(create_std_string(position + 3));
    v.use_short_names(create_bool(position + 4));
    v.output_directory(create_boost_filesystem_path(position + 5));
    v.backend(create_dogen_tracing_backend(position + 6));
    v.run_id(create_std_string(position + 7));
    v.filter_regexes(create_std_vector_std_string(position + 8));
}

tracing_configuration_generator::result_type
tracing_configuration_generator::create(const unsigned int position) {
    tracing_configuration r;
    tracing_configuration_generator::populate(position, r);
    return r;
}

tracing_configuration_generator::result_type*
tracing_configuration_generator::create_ptr(const unsigned int position) {
    tracing_configuration* p = new tracing_configuration();
    tracing_configuration_generator::populate(position, *p);
    return p;
}

tracing_configuration_generator::result_type
tracing_configuration_generator::operator()() {
    return create(position_++);
}

}