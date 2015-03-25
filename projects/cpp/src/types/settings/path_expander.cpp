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
#include "dogen/dynamic/expansion/types/options_copier.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/dynamic/expansion/types/root_object_copier.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"
#include "dogen/cpp/io/formatters/file_types_io.hpp"
#include "dogen/cpp/types/settings/path_settings_factory.hpp"
#include "dogen/cpp/types/settings/path_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.path_expander"));

const std::string underscore("_");
const std::string dot(".");
const std::string unsupported_file_type("File type not supported: ");

const std::string expander_not_setup(
    "Attempt to expand without setting up expander");

}

namespace dogen {
namespace cpp {
namespace settings {

std::string path_expander::static_name() {
    static std::string name("cpp.path_expander");
    return name;
}

boost::filesystem::path path_expander::
make_file_path(const path_settings& ps, const sml::qname& qn) const {
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

        using dynamic::expansion::expansion_error;
        BOOST_THROW_EXCEPTION(expansion_error(unsupported_file_type +
                boost::lexical_cast<std::string>(ft)));
    }

    r /= make_include_path(ps, qn);

    BOOST_LOG_SEV(lg, debug) << "File path: " << r;
    BOOST_LOG_SEV(lg, debug) << "Done creating file path for: "
                             << sml::string_converter::convert(qn);
    return r;
}

boost::filesystem::path path_expander::
make_include_path(const path_settings& ps, const sml::qname& qn) const {
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

    if (!ps.facet_directory().empty())
        r /= ps.facet_directory();

    for(auto n : qn.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qn.simple_name();

    if (!ps.formatter_postfix().empty())
        stream << underscore << ps.formatter_postfix();

    if (!ps.facet_postfix().empty())
        stream << underscore << ps.facet_postfix();

    stream << dot << ps.extension();
    r /= stream.str();

    return r;
}

std::string path_expander::name() const {
    return static_name();
}

const std::forward_list<std::string>& path_expander::dependencies() const {
    using namespace dynamic::expansion;
    static std::forward_list<std::string> r {
        options_copier::static_name(),
        root_object_copier::static_name(),
    };

    return r;
}

void path_expander::setup(const dynamic::expansion::expansion_context& ec) {
    factory_ = std::make_shared<path_settings_factory>(
        ec.cpp_options(),
        ec.repository());
}

void path_expander::expand(const sml::qname& /*qn*/,
    const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& o) const {

    if (!factory_) {
        BOOST_LOG_SEV(lg, error) << expander_not_setup;

        using dynamic::expansion::expansion_error;
        BOOST_THROW_EXCEPTION(expansion_error(expander_not_setup));
    }

    /*const auto ps(*/factory_->make(o);
}

} } }
