/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/io/tracing_format_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/metrics_printer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.metrics_printer"));

const char org_mode_filler('*');
const char txt_filler(' ');
const unsigned int org_mode_fill_size(1);
const unsigned int txt_fill_size(4);
const std::string empty;

const std::string invalid_tracing_format(
    "Invalid or unsupported tracing format: ");

}

namespace dogen::tracing {

void metrics_printer::print_plain(std::ostream& o, unsigned int fill_level,
    const bool disable_guids,
    const boost::shared_ptr<const metrics> tm) {

    BOOST_LOG_SEV(lg, trace) << "Fill level: " << fill_level;
    auto elapsed(tm->end() - tm->start());

    o << std::string(txt_fill_size * fill_level, txt_filler);

    o << tm->transform_id() << " (" << elapsed  << " ms)"
      << " [" << tm->model_id() << "]";

    if (!disable_guids)
        o << " [" << tm->guid() << "]";

    o << std::endl;

    ++fill_level;
    for(auto child : tm->children())
        print_plain(o, fill_level, disable_guids, child);
}

void metrics_printer::print_org_mode(std::ostream& o, unsigned int fill_level,
    const bool disable_guids,
    const boost::shared_ptr<const metrics> tm) {

    BOOST_LOG_SEV(lg, trace) << "Fill level: " << fill_level;
    auto elapsed(tm->end() - tm->start());

    o << std::string(org_mode_fill_size * fill_level, org_mode_filler)
      << " ";

    o << tm->transform_id() << " (" << elapsed  << " ms)"
      << " [" << tm->model_id() << "]";

    if (!disable_guids)
        o << " [" << tm->guid() << "]";

    o << std::endl;

    ++fill_level;
    for(auto child : tm->children())
        print_org_mode(o, fill_level, disable_guids, child);
}

void metrics_printer::print_graphviz(std::ostream& table_stream,
    std::ostream& vertex_stream, const bool disable_guids,
    const std::string& parent_id, const boost::shared_ptr<const metrics> tm) {

    auto elapsed(tm->end() - tm->start());

    auto tid(tm->transform_id());
    boost::replace_all(tid, ".", "_");

    auto pid(parent_id);
    boost::replace_all(pid, ".", "_");

    auto mid(tm->model_id());
    if (mid.empty())
        mid = "empty";
    else {
        boost::replace_all(mid, "<", "");
        boost::replace_all(mid, ">", "_");
    }

    std::string guid("GUID_");
    guid += tm->guid();
    boost::replace_all(guid, "-", "_");

    table_stream << "  " << guid << " [ label=<" << std::endl
                 << "  <table border=\"1\" cellborder=\"0\" cellspacing=\"1\">"
                 << std::endl
                 << "    <tr><td align=\"left\"><b>" << tid
                 << " [" << mid << "]"
                 << "</b></td></tr>"
                 << std::endl
                 << "    <tr><td align=\"left\">" << elapsed << "ms</td></tr>"
                 << std::endl;

    if (!disable_guids) {
        table_stream << "    <tr><td align=\"left\"><font color=\"darkgreen\">"
                     << tm->guid() << "</font></td></tr>" << std::endl;
    }
    table_stream << "  </table>>];" << std::endl<< std::endl;

    if (!parent_id.empty())
        vertex_stream << "  " << pid << " -> " << guid << std::endl;

    for(auto child : tm->children())
        print_graphviz(table_stream, vertex_stream, disable_guids,
            guid, child);
}

void metrics_printer::print_graphviz(std::ostream& s,
    const bool disable_guids,
    const boost::shared_ptr<const metrics> tm) {

    s << "digraph D {" << std::endl
      << "  node [shape=plaintext fontname=\"Sans serif\" fontsize=\"8\"];"
      << std::endl<< std::endl;

    std::ostringstream table_stream;
    std::ostringstream vertex_stream;
    print_graphviz(table_stream, vertex_stream, disable_guids, empty, tm);

    s << table_stream.str() << std::endl;
    s << vertex_stream.str() << std::endl;
    s << "}" << std::endl;
}

std::string metrics_printer::
print(const bool disable_guids, const tracing_format tf,
    const boost::shared_ptr<const metrics> tm) {
    BOOST_LOG_SEV(lg, debug) << "Printing graph.";

    std::ostringstream s;
    switch(tf) {
    case tracing_format::plain:
        BOOST_LOG_SEV(lg, debug) << "Using plain format.";
        print_plain(s, 0, disable_guids, tm);
        break;
    case tracing_format::org_mode:
        BOOST_LOG_SEV(lg, debug) << "Using org-mode format.";
        print_org_mode(s, 1, disable_guids, tm);
        break;
    case tracing_format::graphviz:
        BOOST_LOG_SEV(lg, debug) << "Using graphviz format.";
        print_graphviz(s, disable_guids, tm);
        break;
    default: {
        BOOST_LOG_SEV(lg, error) << invalid_tracing_format << tf;
        BOOST_THROW_EXCEPTION(tracing_error(invalid_tracing_format +
                boost::lexical_cast<std::string>(tf)));
    } }
    const auto r(s.str());

    BOOST_LOG_SEV(lg, debug) << "Finished printing graph.";
    return r;
}

}
