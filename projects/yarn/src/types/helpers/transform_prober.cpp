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
#include "dogen/yarn/types/helpers/transform_prober.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

transform_prober::transform_prober()
    : probe_data__(static_cast<bool>(0)),
      probe_stats__(static_cast<bool>(0)),
      probe_stats_graph__(static_cast<bool>(0)) { }

transform_prober::transform_prober(transform_prober&& rhs)
    : builder__(std::move(rhs.builder__)),
      probe_data__(std::move(rhs.probe_data__)),
      probe_stats__(std::move(rhs.probe_stats__)),
      probe_stats_graph__(std::move(rhs.probe_stats_graph__)),
      probe_data_directory__(std::move(rhs.probe_data_directory__)) { }

transform_prober::transform_prober(
    const dogen::yarn::helpers::transform_metrics_builder& builder_,
    const bool probe_data_,
    const bool probe_stats_,
    const bool probe_stats_graph_,
    const boost::filesystem::path& probe_data_directory_)
    : builder__(builder_),
      probe_data__(probe_data_),
      probe_stats__(probe_stats_),
      probe_stats_graph__(probe_stats_graph_),
      probe_data_directory__(probe_data_directory_) { }

void transform_prober::swap(transform_prober& other) noexcept {
    using std::swap;
    swap(builder__, other.builder__);
    swap(probe_data__, other.probe_data__);
    swap(probe_stats__, other.probe_stats__);
    swap(probe_stats_graph__, other.probe_stats_graph__);
    swap(probe_data_directory__, other.probe_data_directory__);
}

bool transform_prober::operator==(const transform_prober& rhs) const {
    return builder__ == rhs.builder__ &&
        probe_data__ == rhs.probe_data__ &&
        probe_stats__ == rhs.probe_stats__ &&
        probe_stats_graph__ == rhs.probe_stats_graph__ &&
        probe_data_directory__ == rhs.probe_data_directory__;
}

transform_prober& transform_prober::operator=(transform_prober other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::helpers::transform_metrics_builder& transform_prober::builder_() const {
    return builder__;
}

dogen::yarn::helpers::transform_metrics_builder& transform_prober::builder_() {
    return builder__;
}

void transform_prober::builder_(const dogen::yarn::helpers::transform_metrics_builder& v) {
    builder__ = v;
}

void transform_prober::builder_(const dogen::yarn::helpers::transform_metrics_builder&& v) {
    builder__ = std::move(v);
}

bool transform_prober::probe_data_() const {
    return probe_data__;
}

void transform_prober::probe_data_(const bool v) {
    probe_data__ = v;
}

bool transform_prober::probe_stats_() const {
    return probe_stats__;
}

void transform_prober::probe_stats_(const bool v) {
    probe_stats__ = v;
}

bool transform_prober::probe_stats_graph_() const {
    return probe_stats_graph__;
}

void transform_prober::probe_stats_graph_(const bool v) {
    probe_stats_graph__ = v;
}

const boost::filesystem::path& transform_prober::probe_data_directory_() const {
    return probe_data_directory__;
}

boost::filesystem::path& transform_prober::probe_data_directory_() {
    return probe_data_directory__;
}

void transform_prober::probe_data_directory_(const boost::filesystem::path& v) {
    probe_data_directory__ = v;
}

void transform_prober::probe_data_directory_(const boost::filesystem::path&& v) {
    probe_data_directory__ = std::move(v);
}

} } }
