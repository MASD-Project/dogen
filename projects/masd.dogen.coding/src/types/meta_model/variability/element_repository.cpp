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
#include "masd.dogen.coding/types/meta_model/variability/profile_template.hpp"
#include "masd.dogen.coding/types/meta_model/variability/element_repository.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_registrar.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::coding::meta_model::variability {

element_repository::element_repository(
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& profile_templates,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >& feature_template_groups,
    const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& feature_template_group_registrar)
    : profile_templates_(profile_templates),
      feature_template_groups_(feature_template_groups),
      feature_template_group_registrar_(feature_template_group_registrar) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(profile_templates_, other.profile_templates_);
    swap(feature_template_groups_, other.feature_template_groups_);
    swap(feature_template_group_registrar_, other.feature_template_group_registrar_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return profile_templates_ == rhs.profile_templates_ &&
        feature_template_groups_ == rhs.feature_template_groups_ &&
        feature_template_group_registrar_ == rhs.feature_template_group_registrar_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& element_repository::profile_templates() const {
    return profile_templates_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& element_repository::profile_templates() {
    return profile_templates_;
}

void element_repository::profile_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& v) {
    profile_templates_ = v;
}

void element_repository::profile_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >&& v) {
    profile_templates_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >& element_repository::feature_template_groups() const {
    return feature_template_groups_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >& element_repository::feature_template_groups() {
    return feature_template_groups_;
}

void element_repository::feature_template_groups(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >& v) {
    feature_template_groups_ = v;
}

void element_repository::feature_template_groups(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >&& v) {
    feature_template_groups_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& element_repository::feature_template_group_registrar() const {
    return feature_template_group_registrar_;
}

boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& element_repository::feature_template_group_registrar() {
    return feature_template_group_registrar_;
}

void element_repository::feature_template_group_registrar(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& v) {
    feature_template_group_registrar_ = v;
}

void element_repository::feature_template_group_registrar(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>&& v) {
    feature_template_group_registrar_ = std::move(v);
}

}
