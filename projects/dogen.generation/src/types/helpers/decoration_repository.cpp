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
#include "dogen.generation/types/helpers/decoration_repository.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker.hpp"

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

namespace dogen::generation::helpers {

decoration_repository::decoration_repository(
    const std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >& modelines_by_modeline_group_by_technical_space,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& licences_by_name,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& generation_markers_by_name)
    : modelines_by_modeline_group_by_technical_space_(modelines_by_modeline_group_by_technical_space),
      licences_by_name_(licences_by_name),
      generation_markers_by_name_(generation_markers_by_name) { }

void decoration_repository::swap(decoration_repository& other) noexcept {
    using std::swap;
    swap(modelines_by_modeline_group_by_technical_space_, other.modelines_by_modeline_group_by_technical_space_);
    swap(licences_by_name_, other.licences_by_name_);
    swap(generation_markers_by_name_, other.generation_markers_by_name_);
}

bool decoration_repository::operator==(const decoration_repository& rhs) const {
    return modelines_by_modeline_group_by_technical_space_ == rhs.modelines_by_modeline_group_by_technical_space_ &&
        licences_by_name_ == rhs.licences_by_name_ &&
        generation_markers_by_name_ == rhs.generation_markers_by_name_;
}

decoration_repository& decoration_repository::operator=(decoration_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >& decoration_repository::modelines_by_modeline_group_by_technical_space() const {
    return modelines_by_modeline_group_by_technical_space_;
}

std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >& decoration_repository::modelines_by_modeline_group_by_technical_space() {
    return modelines_by_modeline_group_by_technical_space_;
}

void decoration_repository::modelines_by_modeline_group_by_technical_space(const std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >& v) {
    modelines_by_modeline_group_by_technical_space_ = v;
}

void decoration_repository::modelines_by_modeline_group_by_technical_space(const std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >&& v) {
    modelines_by_modeline_group_by_technical_space_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& decoration_repository::licences_by_name() const {
    return licences_by_name_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& decoration_repository::licences_by_name() {
    return licences_by_name_;
}

void decoration_repository::licences_by_name(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& v) {
    licences_by_name_ = v;
}

void decoration_repository::licences_by_name(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >&& v) {
    licences_by_name_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& decoration_repository::generation_markers_by_name() const {
    return generation_markers_by_name_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& decoration_repository::generation_markers_by_name() {
    return generation_markers_by_name_;
}

void decoration_repository::generation_markers_by_name(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& v) {
    generation_markers_by_name_ = v;
}

void decoration_repository::generation_markers_by_name(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >&& v) {
    generation_markers_by_name_ = std::move(v);
}

}
