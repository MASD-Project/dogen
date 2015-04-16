/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/stitch/types/stitching_settings.hpp"

namespace dogen {
namespace stitch {

stitching_settings::stitching_settings(stitching_settings&& rhs)
    : stream_variable_name_(std::move(rhs.stream_variable_name_)),
      template_path_(std::move(rhs.template_path_)),
      output_path_(std::move(rhs.output_path_)),
      relative_output_directory_(std::move(rhs.relative_output_directory_)),
      inclusion_dependencies_(std::move(rhs.inclusion_dependencies_)) { }

stitching_settings::stitching_settings(
    const std::string& stream_variable_name,
    const boost::optional<boost::filesystem::path>& template_path,
    const boost::optional<boost::filesystem::path>& output_path,
    const boost::optional<boost::filesystem::path>& relative_output_directory,
    const std::list<std::string>& inclusion_dependencies)
    : stream_variable_name_(stream_variable_name),
      template_path_(template_path),
      output_path_(output_path),
      relative_output_directory_(relative_output_directory),
      inclusion_dependencies_(inclusion_dependencies) { }

void stitching_settings::swap(stitching_settings& other) noexcept {
    using std::swap;
    swap(stream_variable_name_, other.stream_variable_name_);
    swap(template_path_, other.template_path_);
    swap(output_path_, other.output_path_);
    swap(relative_output_directory_, other.relative_output_directory_);
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
}

bool stitching_settings::operator==(const stitching_settings& rhs) const {
    return stream_variable_name_ == rhs.stream_variable_name_ &&
        template_path_ == rhs.template_path_ &&
        output_path_ == rhs.output_path_ &&
        relative_output_directory_ == rhs.relative_output_directory_ &&
        inclusion_dependencies_ == rhs.inclusion_dependencies_;
}

stitching_settings& stitching_settings::operator=(stitching_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& stitching_settings::stream_variable_name() const {
    return stream_variable_name_;
}

std::string& stitching_settings::stream_variable_name() {
    return stream_variable_name_;
}

void stitching_settings::stream_variable_name(const std::string& v) {
    stream_variable_name_ = v;
}

void stitching_settings::stream_variable_name(const std::string&& v) {
    stream_variable_name_ = std::move(v);
}

const boost::optional<boost::filesystem::path>& stitching_settings::template_path() const {
    return template_path_;
}

boost::optional<boost::filesystem::path>& stitching_settings::template_path() {
    return template_path_;
}

void stitching_settings::template_path(const boost::optional<boost::filesystem::path>& v) {
    template_path_ = v;
}

void stitching_settings::template_path(const boost::optional<boost::filesystem::path>&& v) {
    template_path_ = std::move(v);
}

const boost::optional<boost::filesystem::path>& stitching_settings::output_path() const {
    return output_path_;
}

boost::optional<boost::filesystem::path>& stitching_settings::output_path() {
    return output_path_;
}

void stitching_settings::output_path(const boost::optional<boost::filesystem::path>& v) {
    output_path_ = v;
}

void stitching_settings::output_path(const boost::optional<boost::filesystem::path>&& v) {
    output_path_ = std::move(v);
}

const boost::optional<boost::filesystem::path>& stitching_settings::relative_output_directory() const {
    return relative_output_directory_;
}

boost::optional<boost::filesystem::path>& stitching_settings::relative_output_directory() {
    return relative_output_directory_;
}

void stitching_settings::relative_output_directory(const boost::optional<boost::filesystem::path>& v) {
    relative_output_directory_ = v;
}

void stitching_settings::relative_output_directory(const boost::optional<boost::filesystem::path>&& v) {
    relative_output_directory_ = std::move(v);
}

const std::list<std::string>& stitching_settings::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<std::string>& stitching_settings::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void stitching_settings::inclusion_dependencies(const std::list<std::string>& v) {
    inclusion_dependencies_ = v;
}

void stitching_settings::inclusion_dependencies(const std::list<std::string>&& v) {
    inclusion_dependencies_ = std::move(v);
}

} }