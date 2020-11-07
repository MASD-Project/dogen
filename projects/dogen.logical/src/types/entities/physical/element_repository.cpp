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
#include "dogen.logical/types/entities/physical/part.hpp"
#include "dogen.logical/types/entities/physical/facet.hpp"
#include "dogen.logical/types/entities/physical/helper.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind.hpp"
#include "dogen.logical/types/entities/physical/element_repository.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::physical::backend>& lhs,
const boost::shared_ptr<dogen::logical::entities::physical::backend>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::physical::facet>& lhs,
const boost::shared_ptr<dogen::logical::entities::physical::facet>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::physical::archetype>& lhs,
const boost::shared_ptr<dogen::logical::entities::physical::archetype>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::physical::part>& lhs,
const boost::shared_ptr<dogen::logical::entities::physical::part>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::physical::archetype_kind>& lhs,
const boost::shared_ptr<dogen::logical::entities::physical::archetype_kind>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::physical::helper>& lhs,
const boost::shared_ptr<dogen::logical::entities::physical::helper>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::entities::physical {

element_repository::element_repository(
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >& backends,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >& facets,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >& archetypes,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >& parts,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >& archetype_kinds,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >& helpers)
    : backends_(backends),
      facets_(facets),
      archetypes_(archetypes),
      parts_(parts),
      archetype_kinds_(archetype_kinds),
      helpers_(helpers) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(backends_, other.backends_);
    swap(facets_, other.facets_);
    swap(archetypes_, other.archetypes_);
    swap(parts_, other.parts_);
    swap(archetype_kinds_, other.archetype_kinds_);
    swap(helpers_, other.helpers_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return backends_ == rhs.backends_ &&
        facets_ == rhs.facets_ &&
        archetypes_ == rhs.archetypes_ &&
        parts_ == rhs.parts_ &&
        archetype_kinds_ == rhs.archetype_kinds_ &&
        helpers_ == rhs.helpers_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >& element_repository::backends() const {
    return backends_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >& element_repository::backends() {
    return backends_;
}

void element_repository::backends(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >& v) {
    backends_ = v;
}

void element_repository::backends(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >&& v) {
    backends_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >& element_repository::facets() const {
    return facets_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >& element_repository::facets() {
    return facets_;
}

void element_repository::facets(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >& v) {
    facets_ = v;
}

void element_repository::facets(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >&& v) {
    facets_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >& element_repository::archetypes() const {
    return archetypes_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >& element_repository::archetypes() {
    return archetypes_;
}

void element_repository::archetypes(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >& v) {
    archetypes_ = v;
}

void element_repository::archetypes(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >&& v) {
    archetypes_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >& element_repository::parts() const {
    return parts_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >& element_repository::parts() {
    return parts_;
}

void element_repository::parts(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >& v) {
    parts_ = v;
}

void element_repository::parts(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >&& v) {
    parts_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >& element_repository::archetype_kinds() const {
    return archetype_kinds_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >& element_repository::archetype_kinds() {
    return archetype_kinds_;
}

void element_repository::archetype_kinds(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >& v) {
    archetype_kinds_ = v;
}

void element_repository::archetype_kinds(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >&& v) {
    archetype_kinds_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >& element_repository::helpers() const {
    return helpers_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >& element_repository::helpers() {
    return helpers_;
}

void element_repository::helpers(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >& v) {
    helpers_ = v;
}

void element_repository::helpers(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >&& v) {
    helpers_ = std::move(v);
}

}
