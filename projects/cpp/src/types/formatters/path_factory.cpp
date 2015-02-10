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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/io/formatters/file_types_io.hpp"
#include "dogen/cpp/types/formatters/building_error.hpp"
#include "dogen/cpp/types/formatters/path_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.path_factory"));
const std::string underscore("_");
const std::string dot(".");
const std::string unsupported_file_type("File type not supported: ");

}

namespace dogen {
namespace cpp {
namespace formatters {

boost::filesystem::path path_factory::
make_file_path(const path_ingredients& d, const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Creating file path for: "
                             << sml::string_converter::convert(qn);

    boost::filesystem::path r;

    const auto ft(d.file_type());
    switch (ft) {
    case file_types::cpp_header:
        if (d.split_project())
            r = d.include_directory();
        else {
            r = d.project_directory() / qn.model_name();
            r /= d.include_directory();
        }
        break;

    case file_types::cpp_implementation:
        if (d.split_project())
            r = d.source_directory();
        else {
            r = d.project_directory() / qn.model_name();
            r /= d.source_directory();
        }
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_file_type << ft;
        BOOST_THROW_EXCEPTION(building_error(unsupported_file_type +
                boost::lexical_cast<std::string>(ft)));
    }

    r /= make_include_path(d, qn);

    BOOST_LOG_SEV(lg, debug) << "File path: " << r;
    BOOST_LOG_SEV(lg, debug) << "Done creating file path for: "
                             << sml::string_converter::convert(qn);
    return r;
}

boost::filesystem::path path_factory::
make_include_path(const path_ingredients& d, const sml::qname& qn) const {
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

} } }
