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
#include <boost/algorithm/string.hpp>
#include "dogen/cpp/io/formattables/formattable_io.hpp"
#include "dogen/cpp/types/formattables/cmakelists_info.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace cpp {
namespace formattables {

cmakelists_info::cmakelists_info(cmakelists_info&& rhs)
    : dogen::cpp::formattables::formattable(
        std::forward<dogen::cpp::formattables::formattable>(rhs)),
      file_path_(std::move(rhs.file_path_)),
      model_name_(std::move(rhs.model_name_)),
      product_name_(std::move(rhs.product_name_)),
      file_name_(std::move(rhs.file_name_)) { }

cmakelists_info::cmakelists_info(
    const std::string& identity,
    const dogen::cpp::formattables::origin_types origin_type,
    const boost::filesystem::path& file_path,
    const std::string& model_name,
    const std::string& product_name,
    const std::string& file_name)
    : dogen::cpp::formattables::formattable(
      identity,
      origin_type),
      file_path_(file_path),
      model_name_(model_name),
      product_name_(product_name),
      file_name_(file_name) { }

void cmakelists_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::cmakelists_info\"" << ", "
      << "\"__parent_0__\": ";
    formattable::to_stream(s);
    s << ", "
      << "\"file_path\": " << "\"" << file_path_.generic_string() << "\"" << ", "
      << "\"model_name\": " << "\"" << tidy_up_string(model_name_) << "\"" << ", "
      << "\"product_name\": " << "\"" << tidy_up_string(product_name_) << "\"" << ", "
      << "\"file_name\": " << "\"" << tidy_up_string(file_name_) << "\""
      << " }";
}

void cmakelists_info::swap(cmakelists_info& other) noexcept {
    formattable::swap(other);

    using std::swap;
    swap(file_path_, other.file_path_);
    swap(model_name_, other.model_name_);
    swap(product_name_, other.product_name_);
    swap(file_name_, other.file_name_);
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
        file_name_ == rhs.file_name_;
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

} } }
