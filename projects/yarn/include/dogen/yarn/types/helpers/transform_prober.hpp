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
#include "dogen/yarn/types/helpers/transform_metrics_builder.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class transform_prober final {
public:
    transform_prober(const transform_prober&) = default;
    ~transform_prober() = default;

public:
    transform_prober();

public:
    transform_prober(transform_prober&& rhs);

public:
    transform_prober(
        const dogen::yarn::helpers::transform_metrics_builder& builder_,
        const bool probe_data_,
        const bool probe_stats_,
        const bool probe_stats_graph_,
        const boost::filesystem::path& probe_data_directory_);

public:
    const dogen::yarn::helpers::transform_metrics_builder& builder_() const;
    dogen::yarn::helpers::transform_metrics_builder& builder_();
    void builder_(const dogen::yarn::helpers::transform_metrics_builder& v);
    void builder_(const dogen::yarn::helpers::transform_metrics_builder&& v);

    bool probe_data_() const;
    void probe_data_(const bool v);

    bool probe_stats_() const;
    void probe_stats_(const bool v);

    bool probe_stats_graph_() const;
    void probe_stats_graph_(const bool v);

    const boost::filesystem::path& probe_data_directory_() const;
    boost::filesystem::path& probe_data_directory_();
    void probe_data_directory_(const boost::filesystem::path& v);
    void probe_data_directory_(const boost::filesystem::path&& v);

public:
    bool operator==(const transform_prober& rhs) const;
    bool operator!=(const transform_prober& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform_prober& other) noexcept;
    transform_prober& operator=(transform_prober other);

private:
    dogen::yarn::helpers::transform_metrics_builder builder__;
    bool probe_data__;
    bool probe_stats__;
    bool probe_stats_graph__;
    boost::filesystem::path probe_data_directory__;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::helpers::transform_prober& lhs,
    dogen::yarn::helpers::transform_prober& rhs) {
    lhs.swap(rhs);
}

}

#endif
