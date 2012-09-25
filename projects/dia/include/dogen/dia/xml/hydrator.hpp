/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_XML_SERIALISER_HPP
#define DOGEN_DIA_XML_SERIALISER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/utility/xml/text_reader.hpp"
#include "dogen/dia/domain/diagram.hpp"

namespace dogen {
namespace dia {
namespace xml {

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
    bool is_attribute_value(std::string name) const;

    bool is_start_element(std::string element_name) const;
    bool is_end_element(std::string element_name) const;

    std::string read_xml_string_attribute(std::string name);
    int read_xml_int_attribute(std::string name);
    bool read_xml_bool_attribute(std::string name);
    bool try_read_xml_bool_attribute(std::string name);

    child_node read_child_node();
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

} } }

#endif
