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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/io/formatters/file_types_io.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.path_derivatives_factory"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");
const std::string unsupported_file_type("File type not supported: ");

const std::string missing_path_settings(
    "Could not find any path settings for formatter: ");
const std::string empty_formatter_name("Empty formatter name was supplied.");
}

namespace dogen {
namespace cpp {
namespace formattables {

path_derivatives_factory::path_derivatives_factory(
    const sml::model& m,
    const std::unordered_map<std::string, settings::path_settings>& ps)
    : model_(m), path_settings_(ps) { }

boost::filesystem::path path_derivatives_factory::
make_inclusion_path(const settings::path_settings& ps,
    const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Creating inclusion path for: "
                             << sml::string_converter::convert(qn);

    boost::filesystem::path r;

    if (ps.split_project()) {
        for(auto n : qn.external_module_path())
            r /= n;

        r /= qn.model_name();
    } else if (ps.file_type() == formatters::file_types::cpp_header) {
        for(auto n : qn.external_module_path())
            r /= n;
        r /= qn.model_name();
    }

    if (!ps.facet_directory().empty() && !ps.disable_facet_directories())
        r /= ps.facet_directory();

    for(auto n : qn.module_path())
        r /= n;

    // modules other than the model module have simple names
    // contribute to the directories.
    if (qn != model_.name()) {
        const auto i(model_.modules().find(qn));
        if (i != model_.modules().end())
            r /= qn.simple_name();
    }

    std::ostringstream stream;
    stream << qn.simple_name();

    if (!ps.formatter_postfix().empty())
        stream << underscore << ps.formatter_postfix();

    if (!ps.facet_postfix().empty())
        stream << underscore << ps.facet_postfix();

    if (ps.file_type() == formatters::file_types::cpp_header)
        stream << dot << ps.header_file_extension();
    else if (ps.file_type() == formatters::file_types::cpp_implementation)
        stream << dot << ps.implementation_file_extension();

    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Done creating inclusion path. Result: " << r;
    return r;
}

boost::filesystem::path path_derivatives_factory::
make_file_path(const settings::path_settings& ps,
    const boost::filesystem::path& inclusion_path,
    const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Creating file path for: "
                             << sml::string_converter::convert(qn);

    boost::filesystem::path r;

    const auto ft(ps.file_type());
    switch (ft) {
    case formatters::file_types::cpp_header:
        if (ps.split_project())
            r = ps.include_directory_path();
        else {
            r = ps.project_directory_path() / qn.model_name();
            r /= ps.include_directory_name();
        }
        break;

    case formatters::file_types::cpp_implementation:
        if (ps.split_project())
            r = ps.source_directory_path();
        else {
            r = ps.project_directory_path() / qn.model_name();
            r /= ps.source_directory_name();
        }
        break;

    default:
        BOOST_LOG_SEV(lg, error) << unsupported_file_type << ft;

        BOOST_THROW_EXCEPTION(building_error(unsupported_file_type +
                boost::lexical_cast<std::string>(ft)));
    }

    r /= inclusion_path;

    BOOST_LOG_SEV(lg, debug) << "Done creating file path. Result: " << r;
    return r;
}

std::string path_derivatives_factory::
to_inclusion_directive(const boost::filesystem::path& p) const {
    std::ostringstream ss;
    ss << double_quote << p.generic_string() << double_quote;
    return ss.str();
}

std::string path_derivatives_factory::
to_header_guard_name(const boost::filesystem::path& p) const {
    bool is_first(true);
    std::ostringstream ss;
    for (const auto& token : p) {
        std::string s(token.string());
        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        ss << (is_first ? empty : separator) << s;
        is_first = false;
    }
    return ss.str();
}

std::unordered_map<std::string, path_derivatives> path_derivatives_factory::
make(const sml::qname& qn) const {
    std::unordered_map<std::string, path_derivatives> r;

    for (const auto& pair : path_settings_) {
        if (pair.first.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        const auto& s(pair.second);
        const auto inclusion_path(make_inclusion_path(s, qn));

        path_derivatives pd;
        const auto file_path(make_file_path(s, inclusion_path, qn));
        pd.file_path(file_path);

        if (s.file_type() == formatters::file_types::cpp_header) {
            pd.inclusion_directive(to_inclusion_directive(inclusion_path));
            pd.header_guard(to_header_guard_name(inclusion_path));
        }

        r[pair.first] = pd;
    }
    return r;
}

} } }
