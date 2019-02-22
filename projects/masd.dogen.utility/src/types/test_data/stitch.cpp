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
#include "masd.dogen.utility/types/test_data/resolver.hpp"
#include "masd.dogen.utility/types/test_data/validating_resolver.hpp"
#include "masd.dogen.utility/types/test_data/stitch.hpp"

using boost::filesystem::path;

namespace {

path data_set("stitch");
path non_existent_file("stitch/input/non_existent_file.stitch");
path input("stitch/input");
path input_simple_template_stitch("stitch/input/simple_template.stitch");
path input_empty_template_stitch("stitch/input/empty_template.stitch");
path input_complex_template_stitch("stitch/input/complex_template.stitch");

path expected("stitch/expected");
path expected_simple_template_stitch_cpp(
    "stitch/expected/simple_template.cpp");
path expected_empty_template_stitch_cpp(
    "stitch/expected/empty_template.cpp");
path expected_complex_template_stitch_cpp(
    "stitch/expected/complex_template.cpp");

path actual("stitch/actual");
path actual_simple_template_stitch_cpp(
    "stitch/actual/simple_template.cpp");
path actual_empty_template_stitch_cpp(
    "stitch/actual/empty_template.cpp");
path actual_complex_template_stitch_cpp(
    "stitch/actual/complex_template.cpp");

}

namespace masd::dogen::utility::test_data {

path stitch::data_set() {
    return validating_resolver::resolve(::data_set);
}

path stitch::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path stitch::input() {
    return validating_resolver::resolve(::input);
}

path stitch::input_simple_template_stitch() {
    return validating_resolver::resolve(::input_simple_template_stitch);
}

path stitch::input_empty_template_stitch() {
    return validating_resolver::resolve(::input_empty_template_stitch);
}

path stitch::input_complex_template_stitch() {
    return validating_resolver::resolve(::input_complex_template_stitch);
}

path stitch::expected_simple_template_stitch_cpp() {
    return validating_resolver::resolve(::expected_simple_template_stitch_cpp);
}

path stitch::expected_empty_template_stitch_cpp() {
    return validating_resolver::resolve(::expected_empty_template_stitch_cpp);
}

path stitch::expected_complex_template_stitch_cpp() {
    return validating_resolver::resolve(::expected_complex_template_stitch_cpp);
}

path stitch::actual() {
    return validating_resolver::resolve(::actual);
}

path stitch::actual_simple_template_stitch_cpp() {
    return resolver::resolve(::actual_simple_template_stitch_cpp);
}

path stitch::actual_empty_template_stitch_cpp() {
    return resolver::resolve(::actual_empty_template_stitch_cpp);
}

path stitch::actual_complex_template_stitch_cpp() {
    return resolver::resolve(::actual_complex_template_stitch_cpp);
}

}
