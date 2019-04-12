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
#include "masd.dogen.extraction/types/meta_model/model.hpp"

namespace masd::dogen::extraction::meta_model {

model::model(
    const masd::dogen::variability::annotation& annotation,
    const std::string& name,
    const std::string& technical_space,
    const std::list<masd::dogen::extraction::meta_model::artefact>& artefacts,
    const std::list<boost::filesystem::path>& managed_directories,
    const masd::dogen::extraction::meta_model::outputting_properties& outputting_properties)
    : annotation_(annotation),
      name_(name),
      technical_space_(technical_space),
      artefacts_(artefacts),
      managed_directories_(managed_directories),
      outputting_properties_(outputting_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(annotation_, other.annotation_);
    swap(name_, other.name_);
    swap(technical_space_, other.technical_space_);
    swap(artefacts_, other.artefacts_);
    swap(managed_directories_, other.managed_directories_);
    swap(outputting_properties_, other.outputting_properties_);
}

bool model::operator==(const model& rhs) const {
    return annotation_ == rhs.annotation_ &&
        name_ == rhs.name_ &&
        technical_space_ == rhs.technical_space_ &&
        artefacts_ == rhs.artefacts_ &&
        managed_directories_ == rhs.managed_directories_ &&
        outputting_properties_ == rhs.outputting_properties_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::variability::annotation& model::annotation() const {
    return annotation_;
}

masd::dogen::variability::annotation& model::annotation() {
    return annotation_;
}

void model::annotation(const masd::dogen::variability::annotation& v) {
    annotation_ = v;
}

void model::annotation(const masd::dogen::variability::annotation&& v) {
    annotation_ = std::move(v);
}

const std::string& model::name() const {
    return name_;
}

std::string& model::name() {
    return name_;
}

void model::name(const std::string& v) {
    name_ = v;
}

void model::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& model::technical_space() const {
    return technical_space_;
}

std::string& model::technical_space() {
    return technical_space_;
}

void model::technical_space(const std::string& v) {
    technical_space_ = v;
}

void model::technical_space(const std::string&& v) {
    technical_space_ = std::move(v);
}

const std::list<masd::dogen::extraction::meta_model::artefact>& model::artefacts() const {
    return artefacts_;
}

std::list<masd::dogen::extraction::meta_model::artefact>& model::artefacts() {
    return artefacts_;
}

void model::artefacts(const std::list<masd::dogen::extraction::meta_model::artefact>& v) {
    artefacts_ = v;
}

void model::artefacts(const std::list<masd::dogen::extraction::meta_model::artefact>&& v) {
    artefacts_ = std::move(v);
}

const std::list<boost::filesystem::path>& model::managed_directories() const {
    return managed_directories_;
}

std::list<boost::filesystem::path>& model::managed_directories() {
    return managed_directories_;
}

void model::managed_directories(const std::list<boost::filesystem::path>& v) {
    managed_directories_ = v;
}

void model::managed_directories(const std::list<boost::filesystem::path>&& v) {
    managed_directories_ = std::move(v);
}

const masd::dogen::extraction::meta_model::outputting_properties& model::outputting_properties() const {
    return outputting_properties_;
}

masd::dogen::extraction::meta_model::outputting_properties& model::outputting_properties() {
    return outputting_properties_;
}

void model::outputting_properties(const masd::dogen::extraction::meta_model::outputting_properties& v) {
    outputting_properties_ = v;
}

void model::outputting_properties(const masd::dogen::extraction::meta_model::outputting_properties&& v) {
    outputting_properties_ = std::move(v);
}

}
