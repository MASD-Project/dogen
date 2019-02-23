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
#ifndef MASD_DOGEN_TRACING_TYPES_TRACER_HPP
#define MASD_DOGEN_TRACING_TYPES_TRACER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <stack>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen/types/tracing_configuration.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository.hpp"
#include "masd.dogen.tracing/types/metrics.hpp"
#include "masd.dogen.tracing/types/metrics_builder.hpp"

namespace masd::dogen::tracing {

/**
 * @brief Handles all of the tracing-related work.
 */
class tracer final {
public:
    tracer(const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const boost::filesystem::path& tracing_directory,
        const boost::optional<tracing_configuration>& cfg);

private:
    void validate() const;
    bool tracing_enabled() const;
    bool detailed_tracing_enabled() const;
    void handle_tracing_directory() const;
    void handle_current_directory() const;
    void ensure_transform_position_not_empty() const;

    void write_initial_inputs(
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp) const;

    boost::filesystem::path
    full_path_for_writing(const std::string& transform_id,
        const std::string& type) const;

    boost::filesystem::path
    full_path_for_writing(const std::string& filename) const;

public:
    void start_chain(const std::string& transform_id) const;
    void start_chain(const std::string& transform_id,
        const std::string& model_id) const;

    template<typename Ioable>
    void start_chain(const std::string& transform_id,
        const std::string& model_id,
        const Ioable& input) const {
        start_chain(transform_id, model_id);

        if (!detailed_tracing_enabled())
            return;

        ensure_transform_position_not_empty();
        ++transform_position_.top();
        const auto p(full_path_for_writing(transform_id, "input"));
        utility::filesystem::write(p, input);
    }

    void start_transform(const std::string& transform_id) const;

    void start_transform(const std::string& transform_id,
        const std::string& model_id) const;

    template<typename Ioable>
    void start_transform(const std::string& transform_id,
        const std::string& model_id,
        const Ioable& input) const {
        start_transform(transform_id, model_id);

        if (detailed_tracing_enabled()) {
            ensure_transform_position_not_empty();
            ++transform_position_.top();
            const auto p(full_path_for_writing(transform_id, "input"));
            utility::filesystem::write(p, input);
        }
    }

    void end_chain() const;

    template<typename Ioable>
    void end_chain(const Ioable& output) const {
        if (detailed_tracing_enabled()) {
            ensure_transform_position_not_empty();
            ++transform_position_.top();
            const auto id(builder_.current()->transform_id());
            const auto p(full_path_for_writing(id, "output"));
            utility::filesystem::write(p, output);
        }
        end_chain();
    }

    void end_transform() const;

    template<typename Ioable>
    void end_transform(const Ioable& output) const {
        if (detailed_tracing_enabled()) {
            ensure_transform_position_not_empty();
            ++transform_position_.top();
            const auto id(builder_.current()->transform_id());
            const auto p(full_path_for_writing(id, "output"));
            utility::filesystem::write(p, output);
        }
        end_transform();
    }

    void end_tracing() const;

private:
    const boost::optional<tracing_configuration> configuration_;
    const boost::filesystem::path tracing_directory_;
    mutable metrics_builder builder_;
    mutable std::stack<unsigned int> transform_position_;
    mutable boost::filesystem::path current_directory_;
};

}

#endif
