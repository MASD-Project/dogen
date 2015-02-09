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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/io/formattables/file_properties_io.hpp"
#include "dogen/cpp/types/formatters/file_properties_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.file_properties_factory"));
const std::string underscore("_");
const std::string dot(".");

}

namespace dogen {
namespace cpp {
namespace formatters {

boost::filesystem::path file_properties_factory::
create_relative_path(const file_details& d, const sml::qname& qn) const {
    boost::filesystem::path r;

    if (d.split_project()) {
        for(auto n : qn.external_module_path())
            r /= n;

        r /= qn.model_name();
    } else if (d.file_type() == file_types::cpp_header) {
        for(auto n : qn.external_module_path())
            r /= n;
        r /= qn.model_name();
    }

    if (!d.facet_directory().empty())
        r /= d.facet_directory();

    for(auto n : qn.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qn.simple_name();

    if (!d.formatter_postfix().empty())
        stream << underscore << d.formatter_postfix();

    if (!d.facet_postfix().empty())
        stream << underscore << d.facet_postfix();

    stream << dot << d.extension();
    r /= stream.str();

    return r;
}

boost::filesystem::path file_properties_factory::
create_absolute_path(
    const file_details& /*d*/, const sml::qname& /*qn*/) const {
    boost::filesystem::path r;
    return r;
}

formattables::file_properties file_properties_factory::
make(const file_details& d, const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Creating file properties for: "
                             << sml::string_converter::convert(qn);

    formattables::file_properties r;
    r.relative_path(create_relative_path(d, qn));
    r.absolute_path(create_absolute_path(d, qn));

    BOOST_LOG_SEV(lg, debug) << "File properties: " << r;
    BOOST_LOG_SEV(lg, debug) << "Done creating file properties for: "
                             << sml::string_converter::convert(qn);

    return r;
}

} } }
