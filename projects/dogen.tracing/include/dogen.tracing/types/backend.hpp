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
#ifndef DOGEN_TRACING_TYPES_BACKEND_HPP
#define DOGEN_TRACING_TYPES_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <sstream>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen/types/tracing_configuration.hpp"
#include "dogen/types/database_configuration.hpp"

namespace dogen::tracing {

/**
 * @brief Interface for tracing backends.
 */
class backend {
public:
    virtual ~backend() noexcept = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Starts a tracing session.
     */
    virtual void start_tracing(const std::string& input_id,
        const std::string& input) const = 0;

    /**
     * @brief Ends the current tracing session.
     *
     * @pre A tracing session must have been started.
     */
    virtual void end_tracing() const = 0;

public:
    /**
     * @brief Creates a references graph.
     */
    virtual void add_references_graph(const std::string& root_vertex,
        const std::unordered_map<std::string, std::list<std::string>>&
        edges_per_model) const = 0;

public:
    /**
     * @brief Starts a new transform chain.
     */
    /**@{*/
    virtual void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id) const = 0;
    virtual void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const = 0;
    virtual void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id, const std::string& input) const = 0;
    /**@}*/

    /**
     * @brief Ends a transform chain.
     *
     * @pre A transform chain must have been staerted.
     */
    /**@{*/
    virtual void end_chain() const = 0;
    virtual void end_chain(const std::string& output) const = 0;
    /**@}*/

public:
    /**
     * @brief Starts a new transform.
     */
    /**@{*/
    virtual void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id) const = 0;
    virtual void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const = 0;
    virtual void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id, const std::string& input) const = 0;
    /**@}*/

    /**
     * @brief Ends a transform.
     *
     * @pre A transform must have been staerted.
     */
    /**@{*/
    virtual void end_transform() const = 0;
    virtual void end_transform(const std::string& output) const = 0;
    /**@}*/
};

inline backend::~backend() noexcept { }

}

#endif
