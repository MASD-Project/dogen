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
#include <sstream>
#include "dogen/cpp/types/formatters/file_name_builder.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

file_name_builder::file_name_builder()
    : split_project_(false), file_type_(file_types::invalid) { }

file_name_builder& file_name_builder::split_project(bool v) {
    split_project_ = v;
    return *this;
}

file_name_builder& file_name_builder::file_type(file_types v) {
    file_type_ = v;
    return *this;
}

file_name_builder& file_name_builder::facet_directory(const std::string& v) {
    facet_directory_ = v;
    return *this;
}

file_name_builder& file_name_builder::facet_postfix(const std::string& v) {
    facet_postfix_ = v;
    return *this;
}

file_name_builder& file_name_builder::formatter_postfix(const std::string& v) {
    formatter_postfix_ = v;
    return *this;
}

file_name_builder& file_name_builder::extension(const std::string& v) {
    extension_ = v;
    return *this;
}

file_name_builder& file_name_builder::qname(const sml::qname& v) {
    qname_ = v;
    return *this;
}

boost::filesystem::path file_name_builder::build() const {
    boost::filesystem::path r;
    if (split_project_) {
        for(auto n : qname_.external_module_path())
            r /= n;

        r /= qname_.model_name();
    } else if (file_type_ == file_types::cpp_header) {
        for(auto n : qname_.external_module_path())
            r /= n;
        r /= qname_.model_name();
    }

    if (!facet_directory_.empty())
        r /= facet_directory_;

    for(auto n : qname_.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qname_.simple_name();

    if (!formatter_postfix_.empty())
        stream << "_" << formatter_postfix_;

    if (!facet_postfix_.empty())
        stream << "_" << facet_postfix_;

    stream << "." << extension_;

    r /= stream.str();

    return r;
}

} } }
