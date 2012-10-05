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
#include <libxml/xmlreader.h>
#include <boost/lexical_cast.hpp>
#include <boost/scope_exit.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/xml/exception.hpp"
#include "dogen/utility/xml/text_reader.hpp"

namespace {

/**
 * @brief Performs initialisation and cleanup of the static state in
 * libxml.
 */
class libxml_scope_guard {
public:
    libxml_scope_guard() { xmlInitParser(); }
    ~libxml_scope_guard() { xmlCleanupParser(); }
};

libxml_scope_guard scope_guard;

// error codes
const int libxml_error_code(-1);

// error messages for exceptions
const std::string initialisation_error("Failed to initialise LibXml. File: ");
const std::string error_reading_node("Error reading node");
const std::string error_closing("Error closing text_reader");
const std::string error_getting_attribute("Error getting attribute: ");
const std::string error_has_value("Error checking if node has a text value");
const std::string error_skipping_children("Error skipping children in node");
const std::string error_file_not_found("File does not exist: ");
const std::string error_file_not_regular("File is not a regular file: ");
const std::string error_converting_bool("Error converting boolean value");
const std::string error_converting_double("Error converting double value");
const std::string error_converting_int("Error converting int value");
const std::string error_converting_long("Error converting long value");

// boolean values
const std::string bool_true("true");
const std::string bool_false("false");
const std::string bool_one("1");
const std::string bool_zero("0");

bool string_to_bool(std::string value) {
    if (boost::iequals(value, bool_true) || boost::iequals(value, bool_one))
        return true;

    if (boost::iequals(value, bool_false) || boost::iequals(value, bool_zero))
        return false;

    throw dogen::utility::xml::exception(error_converting_bool);
}

}

