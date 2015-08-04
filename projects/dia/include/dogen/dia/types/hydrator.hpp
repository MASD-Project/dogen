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
#ifndef DOGEN_DIA_TYPES_HYDRATOR_HPP
#define DOGEN_DIA_TYPES_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/utility/xml/text_reader.hpp"
#include "dogen/dia/types/diagram.hpp"
#include "dogen/dia/types/child_node.hpp"
#include "dogen/dia/types/connection.hpp"
#include "dogen/dia/types/object.hpp"

namespace dogen {
namespace dia {

class hydrator {
public:
    hydrator() = delete;
    hydrator(const hydrator&) = delete;
    ~hydrator() = default;
    hydrator(hydrator&&) = default;
    hydrator& operator=(const hydrator&) = delete;

public:
    hydrator(boost::filesystem::path file_name);

private:
    void validate_current_element(std::string name) const;
    void validate_self_closing() const;
    void next_element(std::string name);

private:
    bool is_attribute_value(std::string name) const;
    bool is_start_element(std::string element_name) const;
    bool is_end_element(std::string element_name) const;

private:
    std::string read_xml_string_attribute(std::string name);
    int read_xml_int_attribute(std::string name);
    bool read_xml_bool_attribute(std::string name);
    bool try_read_xml_bool_attribute(std::string name);

    child_node read_child_node();
    connection read_connection();
    std::vector<connection> read_connections();
    object read_object();
    template<typename AttributeValue> AttributeValue read_attribute_value();
    attribute read_attribute();
    layer read_layer();
    diagram_data read_diagram_data();
    diagram read_diagram();

public:
    diagram hydrate();

    /**
     * @brief Name of the file we are currently processing.
     */
    /**@{*/
    boost::filesystem::path file_name() const { return(file_name_); }
    void file_name(const boost::filesystem::path& value) { file_name_ = value; }
    /**@}*/

private:
    boost::filesystem::path file_name_;
    ::dogen::utility::xml::text_reader reader_;
};

} }

#endif
