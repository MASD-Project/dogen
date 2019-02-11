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
    : activity_(std::move(rhs.activity_)),
      tracing_(std::move(rhs.tracing_)),
      logging_(std::move(rhs.logging_)),
      diffing_(std::move(rhs.diffing_)) { }

configuration::configuration(
    const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& activity,
    const masd::dogen::tracing_configuration& tracing,
    const masd::dogen::logging_configuration& logging,
    const masd::dogen::diffing_configuration& diffing)
    : activity_(activity),
      tracing_(tracing),
      logging_(logging),
      diffing_(diffing) { }

void configuration::swap(configuration& other) noexcept {
    using std::swap;
    swap(activity_, other.activity_);
    swap(tracing_, other.tracing_);
    swap(logging_, other.logging_);
    swap(diffing_, other.diffing_);
}

bool configuration::operator==(const configuration& rhs) const {
    return activity_ == rhs.activity_ &&
        tracing_ == rhs.tracing_ &&
        logging_ == rhs.logging_ &&
        diffing_ == rhs.diffing_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& configuration::activity() const {
    return activity_;
}

boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& configuration::activity() {
    return activity_;
}

configuration& configuration::activity(const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& v) {
    activity_ = v;
    return *this;
}

configuration& configuration::activity(const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>&& v) {
    activity_ = std::move(v);
    return *this;
}

const masd::dogen::tracing_configuration& configuration::tracing() const {
    return tracing_;
}

masd::dogen::tracing_configuration& configuration::tracing() {
    return tracing_;
}

configuration& configuration::tracing(const masd::dogen::tracing_configuration& v) {
    tracing_ = v;
    return *this;
}

configuration& configuration::tracing(const masd::dogen::tracing_configuration&& v) {
    tracing_ = std::move(v);
    return *this;
}

const masd::dogen::logging_configuration& configuration::logging() const {
    return logging_;
}

masd::dogen::logging_configuration& configuration::logging() {
    return logging_;
}

configuration& configuration::logging(const masd::dogen::logging_configuration& v) {
    logging_ = v;
    return *this;
}

configuration& configuration::logging(const masd::dogen::logging_configuration&& v) {
    logging_ = std::move(v);
    return *this;
}

const masd::dogen::diffing_configuration& configuration::diffing() const {
    return diffing_;
}

masd::dogen::diffing_configuration& configuration::diffing() {
    return diffing_;
}

configuration& configuration::diffing(const masd::dogen::diffing_configuration& v) {
    diffing_ = v;
    return *this;
}

configuration& configuration::diffing(const masd::dogen::diffing_configuration&& v) {
    diffing_ = std::move(v);
    return *this;
}

}
