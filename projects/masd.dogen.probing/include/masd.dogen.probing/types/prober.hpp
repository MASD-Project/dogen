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
#ifndef MASD_DOGEN_PROBING_TYPES_PROBER_HPP
#define MASD_DOGEN_PROBING_TYPES_PROBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <stack>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.utility/filesystem/file.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository.hpp"
#include "masd.dogen.probing/types/metrics.hpp"
#include "masd.dogen.probing/types/metrics_builder.hpp"

namespace masd::dogen::probing {

class prober final {
public:
    prober(const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const std::string log_level,
        const bool probe_all,
        const bool probe_data,
        const bool probe_stats,
        const bool disable_guids_in_stats,
        const bool use_org_mode,
        const bool use_short_names,
        const boost::filesystem::path probe_directory);

private:
    void validate() const;
    bool probing_enabled() const;
    void handle_probe_directory() const;
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

        if (!probe_data_)
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

        if (probe_data_) {
            ensure_transform_position_not_empty();
            ++transform_position_.top();
            const auto p(full_path_for_writing(transform_id, "input"));
            utility::filesystem::write(p, input);
        }
    }

    void end_chain() const;

    template<typename Ioable>
    void end_chain(const Ioable& output) const {
        if (probe_data_) {
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
        if (probe_data_) {
            ensure_transform_position_not_empty();
            ++transform_position_.top();
            const auto id(builder_.current()->transform_id());
            const auto p(full_path_for_writing(id, "output"));
            utility::filesystem::write(p, output);
        }
        end_transform();
    }

    void end_probing() const;

private:
    mutable metrics_builder builder_;
    mutable std::stack<unsigned int> transform_position_;
    mutable boost::filesystem::path current_directory_;
    const bool probe_data_;
    const bool probe_stats_;
    const bool disable_guids_in_stats_;
    const bool use_org_mode_;
    const bool use_short_names_;
    const boost::filesystem::path probe_directory_;
};

}

#endif
