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
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/sml/types/flat_name_builder.hpp"

namespace {

const std::string scope_operator("::");

}

namespace dogen {
namespace sml {

std::string flat_name_builder::
cpp_filename_for_qname(const boost::property_tree::ptree& meta_data,
    const bool is_header, const qname& qn,
    const std::string& facet_directory, const std::string& facet_postfix,
    const std::string& additional_postfix) const {

    meta_data_reader reader(meta_data);
    boost::filesystem::path r;
    if (reader.is_true(tags::cpp::split_project)) {
        for(auto n : qn.external_module_path())
            r /= n;
    }

    if (reader.is_true(tags::cpp::split_project))
        r /= qn.model_name();
    else if (is_header) {
        for(auto n : qn.external_module_path())
            r /= n;
        r /= qn.model_name();
    }

    if (reader.is_true(tags::cpp::enable_facet_folders))
        r /= facet_directory;

    for(auto n : qn.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qn.simple_name() << additional_postfix;

    if (reader.is_true(tags::cpp::enable_unique_file_names))
        stream << facet_postfix;

    if (is_header)
        stream << reader.get(tags::cpp::header_file_extension);
    else
        stream << reader.get(tags::cpp::implementation_file_extension);

    r /= stream.str();

    return r.generic_string();
}

std::string flat_name_builder::cpp_qualified_name(const sml::qname& qn) const {
    std::ostringstream s;

    if (!qn.model_name().empty())
        s << qn.model_name() << scope_operator;

    bool is_first(false);
    for (const auto& p : qn.module_path()) {
        if (is_first)
            s << scope_operator;
        s << p;
    }

    s << qn.simple_name();
    return s.str();
}

void flat_name_builder::
cpp_complete_name(const nested_qname& nqn, std::string& complete_name) const {
    const auto qualified_name(cpp_qualified_name(nqn.type()));
    const auto& children(nqn.children());
    complete_name += qualified_name;

    auto lambda([&](char c) {
            if (!children.empty()) {
                if (complete_name[complete_name.length() - 1] == c)
                    complete_name += " ";
                complete_name += c;
            }
        });

    lambda('<');
    bool is_first(true);
    for (const auto c : children) {
        if (!is_first)
            complete_name += ", ";

        cpp_complete_name(c, complete_name);
        is_first = false;
    }
    lambda('>');
}

} }
