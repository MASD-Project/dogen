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
#include <ostream>
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/formatters/io/general_settings_io.hpp"
#include "dogen/cpp/io/formattables/formattable_io.hpp"
#include "dogen/cpp/types/formattables/cmakelists_info.hpp"

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
namespace cpp {
namespace formattables {

cmakelists_info::cmakelists_info()
    : odb_enabled_(static_cast<bool>(0)) { }

cmakelists_info::cmakelists_info(cmakelists_info&& rhs)
    : dogen::cpp::formattables::formattable(
        std::forward<dogen::cpp::formattables::formattable>(rhs)),
      file_path_(std::move(rhs.file_path_)),
      model_name_(std::move(rhs.model_name_)),
      product_name_(std::move(rhs.product_name_)),
      file_name_(std::move(rhs.file_name_)),
      source_file_path_(std::move(rhs.source_file_path_)),
      include_file_path_(std::move(rhs.include_file_path_)),
      general_settings_(std::move(rhs.general_settings_)),
      odb_folder_(std::move(rhs.odb_folder_)),
      odb_enabled_(std::move(rhs.odb_enabled_)) { }

cmakelists_info::cmakelists_info(
    const std::string& identity,
    const dogen::cpp::formattables::origin_types origin_type,
    const boost::filesystem::path& file_path,
    const std::string& model_name,
    const std::string& product_name,
    const std::string& file_name,
    const boost::filesystem::path& source_file_path,
    const boost::filesystem::path& include_file_path,
    const boost::optional<dogen::formatters::general_settings>& general_settings,
    const std::string& odb_folder,
    const bool odb_enabled)
    : dogen::cpp::formattables::formattable(
      identity,
      origin_type),
      file_path_(file_path),
      model_name_(model_name),
      product_name_(product_name),
      file_name_(file_name),
      source_file_path_(source_file_path),
      include_file_path_(include_file_path),
      general_settings_(general_settings),
      odb_folder_(odb_folder),
      odb_enabled_(odb_enabled) { }

void cmakelists_info::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::cmakelists_info\"" << ", "
      << "\"__parent_0__\": ";
    formattable::to_stream(s);
    s << ", "
      << "\"file_path\": " << "\"" << file_path_.generic_string() << "\"" << ", "
      << "\"model_name\": " << "\"" << tidy_up_string(model_name_) << "\"" << ", "
      << "\"product_name\": " << "\"" << tidy_up_string(product_name_) << "\"" << ", "
      << "\"file_name\": " << "\"" << tidy_up_string(file_name_) << "\"" << ", "
      << "\"source_file_path\": " << "\"" << source_file_path_.generic_string() << "\"" << ", "
      << "\"include_file_path\": " << "\"" << include_file_path_.generic_string() << "\"" << ", "
      << "\"general_settings\": " << general_settings_ << ", "
      << "\"odb_folder\": " << "\"" << tidy_up_string(odb_folder_) << "\"" << ", "
      << "\"odb_enabled\": " << odb_enabled_
      << " }";
}

void cmakelists_info::swap(cmakelists_info& other) noexcept {
    formattable::swap(other);

    using std::swap;
    swap(file_path_, other.file_path_);
    swap(model_name_, other.model_name_);
    swap(product_name_, other.product_name_);
    swap(file_name_, other.file_name_);
    swap(source_file_path_, other.source_file_path_);
    swap(include_file_path_, other.include_file_path_);
    swap(general_settings_, other.general_settings_);
    swap(odb_folder_, other.odb_folder_);
    swap(odb_enabled_, other.odb_enabled_);
}

bool cmakelists_info::equals(const dogen::cpp::formattables::formattable& other) const {
    const cmakelists_info* const p(dynamic_cast<const cmakelists_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cmakelists_info::operator==(const cmakelists_info& rhs) const {
    return formattable::compare(rhs) &&
        file_path_ == rhs.file_path_ &&
        model_name_ == rhs.model_name_ &&
        product_name_ == rhs.product_name_ &&
        file_name_ == rhs.file_name_ &&
        source_file_path_ == rhs.source_file_path_ &&
        include_file_path_ == rhs.include_file_path_ &&
        general_settings_ == rhs.general_settings_ &&
        odb_folder_ == rhs.odb_folder_ &&
        odb_enabled_ == rhs.odb_enabled_;
}

cmakelists_info& cmakelists_info::operator=(cmakelists_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& cmakelists_info::file_path() const {
    return file_path_;
}

boost::filesystem::path& cmakelists_info::file_path() {
    return file_path_;
}

void cmakelists_info::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void cmakelists_info::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const std::string& cmakelists_info::model_name() const {
    return model_name_;
}

std::string& cmakelists_info::model_name() {
    return model_name_;
}

void cmakelists_info::model_name(const std::string& v) {
    model_name_ = v;
}

void cmakelists_info::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

const std::string& cmakelists_info::product_name() const {
    return product_name_;
}

std::string& cmakelists_info::product_name() {
    return product_name_;
}

void cmakelists_info::product_name(const std::string& v) {
    product_name_ = v;
}

void cmakelists_info::product_name(const std::string&& v) {
    product_name_ = std::move(v);
}

const std::string& cmakelists_info::file_name() const {
    return file_name_;
}

std::string& cmakelists_info::file_name() {
    return file_name_;
}

void cmakelists_info::file_name(const std::string& v) {
    file_name_ = v;
}

void cmakelists_info::file_name(const std::string&& v) {
    file_name_ = std::move(v);
}

const boost::filesystem::path& cmakelists_info::source_file_path() const {
    return source_file_path_;
}

boost::filesystem::path& cmakelists_info::source_file_path() {
    return source_file_path_;
}

void cmakelists_info::source_file_path(const boost::filesystem::path& v) {
    source_file_path_ = v;
}

void cmakelists_info::source_file_path(const boost::filesystem::path&& v) {
    source_file_path_ = std::move(v);
}

const boost::filesystem::path& cmakelists_info::include_file_path() const {
    return include_file_path_;
}

boost::filesystem::path& cmakelists_info::include_file_path() {
    return include_file_path_;
}

void cmakelists_info::include_file_path(const boost::filesystem::path& v) {
    include_file_path_ = v;
}

void cmakelists_info::include_file_path(const boost::filesystem::path&& v) {
    include_file_path_ = std::move(v);
}

const boost::optional<dogen::formatters::general_settings>& cmakelists_info::general_settings() const {
    return general_settings_;
}

boost::optional<dogen::formatters::general_settings>& cmakelists_info::general_settings() {
    return general_settings_;
}

void cmakelists_info::general_settings(const boost::optional<dogen::formatters::general_settings>& v) {
    general_settings_ = v;
}

void cmakelists_info::general_settings(const boost::optional<dogen::formatters::general_settings>&& v) {
    general_settings_ = std::move(v);
}

const std::string& cmakelists_info::odb_folder() const {
    return odb_folder_;
}

std::string& cmakelists_info::odb_folder() {
    return odb_folder_;
}

void cmakelists_info::odb_folder(const std::string& v) {
    odb_folder_ = v;
}

void cmakelists_info::odb_folder(const std::string&& v) {
    odb_folder_ = std::move(v);
}

bool cmakelists_info::odb_enabled() const {
    return odb_enabled_;
}

void cmakelists_info::odb_enabled(const bool v) {
    odb_enabled_ = v;
}

} } }
