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
#include "masd.dogen.extraction/test_data/meta_model/model_td.hpp"
#include "masd.dogen.extraction/test_data/meta_model/artefact_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "masd.dogen.extraction/test_data/meta_model/outputting_properties_td.hpp"

namespace {

masd::dogen::variability::meta_model::configuration*
create_masd_dogen_variability_meta_model_configuration_ptr(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::variability::meta_model::configuration>
create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(unsigned int position) {
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration> r(
        create_masd_dogen_variability_meta_model_configuration_ptr(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::extraction::meta_model::artefact
create_masd_dogen_extraction_meta_model_artefact(const unsigned int position) {
    return masd::dogen::extraction::meta_model::artefact_generator::create(position);
}

std::list<masd::dogen::extraction::meta_model::artefact> create_std_list_masd_dogen_extraction_meta_model_artefact(unsigned int position) {
    std::list<masd::dogen::extraction::meta_model::artefact> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_extraction_meta_model_artefact(position + i));
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

masd::dogen::extraction::meta_model::outputting_properties
create_masd_dogen_extraction_meta_model_outputting_properties(const unsigned int position) {
    return masd::dogen::extraction::meta_model::outputting_properties_generator::create(position);
}

}

namespace masd::dogen::extraction::meta_model {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.configuration(create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(position + 0));
    v.name(create_std_string(position + 1));
    v.technical_space(create_std_string(position + 2));
    v.artefacts(create_std_list_masd_dogen_extraction_meta_model_artefact(position + 3));
    v.managed_directories(create_std_list_boost_filesystem_path(position + 4));
    v.outputting_properties(create_masd_dogen_extraction_meta_model_outputting_properties(position + 5));
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
