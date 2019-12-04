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
#ifndef DOGEN_TRACING_TYPES_RELATIONAL_BACKEND_HPP
#define DOGEN_TRACING_TYPES_RELATIONAL_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/config.hpp"
#ifdef DOGEN_HAVE_RELATIONAL_MODEL
#include <string>
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/schema-catalog.hxx>
#include "dogen.tracing/types/backend.hpp"
#include "dogen/types/tracing_configuration.hpp"
#include "dogen/types/database_configuration.hpp"

namespace dogen::tracing {

/**
 * @brief Writes tracing information to a relational database.
 */
class relational_backend : public dogen::tracing::backend {
public:
    relational_backend(const tracing_configuration& tcfg,
        const database_configuration& dbcfg,
        const std::string& run_id);

public:
    virtual ~relational_backend() noexcept { }

public:
    virtual void to_stream(std::ostream& s) const override;

public:
    void start_tracing(const std::string& input_id,
        const std::string& input) const override;
    void end_tracing() const override;

public:
    void add_references_graph(const std::string& root_vertex,
        const std::unordered_map<std::string, std::list<std::string>>&
        edges_per_model) const override;

public:
    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id) const override;
    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const override;
    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id,
        const std::string& input) const override;

    void end_chain() const override;
    void end_chain(const std::string& output) const override;

public:
    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id) const override;
    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const override;
    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id,
        const std::string& input) const override;

    void end_transform() const override;
    void end_transform(const std::string& output) const override;

private:
    const tracing_configuration tracing_configuration_;
    const database_configuration database_configuration_;
    const std::string run_id_;
    boost::shared_ptr<odb::pgsql::database> database_;

};

}

#endif // DOGEN_HAVE_RELATIONAL_MODEL

#endif
