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
#include "dogen/quilt.cpp/types/formattables/artefact_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

artefact_properties::artefact_properties()
    : enabled_(static_cast<bool>(0)),
      overwrite_(static_cast<bool>(0)),
      formatting_style_(static_cast<dogen::quilt::cpp::formattables::formatting_styles>(0)) { }

artefact_properties::artefact_properties(artefact_properties&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      overwrite_(std::move(rhs.overwrite_)),
      file_path_(std::move(rhs.file_path_)),
      header_guard_(std::move(rhs.header_guard_)),
      inclusion_dependencies_(std::move(rhs.inclusion_dependencies_)),
      formatting_style_(std::move(rhs.formatting_style_)),
      formatting_input_(std::move(rhs.formatting_input_)) { }

artefact_properties::artefact_properties(
    const bool enabled,
    const bool overwrite,
    const boost::filesystem::path& file_path,
    const std::string& header_guard,
    const std::list<std::string>& inclusion_dependencies,
    const dogen::quilt::cpp::formattables::formatting_styles formatting_style,
    const std::string& formatting_input)
    : enabled_(enabled),
      overwrite_(overwrite),
      file_path_(file_path),
      header_guard_(header_guard),
      inclusion_dependencies_(inclusion_dependencies),
      formatting_style_(formatting_style),
      formatting_input_(formatting_input) { }

void artefact_properties::swap(artefact_properties& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
    swap(file_path_, other.file_path_);
    swap(header_guard_, other.header_guard_);
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
    swap(formatting_style_, other.formatting_style_);
    swap(formatting_input_, other.formatting_input_);
}

bool artefact_properties::operator==(const artefact_properties& rhs) const {
    return enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_ &&
        file_path_ == rhs.file_path_ &&
        header_guard_ == rhs.header_guard_ &&
        inclusion_dependencies_ == rhs.inclusion_dependencies_ &&
        formatting_style_ == rhs.formatting_style_ &&
        formatting_input_ == rhs.formatting_input_;
}

artefact_properties& artefact_properties::operator=(artefact_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool artefact_properties::enabled() const {
    return enabled_;
}

void artefact_properties::enabled(const bool v) {
    enabled_ = v;
}

bool artefact_properties::overwrite() const {
    return overwrite_;
}

void artefact_properties::overwrite(const bool v) {
    overwrite_ = v;
}

const boost::filesystem::path& artefact_properties::file_path() const {
    return file_path_;
}

boost::filesystem::path& artefact_properties::file_path() {
    return file_path_;
}

void artefact_properties::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void artefact_properties::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const std::string& artefact_properties::header_guard() const {
    return header_guard_;
}

std::string& artefact_properties::header_guard() {
    return header_guard_;
}

void artefact_properties::header_guard(const std::string& v) {
    header_guard_ = v;
}

void artefact_properties::header_guard(const std::string&& v) {
    header_guard_ = std::move(v);
}

const std::list<std::string>& artefact_properties::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<std::string>& artefact_properties::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void artefact_properties::inclusion_dependencies(const std::list<std::string>& v) {
    inclusion_dependencies_ = v;
}

void artefact_properties::inclusion_dependencies(const std::list<std::string>&& v) {
    inclusion_dependencies_ = std::move(v);
}

dogen::quilt::cpp::formattables::formatting_styles artefact_properties::formatting_style() const {
    return formatting_style_;
}

void artefact_properties::formatting_style(const dogen::quilt::cpp::formattables::formatting_styles v) {
    formatting_style_ = v;
}

const std::string& artefact_properties::formatting_input() const {
    return formatting_input_;
}

std::string& artefact_properties::formatting_input() {
    return formatting_input_;
}

void artefact_properties::formatting_input(const std::string& v) {
    formatting_input_ = v;
}

void artefact_properties::formatting_input(const std::string&& v) {
    formatting_input_ = std::move(v);
}

} } } }
