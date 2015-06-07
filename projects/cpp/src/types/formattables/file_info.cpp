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
#include "dogen/cpp/types/formattables/file_info.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::formattables::formattable>& lhs,
const boost::shared_ptr<dogen::cpp::formattables::formattable>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace cpp {
namespace formattables {

file_info::file_info(file_info&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      includes_(std::move(rhs.includes_)),
      descriptor_(std::move(rhs.descriptor_)),
      header_guard_(std::move(rhs.header_guard_)),
      file_path_(std::move(rhs.file_path_)),
      relative_path_(std::move(rhs.relative_path_)),
      formattable_(std::move(rhs.formattable_)) { }

file_info::file_info(
    const std::string& documentation,
    const dogen::cpp::formattables::includes& includes,
    const dogen::cpp::formattables::content_descriptor& descriptor,
    const std::string& header_guard,
    const boost::filesystem::path& file_path,
    const boost::filesystem::path& relative_path,
    const boost::shared_ptr<dogen::cpp::formattables::formattable>& formattable)
    : documentation_(documentation),
      includes_(includes),
      descriptor_(descriptor),
      header_guard_(header_guard),
      file_path_(file_path),
      relative_path_(relative_path),
      formattable_(formattable) { }

void file_info::swap(file_info& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(includes_, other.includes_);
    swap(descriptor_, other.descriptor_);
    swap(header_guard_, other.header_guard_);
    swap(file_path_, other.file_path_);
    swap(relative_path_, other.relative_path_);
    swap(formattable_, other.formattable_);
}

bool file_info::operator==(const file_info& rhs) const {
    return documentation_ == rhs.documentation_ &&
        includes_ == rhs.includes_ &&
        descriptor_ == rhs.descriptor_ &&
        header_guard_ == rhs.header_guard_ &&
        file_path_ == rhs.file_path_ &&
        relative_path_ == rhs.relative_path_ &&
        formattable_ == rhs.formattable_;
}

file_info& file_info::operator=(file_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& file_info::documentation() const {
    return documentation_;
}

std::string& file_info::documentation() {
    return documentation_;
}

void file_info::documentation(const std::string& v) {
    documentation_ = v;
}

void file_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::cpp::formattables::includes& file_info::includes() const {
    return includes_;
}

dogen::cpp::formattables::includes& file_info::includes() {
    return includes_;
}

void file_info::includes(const dogen::cpp::formattables::includes& v) {
    includes_ = v;
}

void file_info::includes(const dogen::cpp::formattables::includes&& v) {
    includes_ = std::move(v);
}

const dogen::cpp::formattables::content_descriptor& file_info::descriptor() const {
    return descriptor_;
}

dogen::cpp::formattables::content_descriptor& file_info::descriptor() {
    return descriptor_;
}

void file_info::descriptor(const dogen::cpp::formattables::content_descriptor& v) {
    descriptor_ = v;
}

void file_info::descriptor(const dogen::cpp::formattables::content_descriptor&& v) {
    descriptor_ = std::move(v);
}

const std::string& file_info::header_guard() const {
    return header_guard_;
}

std::string& file_info::header_guard() {
    return header_guard_;
}

void file_info::header_guard(const std::string& v) {
    header_guard_ = v;
}

void file_info::header_guard(const std::string&& v) {
    header_guard_ = std::move(v);
}

const boost::filesystem::path& file_info::file_path() const {
    return file_path_;
}

boost::filesystem::path& file_info::file_path() {
    return file_path_;
}

void file_info::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void file_info::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const boost::filesystem::path& file_info::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& file_info::relative_path() {
    return relative_path_;
}

void file_info::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void file_info::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

const boost::shared_ptr<dogen::cpp::formattables::formattable>& file_info::formattable() const {
    return formattable_;
}

boost::shared_ptr<dogen::cpp::formattables::formattable>& file_info::formattable() {
    return formattable_;
}

void file_info::formattable(const boost::shared_ptr<dogen::cpp::formattables::formattable>& v) {
    formattable_ = v;
}

void file_info::formattable(const boost::shared_ptr<dogen::cpp::formattables::formattable>&& v) {
    formattable_ = std::move(v);
}

} } }
