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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/io/formattables/content_descriptor_io.hpp"
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

workflow::workflow(const config::knitting_options& o) : options_(o) { }

std::forward_list<formatters::file>
workflow::format_cmakelists_activity(
    const cpp::formattables::project& p) const {

    std::forward_list<formatters::file> r;
    if (options_.cpp().disable_cmakelists()) {
        BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
        return r;
    }

    {
        const auto path(p.src_cmakelists().file_path());
        BOOST_LOG_SEV(lg, debug) << "Formatting: " << path.string();

        std::ostringstream s;
        cpp_formatters::src_cmakelists fmt(s);
        fmt.format(p.src_cmakelists());

        formatters::file file;
        file.path(path);
        file.content(s.str());
        r.push_front(file);
    }

    if (p.include_cmakelists()) {
        const auto path(p.include_cmakelists()->file_path());
        BOOST_LOG_SEV(lg, debug) << "Formatting: " << path.string();

        const auto fct(options_.cpp().enabled_facets());
        const auto i(fct.find(config::cpp_facet_types::odb));
        const bool is_odb_enabled(i != fct.end());
        const auto fct_folder(options_.cpp().odb_facet_folder());

        std::ostringstream s;
        cpp_formatters::include_cmakelists fmt(s, is_odb_enabled, fct_folder);
        fmt.format(*p.include_cmakelists());

        formatters::file file;
        file.path(path);
        file.content(s.str());
        r.push_front(file);
    }

    return r;
}

std::forward_list<formatters::file> workflow::
format_odb_options_activity(const cpp::formattables::project& p) const {
    std::forward_list<formatters::file> r;
    const auto fcts(options_.cpp().enabled_facets());
    const auto i(fcts.find(config::cpp_facet_types::odb));
    const bool is_odb_enabled(i != fcts.end());
    if (!is_odb_enabled) {
        BOOST_LOG_SEV(lg, info) << "ODB options file generation disabled.";
        return r;
    }

    const auto path(p.odb_options().file_path());
    BOOST_LOG_SEV(lg, debug) << "Formatting:" << path.string();

    std::ostringstream s;
    cpp_formatters::odb_options f(s);
    f.format(p.odb_options());

    formatters::file file;
    file.path(path);
    file.content(s.str());
    r.push_front(file);

    return r;
}

std::forward_list<formatters::file> workflow::
format_file_infos_activity(const cpp::formattables::project& p) const {

    std::ostringstream s;
    std::forward_list<formatters::file> r;
    cpp_formatters::factory factory(options_);
    cpp_formatters::file_formatter::shared_ptr fmt;
    for (const auto f : p.files()) {
        BOOST_LOG_SEV(lg, debug) << "Formatting:" << f.file_path().string();
        BOOST_LOG_SEV(lg, debug) << "Descriptor:" << f.descriptor();

        fmt = factory.create(s, f.descriptor());
        fmt->format(f);

        formatters::file file;
        file.path(f.file_path());
        file.content(s.str());
        r.push_front(file);
        s.str("");
    }

    return r;
}

std::forward_list<formatters::file>
workflow::execute(const cpp::formattables::project& p) const {
    BOOST_LOG_SEV(lg, info) << "C++ formatters workflow started.";

    std::forward_list<formatters::file> r(format_file_infos_activity(p));
    r.splice_after(r.before_begin(), format_cmakelists_activity(p));
    r.splice_after(r.before_begin(), format_odb_options_activity(p));

    BOOST_LOG_SEV(lg, info) << "C++ formatters workflow finished.";
    return r;
}

} }
