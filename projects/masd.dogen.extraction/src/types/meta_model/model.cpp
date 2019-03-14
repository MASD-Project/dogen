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

model::model()
    : force_write_(static_cast<bool>(0)),
      delete_extra_files_(static_cast<bool>(0)),
      delete_empty_directories_(static_cast<bool>(0)) { }

model::model(model&& rhs)
    : name_(std::move(rhs.name_)),
      language_(std::move(rhs.language_)),
      artefacts_(std::move(rhs.artefacts_)),
      managed_directories_(std::move(rhs.managed_directories_)),
      force_write_(std::move(rhs.force_write_)),
      delete_extra_files_(std::move(rhs.delete_extra_files_)),
      ignore_files_matching_regex_(std::move(rhs.ignore_files_matching_regex_)),
      cpp_headers_output_directory_(std::move(rhs.cpp_headers_output_directory_)),
      delete_empty_directories_(std::move(rhs.delete_empty_directories_)),
      outputting_properties_(std::move(rhs.outputting_properties_)) { }

model::model(
    const std::string& name,
    const std::string& language,
    const std::list<masd::dogen::extraction::meta_model::artefact>& artefacts,
    const std::list<boost::filesystem::path>& managed_directories,
    const bool force_write,
    const bool delete_extra_files,
    const std::vector<std::string>& ignore_files_matching_regex,
    const boost::filesystem::path& cpp_headers_output_directory,
    const bool delete_empty_directories,
    const masd::dogen::extraction::meta_model::outputting_properties& outputting_properties)
    : name_(name),
      language_(language),
      artefacts_(artefacts),
      managed_directories_(managed_directories),
      force_write_(force_write),
      delete_extra_files_(delete_extra_files),
      ignore_files_matching_regex_(ignore_files_matching_regex),
      cpp_headers_output_directory_(cpp_headers_output_directory),
      delete_empty_directories_(delete_empty_directories),
      outputting_properties_(outputting_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(language_, other.language_);
    swap(artefacts_, other.artefacts_);
    swap(managed_directories_, other.managed_directories_);
    swap(force_write_, other.force_write_);
    swap(delete_extra_files_, other.delete_extra_files_);
    swap(ignore_files_matching_regex_, other.ignore_files_matching_regex_);
    swap(cpp_headers_output_directory_, other.cpp_headers_output_directory_);
    swap(delete_empty_directories_, other.delete_empty_directories_);
    swap(outputting_properties_, other.outputting_properties_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        language_ == rhs.language_ &&
        artefacts_ == rhs.artefacts_ &&
        managed_directories_ == rhs.managed_directories_ &&
        force_write_ == rhs.force_write_ &&
        delete_extra_files_ == rhs.delete_extra_files_ &&
        ignore_files_matching_regex_ == rhs.ignore_files_matching_regex_ &&
        cpp_headers_output_directory_ == rhs.cpp_headers_output_directory_ &&
        delete_empty_directories_ == rhs.delete_empty_directories_ &&
        outputting_properties_ == rhs.outputting_properties_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

const std::string& model::language() const {
    return language_;
}

std::string& model::language() {
    return language_;
}

void model::language(const std::string& v) {
    language_ = v;
}

void model::language(const std::string&& v) {
    language_ = std::move(v);
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

bool model::force_write() const {
    return force_write_;
}

void model::force_write(const bool v) {
    force_write_ = v;
}

bool model::delete_extra_files() const {
    return delete_extra_files_;
}

void model::delete_extra_files(const bool v) {
    delete_extra_files_ = v;
}

const std::vector<std::string>& model::ignore_files_matching_regex() const {
    return ignore_files_matching_regex_;
}

std::vector<std::string>& model::ignore_files_matching_regex() {
    return ignore_files_matching_regex_;
}

void model::ignore_files_matching_regex(const std::vector<std::string>& v) {
    ignore_files_matching_regex_ = v;
}

void model::ignore_files_matching_regex(const std::vector<std::string>&& v) {
    ignore_files_matching_regex_ = std::move(v);
}

const boost::filesystem::path& model::cpp_headers_output_directory() const {
    return cpp_headers_output_directory_;
}

boost::filesystem::path& model::cpp_headers_output_directory() {
    return cpp_headers_output_directory_;
}

void model::cpp_headers_output_directory(const boost::filesystem::path& v) {
    cpp_headers_output_directory_ = v;
}

void model::cpp_headers_output_directory(const boost::filesystem::path&& v) {
    cpp_headers_output_directory_ = std::move(v);
}

bool model::delete_empty_directories() const {
    return delete_empty_directories_;
}

void model::delete_empty_directories(const bool v) {
    delete_empty_directories_ = v;
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
