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
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.archetypes/types/location_repository.hpp"
#include "dogen.variability/types/transforms/context.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::archetypes::location_repository>& lhs,
const boost::shared_ptr<dogen::archetypes::location_repository>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::tracing::tracer>& lhs,
const boost::shared_ptr<dogen::tracing::tracer>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::variability::transforms {

context::context()
    : compatibility_mode_(static_cast<bool>(0)) { }

context::context(
    const boost::shared_ptr<dogen::archetypes::location_repository>& archetype_location_repository,
    const bool compatibility_mode,
    const boost::shared_ptr<dogen::tracing::tracer>& tracer)
    : archetype_location_repository_(archetype_location_repository),
      compatibility_mode_(compatibility_mode),
      tracer_(tracer) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(archetype_location_repository_, other.archetype_location_repository_);
    swap(compatibility_mode_, other.compatibility_mode_);
    swap(tracer_, other.tracer_);
}

bool context::operator==(const context& rhs) const {
    return archetype_location_repository_ == rhs.archetype_location_repository_ &&
        compatibility_mode_ == rhs.compatibility_mode_ &&
        tracer_ == rhs.tracer_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::archetypes::location_repository>& context::archetype_location_repository() const {
    return archetype_location_repository_;
}

boost::shared_ptr<dogen::archetypes::location_repository>& context::archetype_location_repository() {
    return archetype_location_repository_;
}

void context::archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>& v) {
    archetype_location_repository_ = v;
}

void context::archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>&& v) {
    archetype_location_repository_ = std::move(v);
}

bool context::compatibility_mode() const {
    return compatibility_mode_;
}

void context::compatibility_mode(const bool v) {
    compatibility_mode_ = v;
}

const boost::shared_ptr<dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

boost::shared_ptr<dogen::tracing::tracer>& context::tracer() {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>& v) {
    tracer_ = v;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v) {
    tracer_ = std::move(v);
}

}
