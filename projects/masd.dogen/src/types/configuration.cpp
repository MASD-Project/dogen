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
#include "masd.dogen/types/configuration.hpp"

namespace masd::dogen {

configuration::configuration(configuration&& rhs)
    : error_handling_(std::move(rhs.error_handling_)),
      tracing_(std::move(rhs.tracing_)),
      diffing_(std::move(rhs.diffing_)) { }

configuration::configuration(
    const boost::optional<masd::dogen::error_handling_configuration>& error_handling,
    const boost::optional<masd::dogen::tracing_configuration>& tracing,
    const boost::optional<masd::dogen::diffing_configuration>& diffing)
    : error_handling_(error_handling),
      tracing_(tracing),
      diffing_(diffing) { }

void configuration::swap(configuration& other) noexcept {
    using std::swap;
    swap(error_handling_, other.error_handling_);
    swap(tracing_, other.tracing_);
    swap(diffing_, other.diffing_);
}

bool configuration::operator==(const configuration& rhs) const {
    return error_handling_ == rhs.error_handling_ &&
        tracing_ == rhs.tracing_ &&
        diffing_ == rhs.diffing_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<masd::dogen::error_handling_configuration>& configuration::error_handling() const {
    return error_handling_;
}

boost::optional<masd::dogen::error_handling_configuration>& configuration::error_handling() {
    return error_handling_;
}

configuration& configuration::error_handling(const boost::optional<masd::dogen::error_handling_configuration>& v) {
    error_handling_ = v;
    return *this;
}

configuration& configuration::error_handling(const boost::optional<masd::dogen::error_handling_configuration>&& v) {
    error_handling_ = std::move(v);
    return *this;
}

const boost::optional<masd::dogen::tracing_configuration>& configuration::tracing() const {
    return tracing_;
}

boost::optional<masd::dogen::tracing_configuration>& configuration::tracing() {
    return tracing_;
}

configuration& configuration::tracing(const boost::optional<masd::dogen::tracing_configuration>& v) {
    tracing_ = v;
    return *this;
}

configuration& configuration::tracing(const boost::optional<masd::dogen::tracing_configuration>&& v) {
    tracing_ = std::move(v);
    return *this;
}

const boost::optional<masd::dogen::diffing_configuration>& configuration::diffing() const {
    return diffing_;
}

boost::optional<masd::dogen::diffing_configuration>& configuration::diffing() {
    return diffing_;
}

configuration& configuration::diffing(const boost::optional<masd::dogen::diffing_configuration>& v) {
    diffing_ = v;
    return *this;
}

configuration& configuration::diffing(const boost::optional<masd::dogen::diffing_configuration>&& v) {
    diffing_ = std::move(v);
    return *this;
}

}
