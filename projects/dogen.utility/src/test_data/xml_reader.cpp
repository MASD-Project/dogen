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
#include "dogen/utility/test_data/test_data.hpp"
#include "dogen/utility/test_data/xml_reader.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/resolver.hpp"

using boost::filesystem::path;

namespace {

const path data_set("xml_reader");

const path input("xml_reader/input");
const path non_existent_file("xml_reader/input/non_existent_file.xml");
const path boolean_values("xml_reader/input/boolean_values.xml");
const path double_values("xml_reader/input/double_values.xml");
const path empty_file("xml_reader/input/empty_file.xml");
const path int_values("xml_reader/input/int_values.xml");
const path long_values("xml_reader/input/long_values.xml");
const path node_with_attributes("xml_reader/input/node_with_attributes.xml");
const path one_node_indented("xml_reader/input/one_node_indented.xml");
const path one_node_inlined("xml_reader/input/one_node_inlined.xml");
const path one_node_self_closing("xml_reader/input/one_node_self_closing.xml");
const path string_value_indented("xml_reader/input/string_value_indented.xml");
const path string_value_inlined("xml_reader/input/string_value_inlined.xml");
const path three_nested_elements("xml_reader/input/three_nested_elements.xml");
const path values_of_all_types("xml_reader/input/values_of_all_types.xml");
const path xml_declaration_one_node_indented(
    "xml_reader/input/xml_declaration_one_node_indented.xml");

const path expected("xml_reader/expected");
const path actual("xml_reader/actual");

}

namespace dogen {
namespace utility {
namespace test_data {

path xml_reader::data_set() {
    return validating_resolver::resolve(::data_set);
}

path xml_reader::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path xml_reader::input() {
    return validating_resolver::resolve(::input);
}

path xml_reader::input_boolean_values() {
    return validating_resolver::resolve(::boolean_values);
}

path xml_reader::input_double_values() {
    return validating_resolver::resolve(::double_values);
}

path xml_reader::input_empty_file() {
    return validating_resolver::resolve(::empty_file);
}

path xml_reader::input_int_values() {
    return validating_resolver::resolve(::int_values);
}

path xml_reader::input_long_values() {
    return validating_resolver::resolve(::long_values);
}

path xml_reader::input_node_with_attributes() {
    return validating_resolver::resolve(::node_with_attributes);
}

path xml_reader::input_one_node_indented() {
    return validating_resolver::resolve(::one_node_indented);
}

path xml_reader::input_one_node_inlined() {
    return validating_resolver::resolve(::one_node_inlined);
}

path xml_reader::input_one_node_self_closing() {
    return validating_resolver::resolve(::one_node_self_closing);
}

path xml_reader::input_string_value_indented() {
    return validating_resolver::resolve(::string_value_indented);
}

path xml_reader::input_string_value_inlined() {
    return validating_resolver::resolve(::string_value_inlined);
}

path xml_reader::input_three_nested_elements() {
    return validating_resolver::resolve(::three_nested_elements);
}

path xml_reader::input_values_of_all_types() {
    return validating_resolver::resolve(::values_of_all_types);
}

path xml_reader::input_xml_declaration_one_node_indented() {
    return validating_resolver::resolve(::xml_declaration_one_node_indented);
}

path xml_reader::expected() {
    return validating_resolver::resolve(::expected);
}

path xml_reader::actual() {
    return validating_resolver::resolve(::actual);
}

} } }
