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
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/stitch.hpp"

using boost::filesystem::path;

namespace {

path data_set("stitch");
path non_existent_file("stitch/input/non_existent_file.stitch");
path input("stitch/input");
path input_simple_template_stitch("stitch/input/simple_template.stitch");

path expected("stitch/expected");
path expected_simple_template_stitch_cpp(
    "stitch/expected/simple_template_stitch.cpp");

path actual(
    "stitch/actual");
path actual_simple_template_stitch_cpp(
    "stitch/actual/simple_template_stitch.cpp");

}

namespace dogen {
namespace utility {
namespace test_data {

path dia_sml::data_set() {
    return validating_resolver::resolve(::data_set);
}

path dia_sml::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path dia_sml::input() {
    return validating_resolver::resolve(::input);
}

path dia_sml::input_simple_template_stitch() {
    return validating_resolver::resolve(::input_simple_template_stitch);
}

path dia_sml::expected() {
    return validating_resolver::resolve(::expected);
}

path dia_sml::expected_simple_template_stitch_cpp() {
    return validating_resolver::resolve(::expected_simple_template_stitch_cpp);
}

path dia_sml::actual() {
    return validating_resolver::resolve(::actual);
}

path dia_sml::actual_simple_template_stitch_cpp() {
    return resolver::resolve(::actual_simple_template_stitch_cpp);
}

} } }
