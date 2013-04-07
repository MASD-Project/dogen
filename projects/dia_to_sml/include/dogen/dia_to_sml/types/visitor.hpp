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
#ifndef DOGEN_DIA_TO_SML_TYPES_VISITOR_FWD_HPP
#define DOGEN_DIA_TO_SML_TYPES_VISITOR_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/dia/types/object.hpp"
#include "dogen/dia_to_sml/types/object_transformer_interface.hpp"

namespace dogen {
namespace dia_to_sml {

class visitor : public boost::default_dfs_visitor {
public:
    visitor() = delete;
    visitor& operator=(const visitor&) = default;
    visitor(const visitor&) = default;
    visitor(visitor&&) = default;

public:
    explicit visitor(object_transformer_interface& transformer);

public:
    template<typename Vertex, typename Graph>
    void discover_vertex(const Vertex& u, const Graph& g) {
        transformer_.transform(g[u]);
    }

private:
    object_transformer_interface& transformer_;
};

} }

#endif
