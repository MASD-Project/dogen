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
#ifndef DOGEN_TRACING_TYPES_REFERENCES_PRINTER_HPP
#define DOGEN_TRACING_TYPES_REFERENCES_PRINTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "dogen/types/tracing_format.hpp"

namespace dogen::tracing {

/**
 * @brief Prints a graph of references according to the settings.
 */

class references_printer final {
private:
    typedef std::unordered_map<std::string, std::list<std::string>>
    edges_per_model_type;

private:
    static void print_plain(std::ostream& o, unsigned int fill_level,
        const std::string& vertex, const edges_per_model_type& edges_per_model);

    static void print_org_mode(std::ostream& o, unsigned int fill_level,
        const std::string& vertex, const edges_per_model_type& edges_per_model);

    static void create_graphviz_edge_set(
        std::unordered_set<std::string>& edge_set,
        const std::string& vertex,
        const edges_per_model_type& edges_per_model);

    static void print_graphviz(std::ostream& o,
        const std::unordered_set<std::string>& edge_set);

public:
  /**
   * @brief Print the graph into a string.
   *
   * @pre The graph must be acyclic.
   */
    static std::string print(const tracing_format tf,
        const std::string& root_vertex,
        const edges_per_model_type& edges_per_model);
};

}

#endif
