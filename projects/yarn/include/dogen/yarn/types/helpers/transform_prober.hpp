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
#ifndef DOGEN_YARN_TYPES_HELPERS_TRANSFORM_PROBER_HPP
#define DOGEN_YARN_TYPES_HELPERS_TRANSFORM_PROBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/archetype_location_repository.hpp"
#include "dogen/yarn/types/helpers/mapping_set_repository.hpp"
#include "dogen/yarn/types/helpers/transform_metrics_builder.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class transform_prober final {
public:
    transform_prober(const bool probe_data, const bool probe_stats,
        const bool probe_stats_graph,
        const boost::filesystem::path& probe_directory,
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const helpers::mapping_set_repository& msrp);

private:
    void handle_probe_directory() const;

    void write_initial_inputs(
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const helpers::mapping_set_repository& msrp) const;

private:
    mutable transform_metrics_builder builder_;
    const bool probe_data_;
    const bool probe_stats_;
    const bool probe_stats_graph_;
    const boost::filesystem::path probe_directory_;
};

} } }

#endif
