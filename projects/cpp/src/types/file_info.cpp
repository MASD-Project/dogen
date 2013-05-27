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
#include "dogen/cpp/types/file_info.hpp"

namespace dogen {
namespace cpp {

file_info::file_info()
    : facet_type_(static_cast<dogen::config::cpp_facet_types>(0)),
      file_type_(static_cast<dogen::cpp::file_types>(0)),
      aspect_type_(static_cast<dogen::cpp::aspect_types>(0)),
      category_type_(static_cast<dogen::sml::category_types>(0)),
      meta_type_(static_cast<dogen::sml::meta_types>(0)) { }

file_info::file_info(file_info&& rhs)
    : facet_type_(std::move(rhs.facet_type_)),
      file_type_(std::move(rhs.file_type_)),
      aspect_type_(std::move(rhs.aspect_type_)),
      category_type_(std::move(rhs.category_type_)),
      meta_type_(std::move(rhs.meta_type_)),
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

file_info::file_info(
    const dogen::config::cpp_facet_types& facet_type,
    const dogen::cpp::file_types& file_type,
    const dogen::cpp::aspect_types& aspect_type,
    const dogen::sml::category_types& category_type,
    const dogen::sml::meta_types& meta_type,
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
    : facet_type_(facet_type),
      file_type_(file_type),
      aspect_type_(aspect_type),
      category_type_(category_type),
      meta_type_(meta_type),
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

void file_info::swap(file_info& other) noexcept {
    using std::swap;
    swap(facet_type_, other.facet_type_);
    swap(file_type_, other.file_type_);
    swap(aspect_type_, other.aspect_type_);
    swap(category_type_, other.category_type_);
    swap(meta_type_, other.meta_type_);
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

bool file_info::operator==(const file_info& rhs) const {
    return facet_type_ == rhs.facet_type_ &&
        file_type_ == rhs.file_type_ &&
        aspect_type_ == rhs.aspect_type_ &&
        category_type_ == rhs.category_type_ &&
        meta_type_ == rhs.meta_type_ &&
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

file_info& file_info::operator=(file_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::config::cpp_facet_types file_info::facet_type() const {
    return facet_type_;
}

void file_info::facet_type(const dogen::config::cpp_facet_types& v) {
    facet_type_ = v;
}

dogen::cpp::file_types file_info::file_type() const {
    return file_type_;
}

void file_info::file_type(const dogen::cpp::file_types& v) {
    file_type_ = v;
}

dogen::cpp::aspect_types file_info::aspect_type() const {
    return aspect_type_;
}

void file_info::aspect_type(const dogen::cpp::aspect_types& v) {
    aspect_type_ = v;
}

dogen::sml::category_types file_info::category_type() const {
    return category_type_;
}

void file_info::category_type(const dogen::sml::category_types& v) {
    category_type_ = v;
}

dogen::sml::meta_types file_info::meta_type() const {
    return meta_type_;
}

void file_info::meta_type(const dogen::sml::meta_types& v) {
    meta_type_ = v;
}

const boost::optional<dogen::cpp::class_info>& file_info::class_info() const {
    return class_info_;
}

boost::optional<dogen::cpp::class_info>& file_info::class_info() {
    return class_info_;
}

void file_info::class_info(const boost::optional<dogen::cpp::class_info>& v) {
    class_info_ = v;
}

void file_info::class_info(const boost::optional<dogen::cpp::class_info>&& v) {
    class_info_ = std::move(v);
}

const boost::optional<dogen::cpp::enum_info>& file_info::enum_info() const {
    return enum_info_;
}

boost::optional<dogen::cpp::enum_info>& file_info::enum_info() {
    return enum_info_;
}

void file_info::enum_info(const boost::optional<dogen::cpp::enum_info>& v) {
    enum_info_ = v;
}

void file_info::enum_info(const boost::optional<dogen::cpp::enum_info>&& v) {
    enum_info_ = std::move(v);
}

const boost::optional<dogen::cpp::exception_info>& file_info::exception_info() const {
    return exception_info_;
}

boost::optional<dogen::cpp::exception_info>& file_info::exception_info() {
    return exception_info_;
}

void file_info::exception_info(const boost::optional<dogen::cpp::exception_info>& v) {
    exception_info_ = v;
}

void file_info::exception_info(const boost::optional<dogen::cpp::exception_info>&& v) {
    exception_info_ = std::move(v);
}

const boost::optional<dogen::cpp::registrar_info>& file_info::registrar_info() const {
    return registrar_info_;
}

boost::optional<dogen::cpp::registrar_info>& file_info::registrar_info() {
    return registrar_info_;
}

void file_info::registrar_info(const boost::optional<dogen::cpp::registrar_info>& v) {
    registrar_info_ = v;
}

void file_info::registrar_info(const boost::optional<dogen::cpp::registrar_info>&& v) {
    registrar_info_ = std::move(v);
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

const std::list<std::string>& file_info::system_includes() const {
    return system_includes_;
}

std::list<std::string>& file_info::system_includes() {
    return system_includes_;
}

void file_info::system_includes(const std::list<std::string>& v) {
    system_includes_ = v;
}

void file_info::system_includes(const std::list<std::string>&& v) {
    system_includes_ = std::move(v);
}

const std::list<std::string>& file_info::user_includes() const {
    return user_includes_;
}

std::list<std::string>& file_info::user_includes() {
    return user_includes_;
}

void file_info::user_includes(const std::list<std::string>& v) {
    user_includes_ = v;
}

void file_info::user_includes(const std::list<std::string>&& v) {
    user_includes_ = std::move(v);
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

const boost::optional<dogen::cpp::namespace_info>& file_info::namespace_info() const {
    return namespace_info_;
}

boost::optional<dogen::cpp::namespace_info>& file_info::namespace_info() {
    return namespace_info_;
}

void file_info::namespace_info(const boost::optional<dogen::cpp::namespace_info>& v) {
    namespace_info_ = v;
}

void file_info::namespace_info(const boost::optional<dogen::cpp::namespace_info>&& v) {
    namespace_info_ = std::move(v);
}

const boost::optional<dogen::cpp::visitor_info>& file_info::visitor_info() const {
    return visitor_info_;
}

boost::optional<dogen::cpp::visitor_info>& file_info::visitor_info() {
    return visitor_info_;
}

void file_info::visitor_info(const boost::optional<dogen::cpp::visitor_info>& v) {
    visitor_info_ = v;
}

void file_info::visitor_info(const boost::optional<dogen::cpp::visitor_info>&& v) {
    visitor_info_ = std::move(v);
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

} }