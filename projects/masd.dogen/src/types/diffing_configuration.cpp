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
#include "masd.dogen/types/diffing_configuration.hpp"

namespace masd::dogen {

diffing_configuration::diffing_configuration()
    : enabled_(static_cast<bool>(0)) { }

diffing_configuration::diffing_configuration(diffing_configuration&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      output_directory_(std::move(rhs.output_directory_)) { }

diffing_configuration::diffing_configuration(
    const bool enabled,
    const boost::filesystem::path& output_directory)
    : enabled_(enabled),
      output_directory_(output_directory) { }

void diffing_configuration::swap(diffing_configuration& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(output_directory_, other.output_directory_);
}

bool diffing_configuration::operator==(const diffing_configuration& rhs) const {
    return enabled_ == rhs.enabled_ &&
        output_directory_ == rhs.output_directory_;
}

diffing_configuration& diffing_configuration::operator=(diffing_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool diffing_configuration::enabled() const {
    return enabled_;
}

diffing_configuration& diffing_configuration::enabled(const bool v) {
    enabled_ = v;
    return *this;
}

const boost::filesystem::path& diffing_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& diffing_configuration::output_directory() {
    return output_directory_;
}

diffing_configuration& diffing_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

diffing_configuration& diffing_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

}
