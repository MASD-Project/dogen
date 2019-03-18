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
#include "masd.dogen.cli/test_data/cli_configuration_td.hpp"
#include "masd.dogen.cli/test_data/weaving_configuration_td.hpp"
#include "masd.dogen.cli/test_data/conversion_configuration_td.hpp"
#include "masd.dogen.cli/test_data/generation_configuration_td.hpp"

namespace {

masd::dogen::cli::generation_configuration
create_masd_dogen_cli_generation_configuration(const unsigned int position) {
    return masd::dogen::cli::generation_configuration_generator::create(position);
}

masd::dogen::cli::conversion_configuration
create_masd_dogen_cli_conversion_configuration(const unsigned int position) {
    return masd::dogen::cli::conversion_configuration_generator::create(position);
}

masd::dogen::cli::weaving_configuration
create_masd_dogen_cli_weaving_configuration(const unsigned int position) {
    return masd::dogen::cli::weaving_configuration_generator::create(position);
}

boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>
create_boost_variant_masd_dogen_cli_generation_configuration_masd_dogen_cli_conversion_configuration_masd_dogen_cli_weaving_configuration(unsigned int position) {
    boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration> r;

    if (position == 0 || ((position % 3) == 0))
        r = create_masd_dogen_cli_generation_configuration(position);
    else if (position == 1 || ((position % 4) == 0))
        r = create_masd_dogen_cli_conversion_configuration(position);
    else if ((position % 2) == 0)
        r = create_masd_dogen_cli_weaving_configuration(position);

    return r;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace masd::dogen::cli {

cli_configuration_generator::cli_configuration_generator() : position_(0) { }

void cli_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.activity(create_boost_variant_masd_dogen_cli_generation_configuration_masd_dogen_cli_conversion_configuration_masd_dogen_cli_weaving_configuration(position + 0));
    v.byproduct_directory(create_boost_filesystem_path(position + 1));
}

cli_configuration_generator::result_type
cli_configuration_generator::create(const unsigned int position) {
    cli_configuration r;
    cli_configuration_generator::populate(position, r);
    return r;
}

cli_configuration_generator::result_type*
cli_configuration_generator::create_ptr(const unsigned int position) {
    cli_configuration* p = new cli_configuration();
    cli_configuration_generator::populate(position, *p);
    return p;
}

cli_configuration_generator::result_type
cli_configuration_generator::operator()() {
    return create(position_++);
}

}
