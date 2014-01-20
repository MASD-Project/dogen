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
#include "dogen/cpp/types/entity.hpp"
#include "dogen/cpp/types/source_file.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::entity>& lhs,
const boost::shared_ptr<dogen::cpp::entity>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace cpp {

source_file::source_file(source_file&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      includes_(std::move(rhs.includes_)),
      descriptor_(std::move(rhs.descriptor_)),
      header_guard_(std::move(rhs.header_guard_)),
      file_path_(std::move(rhs.file_path_)),
      relative_path_(std::move(rhs.relative_path_)),
      entity_(std::move(rhs.entity_)),
      annotation_(std::move(rhs.annotation_)) { }

source_file::source_file(
    const std::string& documentation,
    const dogen::cpp::includes& includes,
    const dogen::cpp::content_descriptor& descriptor,
    const std::string& header_guard,
    const boost::filesystem::path& file_path,
    const boost::filesystem::path& relative_path,
    const boost::shared_ptr<dogen::cpp::entity>& entity,
    const dogen::formatters::annotation& annotation)
    : documentation_(documentation),
      includes_(includes),
      descriptor_(descriptor),
      header_guard_(header_guard),
      file_path_(file_path),
      relative_path_(relative_path),
      entity_(entity),
      annotation_(annotation) { }

void source_file::swap(source_file& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(includes_, other.includes_);
    swap(descriptor_, other.descriptor_);
    swap(header_guard_, other.header_guard_);
    swap(file_path_, other.file_path_);
    swap(relative_path_, other.relative_path_);
    swap(entity_, other.entity_);
    swap(annotation_, other.annotation_);
}

bool source_file::operator==(const source_file& rhs) const {
    return documentation_ == rhs.documentation_ &&
        includes_ == rhs.includes_ &&
        descriptor_ == rhs.descriptor_ &&
        header_guard_ == rhs.header_guard_ &&
        file_path_ == rhs.file_path_ &&
        relative_path_ == rhs.relative_path_ &&
        entity_ == rhs.entity_ &&
        annotation_ == rhs.annotation_;
}

source_file& source_file::operator=(source_file other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& source_file::documentation() const {
    return documentation_;
}

std::string& source_file::documentation() {
    return documentation_;
}

void source_file::documentation(const std::string& v) {
    documentation_ = v;
}

void source_file::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::cpp::includes& source_file::includes() const {
    return includes_;
}

dogen::cpp::includes& source_file::includes() {
    return includes_;
}

void source_file::includes(const dogen::cpp::includes& v) {
    includes_ = v;
}

void source_file::includes(const dogen::cpp::includes&& v) {
    includes_ = std::move(v);
}

const dogen::cpp::content_descriptor& source_file::descriptor() const {
    return descriptor_;
}

dogen::cpp::content_descriptor& source_file::descriptor() {
    return descriptor_;
}

void source_file::descriptor(const dogen::cpp::content_descriptor& v) {
    descriptor_ = v;
}

void source_file::descriptor(const dogen::cpp::content_descriptor&& v) {
    descriptor_ = std::move(v);
}

const std::string& source_file::header_guard() const {
    return header_guard_;
}

std::string& source_file::header_guard() {
    return header_guard_;
}

void source_file::header_guard(const std::string& v) {
    header_guard_ = v;
}

void source_file::header_guard(const std::string&& v) {
    header_guard_ = std::move(v);
}

const boost::filesystem::path& source_file::file_path() const {
    return file_path_;
}

boost::filesystem::path& source_file::file_path() {
    return file_path_;
}

void source_file::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void source_file::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const boost::filesystem::path& source_file::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& source_file::relative_path() {
    return relative_path_;
}

void source_file::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void source_file::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

const boost::shared_ptr<dogen::cpp::entity>& source_file::entity() const {
    return entity_;
}

boost::shared_ptr<dogen::cpp::entity>& source_file::entity() {
    return entity_;
}

void source_file::entity(const boost::shared_ptr<dogen::cpp::entity>& v) {
    entity_ = v;
}

void source_file::entity(const boost::shared_ptr<dogen::cpp::entity>&& v) {
    entity_ = std::move(v);
}

const dogen::formatters::annotation& source_file::annotation() const {
    return annotation_;
}

dogen::formatters::annotation& source_file::annotation() {
    return annotation_;
}

void source_file::annotation(const dogen::formatters::annotation& v) {
    annotation_ = v;
}

void source_file::annotation(const dogen::formatters::annotation&& v) {
    annotation_ = std::move(v);
}

} }