namespace dogen {
namespace utility {
namespace xml {

class text_reader::impl {
public:
    impl(std::string file_name);
    ~impl();

public:
    bool read();
    std::string value() const;
    void close();
    bool has_attribute(std::string name) const;
    std::string get_attribute(std::string name) const;
    std::string name() const;
    bool has_value() const;
    bool is_empty() const;
    node_types node_type() const;
    bool skip() const;

private:
    xmlTextReaderPtr reader_;
};

text_reader::impl::impl(std::string file_name)
    : reader_(xmlNewTextReaderFilename(file_name.c_str())) {
    if (reader_ == NULL) {
        using dogen::utility::xml::exception;
        throw exception(initialisation_error + file_name);
    }
}

text_reader::impl::~impl() {
    try {
        close();
    } catch (...) { }
    xmlFreeTextReader(reader_);
}

bool text_reader::impl::read() {
    const int ret(xmlTextReaderRead(reader_));
    if (ret == libxml_error_code)
        throw dogen::utility::xml::exception(error_reading_node);

    return ret != 0;
}

std::string text_reader::impl::value() const {
    char* value((char*) xmlTextReaderConstValue(reader_));
    return value != nullptr ? std::string(value) : std::string();
}

void text_reader::impl::close() {
    const int ret(xmlTextReaderClose(reader_));
    if (ret == libxml_error_code)
        throw dogen::utility::xml::exception(error_closing);
}

bool text_reader::impl::has_attribute(std::string name) const {
    xmlChar* value(xmlTextReaderGetAttribute(reader_, (xmlChar*)name.c_str()));

    BOOST_SCOPE_EXIT( (value) ) {
        xmlFree(value);
    } BOOST_SCOPE_EXIT_END;
    bool r(value != nullptr);
    return r;
}

std::string text_reader::impl::get_attribute(std::string name) const {
    xmlChar* value(xmlTextReaderGetAttribute(reader_, (xmlChar*)name.c_str()));

    BOOST_SCOPE_EXIT( (value) ) {
        xmlFree(value);
    } BOOST_SCOPE_EXIT_END;

    if (value == nullptr)
        throw dogen::utility::xml::exception(error_getting_attribute + name);

    const std::string ret((const char*)value);
    return ret;
}

std::string text_reader::impl::name() const {
    const char* name((const char*)(xmlTextReaderConstName(reader_)));
    return name != nullptr ? std::string(name) : std::string();
}

bool text_reader::impl::has_value() const {
    const int ret(xmlTextReaderHasValue(reader_));
    if (ret == libxml_error_code)
        throw dogen::utility::xml::exception(error_has_value);

    return ret != 0;
}

bool text_reader::impl::is_empty() const {
    const int ret(xmlTextReaderIsEmptyElement(reader_));
    if (ret == libxml_error_code)
        throw dogen::utility::xml::exception(error_has_value);

    return ret != 0;
}

node_types text_reader::impl::node_type() const {
    const int ret(xmlTextReaderNodeType(reader_));
    return (node_types)ret;
}

bool text_reader::impl::skip() const {
    const int ret(xmlTextReaderNext(reader_));
    if (ret == libxml_error_code)
        throw dogen::utility::xml::exception(error_skipping_children);
    return ret != 0;
}

text_reader::text_reader(boost::filesystem::path file_name,
    bool skip_whitespace)
    : file_name_(file_name),
      skip_whitespace_(skip_whitespace) {

    using dogen::utility::xml::exception;
    if (!boost::filesystem::exists(file_name))
        throw exception(error_file_not_found + file_name_.string());

    if (!boost::filesystem::is_regular_file(file_name))
        throw exception(error_file_not_regular + file_name_.string());

    impl_ = std::unique_ptr<impl>(new impl(file_name_.string()));
}

text_reader::~text_reader() {
    // required here due to uncomplete type in unique_ptr
}

bool text_reader::read() {
    if (!skip_whitespace_)
        return impl_->read();

    bool result(false);
    do {
        result = impl_->read();
    } while (result && is_whitespace());
    return result;
}

std::string text_reader::value_as_string() const {
    return impl_->value();
}

bool text_reader::value_as_boolean() const {
    return string_to_bool(value_as_string());
}

double text_reader::value_as_double() const {
    try {
        return boost::lexical_cast<double>(value_as_string());
    } catch (boost::bad_lexical_cast) {
        throw dogen::utility::xml::exception(error_converting_double);
    }
}

int text_reader::value_as_int() const {
    try {
        return boost::lexical_cast<int>(value_as_string());
    } catch (boost::bad_lexical_cast) {
        throw dogen::utility::xml::exception(error_converting_int);
    }
}

long text_reader::value_as_long() const {
    try {
        return boost::lexical_cast<long>(value_as_string());
    } catch (boost::bad_lexical_cast) {
        throw dogen::utility::xml::exception(error_converting_long);
    }
}

bool text_reader::has_attribute(std::string name) const {
    return impl_->has_attribute(name);
}

std::string text_reader::get_attribute_as_string(std::string name) const {
    return impl_->get_attribute(name);
}

bool text_reader::get_attribute_as_boolean(std::string name) const {
    return string_to_bool(get_attribute_as_string(name));
}

int text_reader::get_attribute_as_int(std::string name) const {
    try {
        return boost::lexical_cast<int>(get_attribute_as_string(name));
    } catch (boost::bad_lexical_cast) {
        throw dogen::utility::xml::exception(error_converting_int);
    }
}

std::string text_reader::name() const {
    return impl_->name();
}

bool text_reader::has_value() const {
    return impl_->has_value();
}

bool text_reader::is_empty() const {
    return impl_->is_empty();
}

node_types text_reader::node_type() const {
    return impl_->node_type();
}

bool text_reader::is_start_element() const {
    return node_type() == node_types::element;
}

bool text_reader::is_end_element() const {
    return node_type() == node_types::end_element;
}

bool text_reader::skip() const {
    if (!skip_whitespace_)
        return impl_->skip();

    bool result(false);
    do {
        result = impl_->skip();
    } while (result && is_whitespace());
    return result;
}

bool text_reader::is_whitespace() const {
    return
        node_type() == node_types::whitespace ||
        node_type() == node_types::significant_whitespace;
}

void text_reader::close() {
    return impl_->close();
}

} } }
