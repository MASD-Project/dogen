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
#include "dogen.tracing/types/references_printer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.references_printer"));

const char org_mode_filler('*');
const char txt_filler(' ');
const unsigned int org_mode_fill_size(1);
const unsigned int txt_fill_size(4);
const std::string empty;

const std::string invalid_tracing_format(
    "Invalid or unsupported tracing format: ");

}

namespace dogen::tracing {

void references_printer::print_plain(std::ostream& o, unsigned int fill_level,
    const std::string& vertex, const edges_per_model_type& edges_per_model) {
    BOOST_LOG_SEV(lg, trace) << "Fill level: " << fill_level;
    o << std::string(txt_fill_size * fill_level, txt_filler)
      << vertex << std::endl;

    ++fill_level;
    const auto i(edges_per_model.find(vertex));
    if (i == edges_per_model.end())
        return;

    for(auto child_vertex : i->second)
        print_plain(o, fill_level, child_vertex, edges_per_model);
}

void references_printer::
    print_org_mode(std::ostream& o, unsigned int fill_level,
        const std::string& vertex, const edges_per_model_type& edges_per_model) {
    BOOST_LOG_SEV(lg, trace) << "Fill level: " << fill_level;
    o << std::string(org_mode_fill_size * fill_level, org_mode_filler)
      << " " << vertex << std::endl;

    ++fill_level;
    const auto i(edges_per_model.find(vertex));
    if (i == edges_per_model.end())
        return;

    for(auto child_vertex : i->second)
        print_org_mode(o, fill_level, child_vertex, edges_per_model);
}

void references_printer::create_graphviz_edge_set(
    std::unordered_set<std::string>& edge_set,
    const std::string& vertex, const edges_per_model_type& edges_per_model) {
    const auto i(edges_per_model.find(vertex));
    if (i == edges_per_model.end())
        return;

    std::ostringstream s;
    for(auto child_vertex : i->second) {
        s << "  \"" << vertex << "\" -> \"" << child_vertex << "\";";
        edge_set.insert(s.str());
        s.str("");
        create_graphviz_edge_set(edge_set, child_vertex, edges_per_model);
    }
}

void references_printer::print_graphviz(std::ostream& o,
    const std::unordered_set<std::string>& edge_set) {

    o << "digraph D {" << std::endl
      << "  node [shape=oval fontname=\"Sans serif\" fontsize=\"8\"];"
      << std::endl<< std::endl;

    for (const auto& e : edge_set)
        o << e << std::endl;

    o << "}" << std::endl;
}

std::string references_printer::print(const tracing_format tf,
    const std::string& root_vertex,
    const edges_per_model_type& edges_per_model) {
    BOOST_LOG_SEV(lg, debug) << "Printing graph.";

    std::ostringstream s;
    switch(tf) {
    case tracing_format::plain:
        BOOST_LOG_SEV(lg, debug) << "Using plain format.";
        print_plain(s, 0, root_vertex, edges_per_model);
        break;
    case tracing_format::org_mode:
        BOOST_LOG_SEV(lg, debug) << "Using org-mode format.";
        print_org_mode(s, 1, root_vertex, edges_per_model);
        break;
    case tracing_format::graphviz: {
        BOOST_LOG_SEV(lg, debug) << "Using graphviz format.";
        std::unordered_set<std::string> edge_set;
        create_graphviz_edge_set(edge_set, root_vertex, edges_per_model);
        print_graphviz(s, edge_set);
        break;
    } default: {
        BOOST_LOG_SEV(lg, error) << invalid_tracing_format << tf;
        BOOST_THROW_EXCEPTION(tracing_error(invalid_tracing_format +
                boost::lexical_cast<std::string>(tf)));
    } }
    const auto r(s.str());

    BOOST_LOG_SEV(lg, debug) << "Finished printing graph.";
    return r;

}

}
