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
#include "dogen/formatters/types/general_property_sheet.hpp"

namespace dogen {
namespace formatters {

general_property_sheet::general_property_sheet()
    : enabled_(static_cast<bool>(0)),
      generate_preamble_(static_cast<bool>(0)),
      enable_facet_directories_(static_cast<bool>(0)),
      overwrite_(static_cast<bool>(0)),
      enable_unique_file_names_(static_cast<bool>(0)) { }

general_property_sheet::general_property_sheet(
    const bool enabled,
    const bool generate_preamble,
    const std::list<std::string>& copyright,
    const std::string& licence_name,
    const std::string& modeline_group_name,
    const dogen::formatters::code_generation_marker_property_sheet& code_generation_marker,
    const std::string& feature_directory_name,
    const bool enable_facet_directories,
    const std::string& facet_directory_name,
    const std::string& facet_postfix,
    const bool overwrite,
    const std::string& file_name,
    const std::string& file_postfix,
    const std::string& extension,
    const bool enable_unique_file_names)
    : enabled_(enabled),
      generate_preamble_(generate_preamble),
      copyright_(copyright),
      licence_name_(licence_name),
      modeline_group_name_(modeline_group_name),
      code_generation_marker_(code_generation_marker),
      feature_directory_name_(feature_directory_name),
      enable_facet_directories_(enable_facet_directories),
      facet_directory_name_(facet_directory_name),
      facet_postfix_(facet_postfix),
      overwrite_(overwrite),
      file_name_(file_name),
      file_postfix_(file_postfix),
      extension_(extension),
      enable_unique_file_names_(enable_unique_file_names) { }

void general_property_sheet::swap(general_property_sheet& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(generate_preamble_, other.generate_preamble_);
    swap(copyright_, other.copyright_);
    swap(licence_name_, other.licence_name_);
    swap(modeline_group_name_, other.modeline_group_name_);
    swap(code_generation_marker_, other.code_generation_marker_);
    swap(feature_directory_name_, other.feature_directory_name_);
    swap(enable_facet_directories_, other.enable_facet_directories_);
    swap(facet_directory_name_, other.facet_directory_name_);
    swap(facet_postfix_, other.facet_postfix_);
    swap(overwrite_, other.overwrite_);
    swap(file_name_, other.file_name_);
    swap(file_postfix_, other.file_postfix_);
    swap(extension_, other.extension_);
    swap(enable_unique_file_names_, other.enable_unique_file_names_);
}

bool general_property_sheet::operator==(const general_property_sheet& rhs) const {
    return enabled_ == rhs.enabled_ &&
        generate_preamble_ == rhs.generate_preamble_ &&
        copyright_ == rhs.copyright_ &&
        licence_name_ == rhs.licence_name_ &&
        modeline_group_name_ == rhs.modeline_group_name_ &&
        code_generation_marker_ == rhs.code_generation_marker_ &&
        feature_directory_name_ == rhs.feature_directory_name_ &&
        enable_facet_directories_ == rhs.enable_facet_directories_ &&
        facet_directory_name_ == rhs.facet_directory_name_ &&
        facet_postfix_ == rhs.facet_postfix_ &&
        overwrite_ == rhs.overwrite_ &&
        file_name_ == rhs.file_name_ &&
        file_postfix_ == rhs.file_postfix_ &&
        extension_ == rhs.extension_ &&
        enable_unique_file_names_ == rhs.enable_unique_file_names_;
}

general_property_sheet& general_property_sheet::operator=(general_property_sheet other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool general_property_sheet::enabled() const {
    return enabled_;
}

void general_property_sheet::enabled(const bool v) {
    enabled_ = v;
}

bool general_property_sheet::generate_preamble() const {
    return generate_preamble_;
}

void general_property_sheet::generate_preamble(const bool v) {
    generate_preamble_ = v;
}

const std::list<std::string>& general_property_sheet::copyright() const {
    return copyright_;
}

std::list<std::string>& general_property_sheet::copyright() {
    return copyright_;
}

void general_property_sheet::copyright(const std::list<std::string>& v) {
    copyright_ = v;
}

void general_property_sheet::copyright(const std::list<std::string>&& v) {
    copyright_ = std::move(v);
}

const std::string& general_property_sheet::licence_name() const {
    return licence_name_;
}

std::string& general_property_sheet::licence_name() {
    return licence_name_;
}

void general_property_sheet::licence_name(const std::string& v) {
    licence_name_ = v;
}

void general_property_sheet::licence_name(const std::string&& v) {
    licence_name_ = std::move(v);
}

const std::string& general_property_sheet::modeline_group_name() const {
    return modeline_group_name_;
}

std::string& general_property_sheet::modeline_group_name() {
    return modeline_group_name_;
}

void general_property_sheet::modeline_group_name(const std::string& v) {
    modeline_group_name_ = v;
}

void general_property_sheet::modeline_group_name(const std::string&& v) {
    modeline_group_name_ = std::move(v);
}

const dogen::formatters::code_generation_marker_property_sheet& general_property_sheet::code_generation_marker() const {
    return code_generation_marker_;
}

dogen::formatters::code_generation_marker_property_sheet& general_property_sheet::code_generation_marker() {
    return code_generation_marker_;
}

void general_property_sheet::code_generation_marker(const dogen::formatters::code_generation_marker_property_sheet& v) {
    code_generation_marker_ = v;
}

void general_property_sheet::code_generation_marker(const dogen::formatters::code_generation_marker_property_sheet&& v) {
    code_generation_marker_ = std::move(v);
}

const std::string& general_property_sheet::feature_directory_name() const {
    return feature_directory_name_;
}

std::string& general_property_sheet::feature_directory_name() {
    return feature_directory_name_;
}

void general_property_sheet::feature_directory_name(const std::string& v) {
    feature_directory_name_ = v;
}

void general_property_sheet::feature_directory_name(const std::string&& v) {
    feature_directory_name_ = std::move(v);
}

bool general_property_sheet::enable_facet_directories() const {
    return enable_facet_directories_;
}

void general_property_sheet::enable_facet_directories(const bool v) {
    enable_facet_directories_ = v;
}

const std::string& general_property_sheet::facet_directory_name() const {
    return facet_directory_name_;
}

std::string& general_property_sheet::facet_directory_name() {
    return facet_directory_name_;
}

void general_property_sheet::facet_directory_name(const std::string& v) {
    facet_directory_name_ = v;
}

void general_property_sheet::facet_directory_name(const std::string&& v) {
    facet_directory_name_ = std::move(v);
}

const std::string& general_property_sheet::facet_postfix() const {
    return facet_postfix_;
}

std::string& general_property_sheet::facet_postfix() {
    return facet_postfix_;
}

void general_property_sheet::facet_postfix(const std::string& v) {
    facet_postfix_ = v;
}

void general_property_sheet::facet_postfix(const std::string&& v) {
    facet_postfix_ = std::move(v);
}

bool general_property_sheet::overwrite() const {
    return overwrite_;
}

void general_property_sheet::overwrite(const bool v) {
    overwrite_ = v;
}

const std::string& general_property_sheet::file_name() const {
    return file_name_;
}

std::string& general_property_sheet::file_name() {
    return file_name_;
}

void general_property_sheet::file_name(const std::string& v) {
    file_name_ = v;
}

void general_property_sheet::file_name(const std::string&& v) {
    file_name_ = std::move(v);
}

const std::string& general_property_sheet::file_postfix() const {
    return file_postfix_;
}

std::string& general_property_sheet::file_postfix() {
    return file_postfix_;
}

void general_property_sheet::file_postfix(const std::string& v) {
    file_postfix_ = v;
}

void general_property_sheet::file_postfix(const std::string&& v) {
    file_postfix_ = std::move(v);
}

const std::string& general_property_sheet::extension() const {
    return extension_;
}

std::string& general_property_sheet::extension() {
    return extension_;
}

void general_property_sheet::extension(const std::string& v) {
    extension_ = v;
}

void general_property_sheet::extension(const std::string&& v) {
    extension_ = std::move(v);
}

bool general_property_sheet::enable_unique_file_names() const {
    return enable_unique_file_names_;
}

void general_property_sheet::enable_unique_file_names(const bool v) {
    enable_unique_file_names_ = v;
}

} }