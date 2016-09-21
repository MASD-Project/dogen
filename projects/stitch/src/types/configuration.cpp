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
#include "dogen/stitch/types/configuration.hpp"

namespace dogen {
namespace stitch {

configuration::configuration(configuration&& rhs)
    : decoration_configuration_(std::move(rhs.decoration_configuration_)),
      annotations_(std::move(rhs.annotations_)) { }

configuration::configuration(
    const boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration,
    const dogen::stitch::annotations& annotations)
    : decoration_configuration_(decoration_configuration),
      annotations_(annotations) { }

void configuration::swap(configuration& other) noexcept {
    using std::swap;
    swap(decoration_configuration_, other.decoration_configuration_);
    swap(annotations_, other.annotations_);
}

bool configuration::operator==(const configuration& rhs) const {
    return decoration_configuration_ == rhs.decoration_configuration_ &&
        annotations_ == rhs.annotations_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::decoration_configuration>& configuration::decoration_configuration() const {
    return decoration_configuration_;
}

boost::optional<dogen::formatters::decoration_configuration>& configuration::decoration_configuration() {
    return decoration_configuration_;
}

void configuration::decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>& v) {
    decoration_configuration_ = v;
}

void configuration::decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>&& v) {
    decoration_configuration_ = std::move(v);
}

const dogen::stitch::annotations& configuration::annotations() const {
    return annotations_;
}

dogen::stitch::annotations& configuration::annotations() {
    return annotations_;
}

void configuration::annotations(const dogen::stitch::annotations& v) {
    annotations_ = v;
}

void configuration::annotations(const dogen::stitch::annotations&& v) {
    annotations_ = std::move(v);
}

} }
