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
#ifndef DOGEN_TRACING_TYPES_FILE_BACKEND_HPP
#define DOGEN_TRACING_TYPES_FILE_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <stack>
#include <list>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/types/tracing_configuration.hpp"
#include "dogen.tracing/types/metrics.hpp"
#include "dogen.tracing/types/metrics_builder.hpp"
#include "dogen.tracing/types/backend.hpp"

namespace dogen::tracing {

class file_backend final : public dogen::tracing::backend {
public:
    virtual ~file_backend() noexcept { }

public:
    file_backend(const tracing_configuration& cfg, const std::string& version,
        const std::string& run_id, const std::string& activity,
        const std::string& logging_impact, const std::string& tracing_impact);

public:
    virtual std::string id() const override;
    virtual dogen::tracing_backend tracing_backend() const override;

public:
    const boost::optional<tracing_configuration> configuration() const {
        return configuration_;
    }

private:
    void handle_output_directory() const;
    void handle_current_directory() const;
    void ensure_transform_position_not_empty() const;

    boost::filesystem::path
    full_path_for_writing(const std::string& transform_id,
        const std::string& type) const;

    boost::filesystem::path
    full_path_for_writing(const std::string& filename) const;

    boost::filesystem::path make_path(const boost::filesystem::path& dir,
        const std::string& fn, const tracing_format tf) const;

public:
    virtual void to_stream(std::ostream& s) const override;

public:
    void add_references_graph(const std::string& root_vertex,
        const std::unordered_map<std::string, std::list<std::string>>&
        edges_per_model) const override;

public:
    void start_run(const std::string& input_id,
        const std::string& input) const override;
    void end_run() const override;

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

    void end_chain(const std::string& transform_id,
        const std::string& transform_instance_id) const override;
    void end_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& output) const override;

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

    void end_transform(const std::string& transform_id,
        const std::string& transform_instance_id) const override;
    void end_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& output) const override;

public:
    bool operator==(const file_backend& rhs) const;

private:
    const bool detailed_tracing_enabled_;
    const tracing_configuration configuration_;
    mutable metrics_builder builder_;
    mutable std::stack<unsigned int> transform_position_;
    mutable boost::filesystem::path current_directory_;
    mutable std::string root_vertex_;
    mutable std::unordered_map<std::string, std::list<std::string>>
    edges_per_model_;
};

}

#endif
