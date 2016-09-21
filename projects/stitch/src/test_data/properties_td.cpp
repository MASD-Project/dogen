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
#include "dogen/stitch/test_data/properties_td.hpp"
#include "dogen/stitch/test_data/stitching_settings_td.hpp"
#include "dogen/formatters/test_data/decoration_configuration_td.hpp"

namespace {

dogen::formatters::decoration_configuration
create_dogen_formatters_decoration_configuration(const unsigned int position) {
    return dogen::formatters::decoration_configuration_generator::create(position);
}

boost::optional<dogen::formatters::decoration_configuration>
create_boost_optional_dogen_formatters_decoration_configuration(unsigned int position) {
    boost::optional<dogen::formatters::decoration_configuration> r(
        create_dogen_formatters_decoration_configuration(position));
    return r;
}

dogen::stitch::stitching_settings
create_dogen_stitch_stitching_settings(const unsigned int position) {
    return dogen::stitch::stitching_settings_generator::create(position);
}

}

namespace dogen {
namespace stitch {

properties_generator::properties_generator() : position_(0) { }

void properties_generator::
populate(const unsigned int position, result_type& v) {
    v.decoration_configuration(create_boost_optional_dogen_formatters_decoration_configuration(position + 0));
    v.stitching_settings(create_dogen_stitch_stitching_settings(position + 1));
}

properties_generator::result_type
properties_generator::create(const unsigned int position) {
    properties r;
    properties_generator::populate(position, r);
    return r;
}

properties_generator::result_type*
properties_generator::create_ptr(const unsigned int position) {
    properties* p = new properties();
    properties_generator::populate(position, *p);
    return p;
}

properties_generator::result_type
properties_generator::operator()() {
    return create(position_++);
}

} }
