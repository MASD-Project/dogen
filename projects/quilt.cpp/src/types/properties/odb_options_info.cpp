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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen/formatters/io/general_settings_io.hpp"
#include "dogen/quilt.cpp/io/properties/formattable_io.hpp"
#include "dogen/quilt.cpp/types/properties/odb_options_info.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::formatters::general_settings>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s << " }";
    return s;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

odb_options_info::odb_options_info(odb_options_info&& rhs)
    : dogen::quilt::cpp::properties::formattable(
        std::forward<dogen::quilt::cpp::properties::formattable>(rhs)),
      model_name_(std::move(rhs.model_name_)),
      product_name_(std::move(rhs.product_name_)),
      file_path_(std::move(rhs.file_path_)),
      file_name_(std::move(rhs.file_name_)),
      odb_folder_(std::move(rhs.odb_folder_)),
      general_settings_(std::move(rhs.general_settings_)) { }

odb_options_info::odb_options_info(
    const std::string& identity,
    const dogen::quilt::cpp::properties::origin_types origin_type,
    const std::string& id,
    const std::string& model_name,
    const std::string& product_name,
    const boost::filesystem::path& file_path,
    const std::string& file_name,
    const std::string& odb_folder,
    const boost::optional<dogen::formatters::general_settings>& general_settings)
    : dogen::quilt::cpp::properties::formattable(
      identity,
      origin_type,
      id),
      model_name_(model_name),
      product_name_(product_name),
      file_path_(file_path),
      file_name_(file_name),
      odb_folder_(odb_folder),
      general_settings_(general_settings) { }

void odb_options_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::properties::odb_options_info\"" << ", "
      << "\"__parent_0__\": ";
    formattable::to_stream(s);
    s << ", "
      << "\"model_name\": " << "\"" << tidy_up_string(model_name_) << "\"" << ", "
      << "\"product_name\": " << "\"" << tidy_up_string(product_name_) << "\"" << ", "
      << "\"file_path\": " << "\"" << file_path_.generic_string() << "\"" << ", "
      << "\"file_name\": " << "\"" << tidy_up_string(file_name_) << "\"" << ", "
      << "\"odb_folder\": " << "\"" << tidy_up_string(odb_folder_) << "\"" << ", "
      << "\"general_settings\": " << general_settings_
      << " }";
}

void odb_options_info::swap(odb_options_info& other) noexcept {
    formattable::swap(other);

    using std::swap;
    swap(model_name_, other.model_name_);
    swap(product_name_, other.product_name_);
    swap(file_path_, other.file_path_);
    swap(file_name_, other.file_name_);
    swap(odb_folder_, other.odb_folder_);
    swap(general_settings_, other.general_settings_);
}

bool odb_options_info::equals(const dogen::quilt::cpp::properties::formattable& other) const {
    const odb_options_info* const p(dynamic_cast<const odb_options_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool odb_options_info::operator==(const odb_options_info& rhs) const {
    return formattable::compare(rhs) &&
        model_name_ == rhs.model_name_ &&
        product_name_ == rhs.product_name_ &&
        file_path_ == rhs.file_path_ &&
        file_name_ == rhs.file_name_ &&
        odb_folder_ == rhs.odb_folder_ &&
        general_settings_ == rhs.general_settings_;
}

odb_options_info& odb_options_info::operator=(odb_options_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& odb_options_info::model_name() const {
    return model_name_;
}

std::string& odb_options_info::model_name() {
    return model_name_;
}

void odb_options_info::model_name(const std::string& v) {
    model_name_ = v;
}

void odb_options_info::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

const std::string& odb_options_info::product_name() const {
    return product_name_;
}

std::string& odb_options_info::product_name() {
    return product_name_;
}

void odb_options_info::product_name(const std::string& v) {
    product_name_ = v;
}

void odb_options_info::product_name(const std::string&& v) {
    product_name_ = std::move(v);
}

const boost::filesystem::path& odb_options_info::file_path() const {
    return file_path_;
}

boost::filesystem::path& odb_options_info::file_path() {
    return file_path_;
}

void odb_options_info::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void odb_options_info::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const std::string& odb_options_info::file_name() const {
    return file_name_;
}

std::string& odb_options_info::file_name() {
    return file_name_;
}

void odb_options_info::file_name(const std::string& v) {
    file_name_ = v;
}

void odb_options_info::file_name(const std::string&& v) {
    file_name_ = std::move(v);
}

const std::string& odb_options_info::odb_folder() const {
    return odb_folder_;
}

std::string& odb_options_info::odb_folder() {
    return odb_folder_;
}

void odb_options_info::odb_folder(const std::string& v) {
    odb_folder_ = v;
}

void odb_options_info::odb_folder(const std::string&& v) {
    odb_folder_ = std::move(v);
}

const boost::optional<dogen::formatters::general_settings>& odb_options_info::general_settings() const {
    return general_settings_;
}

boost::optional<dogen::formatters::general_settings>& odb_options_info::general_settings() {
    return general_settings_;
}

void odb_options_info::general_settings(const boost::optional<dogen::formatters::general_settings>& v) {
    general_settings_ = v;
}

void odb_options_info::general_settings(const boost::optional<dogen::formatters::general_settings>&& v) {
    general_settings_ = std::move(v);
}

} } } }
