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
#ifndef DOGEN_SML_TYPES_GRAPH_VISITOR_HPP
#define DOGEN_SML_TYPES_GRAPH_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include <boost/graph/depth_first_search.hpp>

namespace dogen {
namespace sml {

template<typename GraphSubject>
class graph_visitor : public boost::default_dfs_visitor {
public:
    graph_visitor() = delete;
    graph_visitor& operator=(const graph_visitor&) = default;
    graph_visitor(const graph_visitor&) = default;
    graph_visitor(graph_visitor&&) = default;

public:
    typedef std::function<void(const GraphSubject&)> function_type;

public:
    explicit graph_visitor(const function_type& function)
        : function_(function) { }

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        const auto o(g[u]);
        function_(std::cref(o));
    }

private:
    function_type function_;
};

} }

#endif
