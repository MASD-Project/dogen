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
#include "masd.dogen.generation/test/mock_boilerplate_properties_factory.hpp"

namespace {

const std::string single_line_preamble(
    R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
)");

}

namespace masd::dogen::generation::test {

formatters::boilerplate_properties
mock_boilerplate_properties_factory::make_cpp_top_modeline_single_line() {
    formatters::boilerplate_properties r;

    r.preamble(single_line_preamble);
    r.generate_preamble(true);
    r.technical_space(coding::meta_model::technical_space::cpp);

    return r;
}

}
