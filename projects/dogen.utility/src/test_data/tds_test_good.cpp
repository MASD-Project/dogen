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
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/test_data.hpp"
#include "dogen/utility/test_data/tds_test_good.hpp"

using boost::filesystem::path;

namespace {

const path data_set("tds_test_good");
const path non_existent_file("tds_test_good/input/non_existent_file.dia");

const path input("tds_test_good/input");
const path input_non_empty_file_xml(
    "tds_test_good/input/non_empty_file.xml");
const path input_non_empty_file_txt(
    "tds_test_good/input/non_empty_file.txt");
const path input_file_1_xml("tds_test_good/input/file_1.xml");
const path input_empty_file_txt("tds_test_good/input/empty_file.txt");

const path actual("tds_test_good/actual");
const path actual_file_1_txt("tds_test_good/actual/file_1.txt");
const path actual_file_2_txt("tds_test_good/actual/file_2.txt");
const path actual_test_serializer_xmltst(
    "tds_test_good/actual/test_serializer.xmltst");
const path actual_test_serializer_2_xmltst(
    "tds_test_good/actual/test_serializer_2.xmltst");

const path actual_empty_file_txt("tds_test_good/actual/empty_file.txt");

const path expected("tds_test_good/expected");
const path expected_file_1_txt("tds_test_good/expected/file_1.txt");
const path expected_file_2_txt("tds_test_good/expected/file_2.txt");
const path expected_test_serializer_xmltst(
    "tds_test_good/expected/test_serializer.xmltst");
const path expected_test_serializer_2_xmltst(
    "tds_test_good/expected/test_serializer_2.xmltst");
const path expected_empty_file_txt("tds_test_good/expected/empty_file.txt");

}

namespace dogen {
namespace utility {
namespace test_data {

path tds_test_good::data_set() {
    return validating_resolver::resolve(::data_set);
}

path tds_test_good::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path tds_test_good::input() {
    return validating_resolver::resolve(::input);
}

path tds_test_good::input_non_empty_file_xml() {
    return validating_resolver::resolve(::input_non_empty_file_xml);
}

path tds_test_good::input_non_empty_file_txt() {
    return validating_resolver::resolve(::input_non_empty_file_txt);
}

path tds_test_good::input_file_1_xml() {
    return validating_resolver::resolve(::input_file_1_xml);
}

path tds_test_good::input_empty_file_txt() {
    return validating_resolver::resolve(::input_empty_file_txt);
}

path tds_test_good::expected() {
    return validating_resolver::resolve(::expected);
}

path tds_test_good::expected_file_1_txt() {
    return validating_resolver::resolve(::expected_file_1_txt);
}

path tds_test_good::expected_file_2_txt() {
    return validating_resolver::resolve(::expected_file_2_txt);
}

path tds_test_good::expected_test_serializer_xmltst() {
    return validating_resolver::resolve(::expected_test_serializer_xmltst);
}

path tds_test_good::expected_test_serializer_2_xmltst() {
    return resolver::resolve(::expected_test_serializer_2_xmltst);
}

path tds_test_good::expected_empty_file_txt() {
    return validating_resolver::resolve(::expected_empty_file_txt);
}

path tds_test_good::actual() {
    return validating_resolver::resolve(::actual);
}

path tds_test_good::actual_file_1_txt() {
    return validating_resolver::resolve(::actual_file_1_txt);
}

path tds_test_good::actual_file_2_txt() {
    return validating_resolver::resolve(::actual_file_2_txt);
}

path tds_test_good::actual_test_serializer_xmltst() {
    return resolver::resolve(::actual_test_serializer_xmltst);
}

path tds_test_good::actual_test_serializer_2_xmltst() {
    return resolver::resolve(::actual_test_serializer_2_xmltst);
}

path tds_test_good::actual_empty_file_txt() {
    return validating_resolver::resolve(::expected_empty_file_txt);
}

} } }
