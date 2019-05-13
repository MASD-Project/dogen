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
#ifndef DOGEN_UTILITY_TEST_DATA_XML_READER_HPP
#define DOGEN_UTILITY_TEST_DATA_XML_READER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen::utility::test_data {

/**
 * @brief Manages the location of all files in the XML Reader test
 * data set.
 */
class xml_reader {
public:
    xml_reader() = delete;
    xml_reader(const xml_reader&) = delete;
    ~xml_reader() = delete;
    xml_reader(xml_reader&&) = delete;
    xml_reader& operator=(const xml_reader&) = delete;

public:
    static boost::filesystem::path data_set();
    static boost::filesystem::path non_existent_file();

    static boost::filesystem::path input();
    static boost::filesystem::path input_boolean_values();
    static boost::filesystem::path input_double_values();
    static boost::filesystem::path input_empty_file();
    static boost::filesystem::path input_int_values();
    static boost::filesystem::path input_long_values();
    static boost::filesystem::path input_node_with_attributes();
    static boost::filesystem::path input_one_node_indented();
    static boost::filesystem::path input_one_node_inlined();
    static boost::filesystem::path input_one_node_self_closing();
    static boost::filesystem::path input_string_value_indented();
    static boost::filesystem::path input_string_value_inlined();
    static boost::filesystem::path input_three_nested_elements();
    static boost::filesystem::path input_values_of_all_types();
    static boost::filesystem::path input_xml_declaration_one_node_indented();

    static boost::filesystem::path expected();
    static boost::filesystem::path actual();
};

}

#endif
