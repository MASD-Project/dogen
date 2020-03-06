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
#include "dogen.assets/types/meta_model/variability/feature_bundle.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template.hpp"
#include "dogen.assets/types/meta_model/variability/element_repository.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_bundle.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_initializer.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::assets::meta_model::variability::profile_template>& lhs,
const boost::shared_ptr<dogen::assets::meta_model::variability::profile_template>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_bundle>& lhs,
const boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_bundle>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::assets::meta_model::variability::feature_bundle>& lhs,
const boost::shared_ptr<dogen::assets::meta_model::variability::feature_bundle>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_initializer>& lhs,
const boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_initializer>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::assets::meta_model::variability {

element_repository::element_repository(
    const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::profile_template> >& profile_templates,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_bundle> >& feature_template_bundles,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_bundle> >& feature_bundles,
    const boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_initializer>& feature_template_initializer)
    : profile_templates_(profile_templates),
      feature_template_bundles_(feature_template_bundles),
      feature_bundles_(feature_bundles),
      feature_template_initializer_(feature_template_initializer) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(profile_templates_, other.profile_templates_);
    swap(feature_template_bundles_, other.feature_template_bundles_);
    swap(feature_bundles_, other.feature_bundles_);
    swap(feature_template_initializer_, other.feature_template_initializer_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return profile_templates_ == rhs.profile_templates_ &&
        feature_template_bundles_ == rhs.feature_template_bundles_ &&
        feature_bundles_ == rhs.feature_bundles_ &&
        feature_template_initializer_ == rhs.feature_template_initializer_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::profile_template> >& element_repository::profile_templates() const {
    return profile_templates_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::profile_template> >& element_repository::profile_templates() {
    return profile_templates_;
}

void element_repository::profile_templates(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::profile_template> >& v) {
    profile_templates_ = v;
}

void element_repository::profile_templates(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::profile_template> >&& v) {
    profile_templates_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_bundle> >& element_repository::feature_template_bundles() const {
    return feature_template_bundles_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_bundle> >& element_repository::feature_template_bundles() {
    return feature_template_bundles_;
}

void element_repository::feature_template_bundles(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_bundle> >& v) {
    feature_template_bundles_ = v;
}

void element_repository::feature_template_bundles(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_bundle> >&& v) {
    feature_template_bundles_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_bundle> >& element_repository::feature_bundles() const {
    return feature_bundles_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_bundle> >& element_repository::feature_bundles() {
    return feature_bundles_;
}

void element_repository::feature_bundles(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_bundle> >& v) {
    feature_bundles_ = v;
}

void element_repository::feature_bundles(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::variability::feature_bundle> >&& v) {
    feature_bundles_ = std::move(v);
}

const boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_initializer>& element_repository::feature_template_initializer() const {
    return feature_template_initializer_;
}

boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_initializer>& element_repository::feature_template_initializer() {
    return feature_template_initializer_;
}

void element_repository::feature_template_initializer(const boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_initializer>& v) {
    feature_template_initializer_ = v;
}

void element_repository::feature_template_initializer(const boost::shared_ptr<dogen::assets::meta_model::variability::feature_template_initializer>&& v) {
    feature_template_initializer_ = std::move(v);
}

}
