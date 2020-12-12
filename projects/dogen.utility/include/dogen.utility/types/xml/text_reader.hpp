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
#ifndef DOGEN_UTILITY_XML_TEXT_READER_HPP
#define DOGEN_UTILITY_XML_TEXT_READER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <utility>
#include <boost/filesystem/path.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/xml/exception.hpp"
#include "dogen.utility/types/xml/node_types.hpp"

namespace dogen::utility::xml {

/**
 * @brief Represents a reader that provides fast, non-cached,
 * forward-only access to XML data.
 */
class text_reader {
public:
    text_reader() = delete;
    text_reader& operator=(const text_reader&) = delete;
    text_reader(const text_reader&) = delete;
    text_reader(text_reader&&) = default;

public:
    /**
     * @brief Initialises the reader with a file name.
     * @param file_name path to the XML file the reader will open.
     * @param skip_whitespace if true, reads will skip whitespace
     */
    text_reader(const boost::filesystem::path& file_name,
        const bool skip_whitespace = false);

    /**
     * @brief Initialises the reader with a string.
     * @param skip_whitespace if true, reads will skip whitespace
     */
    text_reader(const std::string& content,
        const bool skip_whitespace = false);

    ~text_reader();

public:
    /**
     * @brief Ensures the current element has the expected name.
     */
    void validate_current_element(std::string name) const;

    /**
     * @brief Ensures the current element is self closing.
     */
    void validate_self_closing() const;

    /**
     * @brief Moves to the next element and ensures it has the
     * expected name.
     */
    void next_element(std::string name);

    /**
     * @brief Moves to the next element, which must exist.
     */
    void move_next();

    /**
     * @brief Returns true if the current node is the start of the
     * supplied element, false otherwise.
     */
    bool is_start_element(std::string element_name) const;

    /**
     * @brief Returns true if the current node is the end of the
     * supplied element, false otherwise.
     */
    bool is_end_element(std::string element_name) const;

    /**
     * @brief Returns true if the current element is a comment
     */
    bool is_comment() const;

public:
    /**
     * @brief Reads the next node from the stream.
     * @return True if there's more data to read, false otherwise.
     */
    bool read();

    /**
     * @brief Returns the type of the current node.
     */
    node_types node_type() const;

    /**
     * @brief Reads the value of the current node as a bool.
     */
    bool value_as_boolean() const;

    /**
     * @brief Reads the value of the current node as a double.
     */
    double value_as_double() const;

    /**
     * @brief Reads the value of the current node as an int.
     */
    int value_as_int() const;

    /**
     * @brief Reads the value of the current node as a long.
     */
    long value_as_long() const;

    /**
     * @brief Reads the value of the current node as a string.
     */
    std::string value_as_string() const;

    /**
     * @brief Template-based implementation of value method.
     */
    template<typename Type>
    Type value() const {
        using dogen::utility::xml::exception;
        BOOST_THROW_EXCEPTION(exception("Value not specialised for this type"));
    }

    /**
     * @brief Returns true if the current element has an attribute
     * with the specified name, false otherwise.
     */
    bool has_attribute(const std::string& name) const;

    /**
     * @brief Returns the value of the specified attribute as a string
     */
    std::string get_attribute_as_string(const std::string& name) const;

    /**
     * @brief Returns the value of the specified attribute as boolean
     */
    bool get_attribute_as_boolean(const std::string& name) const;

    /**
     * @brief Returns the value of the specified attribute as int
     */
    int get_attribute_as_int(const std::string& name) const;

    /**
     * @brief Template-based implementation of get_attribute method.
     */
    template<typename Type>
    Type get_attribute(const std::string&) const {
        using dogen::utility::xml::exception;
        BOOST_THROW_EXCEPTION(exception("Value not specialised for this type"));
    }

    /**
     * @brief Returns the name of the current node.
     */
    std::string name() const;

    /**
     * @brief Returns true if the current node can have a value, false
     * otherwise.
     */
    bool has_value() const;

    /**
     * @brief Returns true if the current node is self-closing.
     */
    bool is_empty() const;

    /**
     * @brief Returns true if the current node is the start of an
     * element.
     */
    bool is_start_element() const;

    /**
     * @brief Returns true if the current node is the end of an
     * element.
     */
    bool is_end_element() const;

    /**
     * @brief Skips the children of the current node
     * @return False if there are no more nodes to read, true otherwise.
     */
    bool skip() const;

    /**
     * @brief Returns true if the current node is a type of white space.
     */
    bool is_whitespace() const;

    /**
     * @brief Returns the file name the reader is currently processing.
     */
    boost::filesystem::path file_name() const { return file_name_; }

    /**
     * @brief Close the text reader. Once called the text reader
     * cannot be used again.
     */
    void close();

private:
    const boost::filesystem::path file_name_;
    const bool skip_whitespace_;

private: // pimpl
    class impl;
    std::unique_ptr<impl> impl_;
};

template<> inline std::string text_reader::value<std::string>() const {
    return value_as_string();
}

template<> inline int text_reader::value<int>() const {
    return value_as_int();
}

template<> inline long text_reader::value<long>() const {
    return value_as_long();
}

template<> inline double text_reader::value<double>() const {
    return value_as_double();
}

template<> inline bool text_reader::value<bool>() const {
    return value_as_boolean();
}

template<> inline std::string
text_reader::get_attribute<std::string>(const std::string& name) const {
    return get_attribute_as_string(name);
}

template<> inline bool
text_reader::get_attribute<bool>(const std::string& name) const {
    return get_attribute_as_boolean(name);
}

template<> inline int
text_reader::get_attribute<int>(const std::string& name) const {
    return get_attribute_as_int(name);
}

}

#endif
