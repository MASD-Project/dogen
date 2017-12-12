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
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/test_data/resolver.hpp"
#include "dogen.utility/test_data/validating_resolver.hpp"
#include "dogen.utility/test_data/test_data.hpp"
#include "dogen.utility/test_data/filesystem_tests.hpp"

using boost::filesystem::path;

namespace {

const path data_set("filesystem_tests");
const path non_existent_file("filesystem_tests/input/non_existent_file.dia");

const path input("filesystem_tests/input");
const path input_non_empty_file_txt(
    "filesystem_tests/input/non_empty_file.txt");
const path input_empty_file_txt("filesystem_tests/input/empty_file.txt");

const path actual("filesystem_tests/actual");
const path actual_some_file_txt("filesystem_tests/actual/some_file.txt");
const path actual_file_to_overwrite_txt(
    "filesystem_tests/actual/file_to_overwrite.txt");

const path expected("filesystem_tests/expected");
const path expected_some_file_txt("filesystem_tests/expected/some_file.txt");
const path expected_file_to_overwrite_txt(
    "filesystem_tests/expected/file_to_overwrite.txt");


}

namespace dogen {
namespace utility {
namespace test_data {

path filesystem_tests::data_set() {
    return validating_resolver::resolve(::data_set);
}

path filesystem_tests::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path filesystem_tests::input() {
    return validating_resolver::resolve(::input);
}

path filesystem_tests::input_non_empty_file_txt() {
    return validating_resolver::resolve(::input_non_empty_file_txt);
}

path filesystem_tests::input_empty_file_txt() {
    return validating_resolver::resolve(::input_empty_file_txt);
}

path filesystem_tests::expected() {
    return validating_resolver::resolve(::expected);
}

path filesystem_tests::expected_some_file_txt() {
    return validating_resolver::resolve(::expected_some_file_txt);
}

path filesystem_tests::expected_file_to_overwrite_txt() {
    return resolver::resolve(::actual_file_to_overwrite_txt);
}


path filesystem_tests::actual() {
    return validating_resolver::resolve(::actual);
}

path filesystem_tests::actual_some_file_txt() {
    return resolver::resolve(::actual_some_file_txt);
}

path filesystem_tests::actual_file_to_overwrite_txt() {
    return resolver::resolve(::actual_file_to_overwrite_txt);
}

} } }
