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
#ifndef DOGEN_INJECTION_TYPES_HELPERS_CIRCULAR_REFERENCES_VALIDATOR_HPP
#define DOGEN_INJECTION_TYPES_HELPERS_CIRCULAR_REFERENCES_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include "dogen.injection/types/meta_model/model_set.hpp"

namespace dogen::injection::helpers {

/**
 * @brief Graph of model references.
 */
typedef boost::adjacency_list<
    boost::setS, boost::vecS, boost::directedS, std::string
    > graph_type;

/**
 * @brief Checks that there are no cycles in the references graph.
 */
class circular_references_validator final {
private:
    typedef boost::graph_traits<graph_type>::vertex_descriptor
    vertex_descriptor_type;

    typedef std::unordered_map<std::string, vertex_descriptor_type>
    id_to_vertex_type;

private:
    std::unordered_map<std::string, std::list<std::string>>
    obtain_references_for_model(const meta_model::model_set& ms) const;

private:
    vertex_descriptor_type vertex_for_id(const std::string& id);

    void add_to_graph(const std::string& id,
        const std::unordered_map<std::string, std::list<std::string>>&
        references_for_model);

public:
    void validate(const meta_model::model_set& ms);

private:
    graph_type graph_;
    id_to_vertex_type id_to_vertex_;
};

}

#endif
