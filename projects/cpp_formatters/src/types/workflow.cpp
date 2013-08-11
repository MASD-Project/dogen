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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/io/content_descriptor_io.hpp"
#include "dogen/cpp_formatters/types/factory.hpp"
#include "dogen/cpp_formatters/types/file_formatter.hpp"
#include "dogen/cpp_formatters/types/src_cmakelists.hpp"
#include "dogen/cpp_formatters/types/include_cmakelists.hpp"
#include "dogen/cpp_formatters/types/odb_options.hpp"
#include "dogen/cpp_formatters/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.workflow"));

const std::string includer_name("all");

}

namespace dogen {
namespace cpp_formatters {

workflow::
workflow(const config::cpp_settings& settings) : settings_(settings) { }

workflow::result_type
workflow::format_cmakelists_activity(const cpp::project& p) const {
    const auto src_path(p.src_cmakelists().file_path());
    BOOST_LOG_SEV(lg, debug) << "Formatting: " << src_path.string();

    std::ostringstream s;
    cpp_formatters::src_cmakelists f(s);
    f.format(p.src_cmakelists());

    workflow::result_type r;
    r.insert(std::make_pair(src_path, s.str()));

    if (p.include_cmakelists()) {
        const auto f(settings_.enabled_facets());
        const bool odb_enabled(f.find(config::cpp_facet_types::odb) != f.end());
        s.str("");

        cpp_formatters::include_cmakelists inc(s, odb_enabled,
            settings_.odb_facet_folder());
        inc.format(*p.include_cmakelists());

        const auto inc_path(p.include_cmakelists()->file_path());
        BOOST_LOG_SEV(lg, debug) << "Formatting: " << inc_path.string();
        r.insert(std::make_pair(inc_path, s.str()));
    }

    return r;
}

workflow::result_entry_type
workflow::format_odb_options_activity(const cpp::project& p) const {
    const auto path(p.odb_options().file_path());
    BOOST_LOG_SEV(lg, debug) << "Formatting:" << path.string();

    std::ostringstream s;
    cpp_formatters::odb_options f(s);
    f.format(p.odb_options());

    return std::make_pair(path, s.str());
}

workflow::result_type
workflow::format_source_files_activity(const cpp::project& p) const {
    workflow::result_type r;

    std::map<config::cpp_facet_types, std::list<std::string> >
        headers_for_facet_;

    for (const auto f : p.files()) {
        if (f.descriptor().file_type() == cpp::file_types::header)
            headers_for_facet_[f.descriptor().facet_type()].
                push_back(f.relative_path().generic_string());

        BOOST_LOG_SEV(lg, debug) << "Formatting:" << f.file_path().string();
        BOOST_LOG_SEV(lg, debug) << "Descriptor:" << f.descriptor();
        cpp_formatters::factory factory(settings_);
        cpp_formatters::file_formatter::shared_ptr ff;
        std::ostringstream s;
        ff = factory.create(s, f.descriptor());
        ff->format(f);
        r.insert(std::make_pair(f.file_path(), s.str()));
    }

    return r;
}

workflow::result_type workflow::execute(const cpp::project& p) {
    BOOST_LOG_SEV(lg, info) << "C++ formatters workflow started.";

    workflow::result_type r(format_source_files_activity(p));
    if (settings_.disable_cmakelists())
        BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
    else {
        const auto cm(format_cmakelists_activity(p));
        r.insert(cm.begin(), cm.end());
    }

    const auto f(settings_.enabled_facets());
    const bool odb_enabled(f.find(config::cpp_facet_types::odb) != f.end());
    if (odb_enabled)
        r.insert(format_odb_options_activity(p));
    else
        BOOST_LOG_SEV(lg, info) << "ODB options file generation disabled.";

    BOOST_LOG_SEV(lg, info) << "C++ formatters workflow finished.";
    return r;
}

} }
