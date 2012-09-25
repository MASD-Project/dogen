/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <sstream>
#include <ostream>
#include "dogen/generator/backends/cpp/formatters/cpp_utility.hpp"

namespace  {

const std::string member_variable_postfix("_");
const std::string open_bracket("{");
const std::string close_bracket("}");
const std::string quote_escaped("\\\"");
const std::string quote("\"");

const std::string public_access_specifier("public:");
const std::string private_access_specifier("private:");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

void cpp_utility::public_access_specifier() {
    cpp_negative_indenter_scope s(indenter_);
    stream_ << ::public_access_specifier << std::endl;
}

void cpp_utility::private_access_specifier() {
    cpp_negative_indenter_scope s(indenter_);
    stream_ << ::private_access_specifier << std::endl;
}

void cpp_utility::open_scope() {
    stream_ << open_bracket << std::endl;
}

void cpp_utility::close_scope() {
    stream_ << indenter_ << close_bracket << std::endl;
}

void cpp_utility::blank_line(unsigned int how_many) {
    for (unsigned int i(0); i < how_many; ++i)
        stream_ << std::endl;
}

std::string cpp_utility::as_member_variable(std::string property_name) const {
    return property_name + member_variable_postfix;
}

std::string cpp_utility::quote(std::string original) const {
    return ::quote + original + ::quote;
}

std::string cpp_utility::quote_escaped(std::string original) const {
    return ::quote_escaped + original + ::quote_escaped;
}

} } } } }
