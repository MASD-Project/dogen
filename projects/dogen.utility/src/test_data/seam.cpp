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
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/seam.hpp"

using boost::filesystem::path;

namespace {

path data_set("seam");

path expected("seam/expected");
path expected_simple_template_stitch_cpp(
    "seam/expected/src/simple_template.cpp");
path expected_empty_template_stitch_cpp(
    "seam/expected/src/empty_template.cpp");
path expected_complex_template_stitch_cpp(
    "seam/expected/src/complex_template.cpp");

path actual("seam/actual");
path actual_simple_template_stitch_cpp(
    "seam/actual/src/simple_template.cpp");
path actual_empty_template_stitch_cpp(
    "seam/actual/src/empty_template.cpp");
path actual_complex_template_stitch_cpp(
    "seam/actual/src/complex_template.cpp");

}

namespace dogen {
namespace utility {
namespace test_data {

path seam::data_set() {
    return validating_resolver::resolve(::data_set);
}

path seam::expected() {
    return validating_resolver::resolve(::expected);
}

path seam::expected_simple_template_stitch_cpp() {
    return validating_resolver::resolve(::expected_simple_template_stitch_cpp);
}

path seam::expected_empty_template_stitch_cpp() {
    return validating_resolver::resolve(::expected_empty_template_stitch_cpp);
}

path seam::expected_complex_template_stitch_cpp() {
    return validating_resolver::resolve(::expected_complex_template_stitch_cpp);
}

path seam::actual() {
    return validating_resolver::resolve(::actual);
}

path seam::actual_simple_template_stitch_cpp() {
    return resolver::resolve(::actual_simple_template_stitch_cpp);
}

path seam::actual_empty_template_stitch_cpp() {
    return resolver::resolve(::actual_empty_template_stitch_cpp);
}

path seam::actual_complex_template_stitch_cpp() {
    return resolver::resolve(::actual_complex_template_stitch_cpp);
}

} } }
