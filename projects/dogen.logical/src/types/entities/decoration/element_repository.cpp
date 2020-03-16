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
#include "dogen.logical/types/entities/decoration/licence.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker.hpp"
#include "dogen.logical/types/entities/decoration/element_repository.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::decoration::modeline_group>& lhs,
const boost::shared_ptr<dogen::logical::entities::decoration::modeline_group>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::decoration::modeline>& lhs,
const boost::shared_ptr<dogen::logical::entities::decoration::modeline>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::decoration::licence>& lhs,
const boost::shared_ptr<dogen::logical::entities::decoration::licence>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::decoration::generation_marker>& lhs,
const boost::shared_ptr<dogen::logical::entities::decoration::generation_marker>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::entities::decoration {

element_repository::element_repository(
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& modeline_groups,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modelines,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& licences,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& generation_markers)
    : modeline_groups_(modeline_groups),
      modelines_(modelines),
      licences_(licences),
      generation_markers_(generation_markers) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(modeline_groups_, other.modeline_groups_);
    swap(modelines_, other.modelines_);
    swap(licences_, other.licences_);
    swap(generation_markers_, other.generation_markers_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return modeline_groups_ == rhs.modeline_groups_ &&
        modelines_ == rhs.modelines_ &&
        licences_ == rhs.licences_ &&
        generation_markers_ == rhs.generation_markers_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& element_repository::modeline_groups() const {
    return modeline_groups_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& element_repository::modeline_groups() {
    return modeline_groups_;
}

void element_repository::modeline_groups(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& v) {
    modeline_groups_ = v;
}

void element_repository::modeline_groups(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >&& v) {
    modeline_groups_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& element_repository::modelines() const {
    return modelines_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& element_repository::modelines() {
    return modelines_;
}

void element_repository::modelines(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& v) {
    modelines_ = v;
}

void element_repository::modelines(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >&& v) {
    modelines_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& element_repository::licences() const {
    return licences_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& element_repository::licences() {
    return licences_;
}

void element_repository::licences(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& v) {
    licences_ = v;
}

void element_repository::licences(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >&& v) {
    licences_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& element_repository::generation_markers() const {
    return generation_markers_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& element_repository::generation_markers() {
    return generation_markers_;
}

void element_repository::generation_markers(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& v) {
    generation_markers_ = v;
}

void element_repository::generation_markers(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >&& v) {
    generation_markers_ = std::move(v);
}

}
