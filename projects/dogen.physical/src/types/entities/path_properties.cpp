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
#include "dogen.physical/types/entities/path_properties.hpp"

namespace dogen::physical::entities {

path_properties::path_properties(path_properties&& rhs)
    : file_path_(std::move(rhs.file_path_)),
      header_guard_(std::move(rhs.header_guard_)),
      inclusion_path_(std::move(rhs.inclusion_path_)),
      inclusion_directives_(std::move(rhs.inclusion_directives_)),
      inclusion_dependencies_(std::move(rhs.inclusion_dependencies_)),
      using_dependencies_(std::move(rhs.using_dependencies_)),
      relative_path_(std::move(rhs.relative_path_)) { }

path_properties::path_properties(
    const boost::filesystem::path& file_path,
    const std::string& header_guard,
    const boost::filesystem::path& inclusion_path,
    const dogen::physical::entities::inclusion_directives& inclusion_directives,
    const std::list<std::string>& inclusion_dependencies,
    const std::list<std::string>& using_dependencies,
    const boost::filesystem::path& relative_path)
    : file_path_(file_path),
      header_guard_(header_guard),
      inclusion_path_(inclusion_path),
      inclusion_directives_(inclusion_directives),
      inclusion_dependencies_(inclusion_dependencies),
      using_dependencies_(using_dependencies),
      relative_path_(relative_path) { }

void path_properties::swap(path_properties& other) noexcept {
    using std::swap;
    swap(file_path_, other.file_path_);
    swap(header_guard_, other.header_guard_);
    swap(inclusion_path_, other.inclusion_path_);
    swap(inclusion_directives_, other.inclusion_directives_);
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
    swap(using_dependencies_, other.using_dependencies_);
    swap(relative_path_, other.relative_path_);
}

bool path_properties::operator==(const path_properties& rhs) const {
    return file_path_ == rhs.file_path_ &&
        header_guard_ == rhs.header_guard_ &&
        inclusion_path_ == rhs.inclusion_path_ &&
        inclusion_directives_ == rhs.inclusion_directives_ &&
        inclusion_dependencies_ == rhs.inclusion_dependencies_ &&
        using_dependencies_ == rhs.using_dependencies_ &&
        relative_path_ == rhs.relative_path_;
}

path_properties& path_properties::operator=(path_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& path_properties::file_path() const {
    return file_path_;
}

boost::filesystem::path& path_properties::file_path() {
    return file_path_;
}

void path_properties::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void path_properties::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const std::string& path_properties::header_guard() const {
    return header_guard_;
}

std::string& path_properties::header_guard() {
    return header_guard_;
}

void path_properties::header_guard(const std::string& v) {
    header_guard_ = v;
}

void path_properties::header_guard(const std::string&& v) {
    header_guard_ = std::move(v);
}

const boost::filesystem::path& path_properties::inclusion_path() const {
    return inclusion_path_;
}

boost::filesystem::path& path_properties::inclusion_path() {
    return inclusion_path_;
}

void path_properties::inclusion_path(const boost::filesystem::path& v) {
    inclusion_path_ = v;
}

void path_properties::inclusion_path(const boost::filesystem::path&& v) {
    inclusion_path_ = std::move(v);
}

const dogen::physical::entities::inclusion_directives& path_properties::inclusion_directives() const {
    return inclusion_directives_;
}

dogen::physical::entities::inclusion_directives& path_properties::inclusion_directives() {
    return inclusion_directives_;
}

void path_properties::inclusion_directives(const dogen::physical::entities::inclusion_directives& v) {
    inclusion_directives_ = v;
}

void path_properties::inclusion_directives(const dogen::physical::entities::inclusion_directives&& v) {
    inclusion_directives_ = std::move(v);
}

const std::list<std::string>& path_properties::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<std::string>& path_properties::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void path_properties::inclusion_dependencies(const std::list<std::string>& v) {
    inclusion_dependencies_ = v;
}

void path_properties::inclusion_dependencies(const std::list<std::string>&& v) {
    inclusion_dependencies_ = std::move(v);
}

const std::list<std::string>& path_properties::using_dependencies() const {
    return using_dependencies_;
}

std::list<std::string>& path_properties::using_dependencies() {
    return using_dependencies_;
}

void path_properties::using_dependencies(const std::list<std::string>& v) {
    using_dependencies_ = v;
}

void path_properties::using_dependencies(const std::list<std::string>&& v) {
    using_dependencies_ = std::move(v);
}

const boost::filesystem::path& path_properties::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& path_properties::relative_path() {
    return relative_path_;
}

void path_properties::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void path_properties::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

}
