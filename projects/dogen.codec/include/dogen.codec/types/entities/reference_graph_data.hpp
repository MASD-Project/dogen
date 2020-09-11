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
#ifndef DOGEN_CODEC_TYPES_ENTITIES_REFERENCE_GRAPH_DATA_HPP
#define DOGEN_CODEC_TYPES_ENTITIES_REFERENCE_GRAPH_DATA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>

namespace dogen::codec::entities {

/**
 * @brief Contains all the data required to build the graph of references.
 */
class reference_graph_data final {
public:
    reference_graph_data() = default;
    reference_graph_data(const reference_graph_data&) = default;
    reference_graph_data(reference_graph_data&&) = default;
    ~reference_graph_data() = default;

public:
    reference_graph_data(
        const std::string& root,
        const std::unordered_map<std::string, std::list<std::string> >& edges_per_model);

public:
    /**
     * @brief Has the name of the target model, which is the entry point to the references
     * graph.
     */
    /**@{*/
    const std::string& root() const;
    std::string& root();
    void root(const std::string& v);
    void root(const std::string&& v);
    /**@}*/

    /**
     * @brief Contains the list of referenced models for a particular model name.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<std::string> >& edges_per_model() const;
    std::unordered_map<std::string, std::list<std::string> >& edges_per_model();
    void edges_per_model(const std::unordered_map<std::string, std::list<std::string> >& v);
    void edges_per_model(const std::unordered_map<std::string, std::list<std::string> >&& v);
    /**@}*/

public:
    bool operator==(const reference_graph_data& rhs) const;
    bool operator!=(const reference_graph_data& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(reference_graph_data& other) noexcept;
    reference_graph_data& operator=(reference_graph_data other);

private:
    std::string root_;
    std::unordered_map<std::string, std::list<std::string> > edges_per_model_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::entities::reference_graph_data& lhs,
    dogen::codec::entities::reference_graph_data& rhs) {
    lhs.swap(rhs);
}

}

#endif
