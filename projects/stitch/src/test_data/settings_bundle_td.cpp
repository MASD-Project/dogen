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
#include "dogen/stitch/test_data/settings_bundle_td.hpp"
#include "dogen/stitch/test_data/stitching_settings_td.hpp"
#include "dogen/formatters/test_data/general_settings_td.hpp"

namespace {

dogen::formatters::general_settings
create_dogen_formatters_general_settings(const unsigned int position) {
    return dogen::formatters::general_settings_generator::create(position);
}

boost::optional<dogen::formatters::general_settings>
create_boost_optional_dogen_formatters_general_settings(unsigned int position) {
    boost::optional<dogen::formatters::general_settings> r(
        create_dogen_formatters_general_settings(position));
    return r;
}

dogen::stitch::stitching_settings
create_dogen_stitch_stitching_settings(const unsigned int position) {
    return dogen::stitch::stitching_settings_generator::create(position);
}

}

namespace dogen {
namespace stitch {

settings_bundle_generator::settings_bundle_generator() : position_(0) { }

void settings_bundle_generator::
populate(const unsigned int position, result_type& v) {
    v.general_settings(create_boost_optional_dogen_formatters_general_settings(position + 0));
    v.stitching_settings(create_dogen_stitch_stitching_settings(position + 1));
}

settings_bundle_generator::result_type
settings_bundle_generator::create(const unsigned int position) {
    settings_bundle r;
    settings_bundle_generator::populate(position, r);
    return r;
}
settings_bundle_generator::result_type*
settings_bundle_generator::create_ptr(const unsigned int position) {
    settings_bundle* p = new settings_bundle();
    settings_bundle_generator::populate(position, *p);
    return p;
}

settings_bundle_generator::result_type
settings_bundle_generator::operator()() {
    return create(position_++);
}

} }
