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
#include "dogen/cpp/types/source_file.hpp"

namespace dogen {
namespace cpp {

source_file::source_file(source_file&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      descriptor_(std::move(rhs.descriptor_)),
      class_info_(std::move(rhs.class_info_)),
      enum_info_(std::move(rhs.enum_info_)),
      exception_info_(std::move(rhs.exception_info_)),
      registrar_info_(std::move(rhs.registrar_info_)),
      header_guard_(std::move(rhs.header_guard_)),
      system_includes_(std::move(rhs.system_includes_)),
      user_includes_(std::move(rhs.user_includes_)),
      file_path_(std::move(rhs.file_path_)),
      namespace_info_(std::move(rhs.namespace_info_)),
      visitor_info_(std::move(rhs.visitor_info_)),
      relative_path_(std::move(rhs.relative_path_)) { }

source_file::source_file(
    const std::string& documentation,
    const dogen::cpp::content_descriptor& descriptor,
    const boost::optional<dogen::cpp::class_info>& class_info,
    const boost::optional<dogen::cpp::enum_info>& enum_info,
    const boost::optional<dogen::cpp::exception_info>& exception_info,
    const boost::optional<dogen::cpp::registrar_info>& registrar_info,
    const std::string& header_guard,
    const std::list<std::string>& system_includes,
    const std::list<std::string>& user_includes,
    const boost::filesystem::path& file_path,
    const boost::optional<dogen::cpp::namespace_info>& namespace_info,
    const boost::optional<dogen::cpp::visitor_info>& visitor_info,
    const boost::filesystem::path& relative_path)
    : documentation_(documentation),
      descriptor_(descriptor),
      class_info_(class_info),
      enum_info_(enum_info),
      exception_info_(exception_info),
      registrar_info_(registrar_info),
      header_guard_(header_guard),
      system_includes_(system_includes),
      user_includes_(user_includes),
      file_path_(file_path),
      namespace_info_(namespace_info),
      visitor_info_(visitor_info),
      relative_path_(relative_path) { }

void source_file::swap(source_file& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(descriptor_, other.descriptor_);
    swap(class_info_, other.class_info_);
    swap(enum_info_, other.enum_info_);
    swap(exception_info_, other.exception_info_);
    swap(registrar_info_, other.registrar_info_);
    swap(header_guard_, other.header_guard_);
    swap(system_includes_, other.system_includes_);
    swap(user_includes_, other.user_includes_);
    swap(file_path_, other.file_path_);
    swap(namespace_info_, other.namespace_info_);
    swap(visitor_info_, other.visitor_info_);
    swap(relative_path_, other.relative_path_);
}

bool source_file::operator==(const source_file& rhs) const {
    return documentation_ == rhs.documentation_ &&
        descriptor_ == rhs.descriptor_ &&
        class_info_ == rhs.class_info_ &&
        enum_info_ == rhs.enum_info_ &&
        exception_info_ == rhs.exception_info_ &&
        registrar_info_ == rhs.registrar_info_ &&
        header_guard_ == rhs.header_guard_ &&
        system_includes_ == rhs.system_includes_ &&
        user_includes_ == rhs.user_includes_ &&
        file_path_ == rhs.file_path_ &&
        namespace_info_ == rhs.namespace_info_ &&
        visitor_info_ == rhs.visitor_info_ &&
        relative_path_ == rhs.relative_path_;
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

const boost::optional<dogen::cpp::class_info>& source_file::class_info() const {
    return class_info_;
}

boost::optional<dogen::cpp::class_info>& source_file::class_info() {
    return class_info_;
}

void source_file::class_info(const boost::optional<dogen::cpp::class_info>& v) {
    class_info_ = v;
}

void source_file::class_info(const boost::optional<dogen::cpp::class_info>&& v) {
    class_info_ = std::move(v);
}

const boost::optional<dogen::cpp::enum_info>& source_file::enum_info() const {
    return enum_info_;
}

boost::optional<dogen::cpp::enum_info>& source_file::enum_info() {
    return enum_info_;
}

void source_file::enum_info(const boost::optional<dogen::cpp::enum_info>& v) {
    enum_info_ = v;
}

void source_file::enum_info(const boost::optional<dogen::cpp::enum_info>&& v) {
    enum_info_ = std::move(v);
}

const boost::optional<dogen::cpp::exception_info>& source_file::exception_info() const {
    return exception_info_;
}

boost::optional<dogen::cpp::exception_info>& source_file::exception_info() {
    return exception_info_;
}

void source_file::exception_info(const boost::optional<dogen::cpp::exception_info>& v) {
    exception_info_ = v;
}

void source_file::exception_info(const boost::optional<dogen::cpp::exception_info>&& v) {
    exception_info_ = std::move(v);
}

const boost::optional<dogen::cpp::registrar_info>& source_file::registrar_info() const {
    return registrar_info_;
}

boost::optional<dogen::cpp::registrar_info>& source_file::registrar_info() {
    return registrar_info_;
}

void source_file::registrar_info(const boost::optional<dogen::cpp::registrar_info>& v) {
    registrar_info_ = v;
}

void source_file::registrar_info(const boost::optional<dogen::cpp::registrar_info>&& v) {
    registrar_info_ = std::move(v);
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

const std::list<std::string>& source_file::system_includes() const {
    return system_includes_;
}

std::list<std::string>& source_file::system_includes() {
    return system_includes_;
}

void source_file::system_includes(const std::list<std::string>& v) {
    system_includes_ = v;
}

void source_file::system_includes(const std::list<std::string>&& v) {
    system_includes_ = std::move(v);
}

const std::list<std::string>& source_file::user_includes() const {
    return user_includes_;
}

std::list<std::string>& source_file::user_includes() {
    return user_includes_;
}

void source_file::user_includes(const std::list<std::string>& v) {
    user_includes_ = v;
}

void source_file::user_includes(const std::list<std::string>&& v) {
    user_includes_ = std::move(v);
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

const boost::optional<dogen::cpp::namespace_info>& source_file::namespace_info() const {
    return namespace_info_;
}

boost::optional<dogen::cpp::namespace_info>& source_file::namespace_info() {
    return namespace_info_;
}

void source_file::namespace_info(const boost::optional<dogen::cpp::namespace_info>& v) {
    namespace_info_ = v;
}

void source_file::namespace_info(const boost::optional<dogen::cpp::namespace_info>&& v) {
    namespace_info_ = std::move(v);
}

const boost::optional<dogen::cpp::visitor_info>& source_file::visitor_info() const {
    return visitor_info_;
}

boost::optional<dogen::cpp::visitor_info>& source_file::visitor_info() {
    return visitor_info_;
}

void source_file::visitor_info(const boost::optional<dogen::cpp::visitor_info>& v) {
    visitor_info_ = v;
}

void source_file::visitor_info(const boost::optional<dogen::cpp::visitor_info>&& v) {
    visitor_info_ = std::move(v);
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

} }