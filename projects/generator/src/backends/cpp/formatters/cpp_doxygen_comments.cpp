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
#include <string>
#include <sstream>
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen/generator/backends/cpp/formatters/cpp_doxygen_comments.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_doxygen_comments::
cpp_doxygen_comments(std::ostream& stream, cpp_indenter& indenter)
    : stream_(stream), indenter_(indenter) { }

void cpp_doxygen_comments::format(const std::string& documentation) {
    std::string trimmed(boost::algorithm::trim_copy(documentation));
    if (trimmed.empty())
        return;

    std::stringstream s(documentation);
    std::string line;
    bool is_first(true);
    stream_ << indenter_ << "/**" << std::endl;
    while(std::getline(s, line)) {
        boost::algorithm::trim_right(line);
        if (is_first)
            stream_ << indenter_ << " * @brief " << line << std::endl;
        else {
            trimmed = boost::algorithm::trim_copy(line);
            if (trimmed.empty())
                stream_ << indenter_ << " *" << std::endl;
            else
                stream_ << indenter_ << " * " << line << std::endl;
        }
        is_first = false;
    }
    stream_ << indenter_ << " */" << std::endl;
}

void cpp_doxygen_comments::format_inline(const std::string& documentation) {
    std::string trimmed(boost::algorithm::trim_copy(documentation));
    if (trimmed.empty())
        return;

    const auto s(boost::algorithm::trim_right_copy(documentation));
    stream_ << " ///< " << s;
}

void cpp_doxygen_comments::
format_start_block(const std::string& documentation) {
    std::string trimmed(boost::algorithm::trim_copy(documentation));
    if (trimmed.empty())
        return;

    stream_ << indenter_ << "/**@{*/" << std::endl;
}

void cpp_doxygen_comments::
format_end_block(const std::string& documentation) {
    std::string trimmed(boost::algorithm::trim_copy(documentation));
    if (trimmed.empty())
        return;

    stream_ << indenter_ << "/**@}*/" << std::endl;
}


} } } } }
