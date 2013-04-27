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
#include "dogen/cpp/types/view_models/file_view_model.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

file_view_model::file_view_model()
    : facet_type_(static_cast<dogen::config::cpp_facet_types>(0)),
      file_type_(static_cast<dogen::cpp::file_types>(0)),
      aspect_type_(static_cast<dogen::cpp::aspect_types>(0)),
      category_type_(static_cast<dogen::sml::category_types>(0)),
      meta_type_(static_cast<dogen::sml::meta_types>(0)) { }

file_view_model::file_view_model(file_view_model&& rhs)
    : facet_type_(std::move(rhs.facet_type_)),
      file_type_(std::move(rhs.file_type_)),
      aspect_type_(std::move(rhs.aspect_type_)),
      category_type_(std::move(rhs.category_type_)),
      meta_type_(std::move(rhs.meta_type_)),
      class_vm_(std::move(rhs.class_vm_)),
      enumeration_vm_(std::move(rhs.enumeration_vm_)),
      exception_vm_(std::move(rhs.exception_vm_)),
      registrar_vm_(std::move(rhs.registrar_vm_)),
      header_guard_(std::move(rhs.header_guard_)),
      system_includes_(std::move(rhs.system_includes_)),
      user_includes_(std::move(rhs.user_includes_)),
      file_path_(std::move(rhs.file_path_)),
      namespace_vm_(std::move(rhs.namespace_vm_)),
      visitor_vm_(std::move(rhs.visitor_vm_)) { }

file_view_model::file_view_model(
    const dogen::config::cpp_facet_types& facet_type,
    const dogen::cpp::file_types& file_type,
    const dogen::cpp::aspect_types& aspect_type,
    const dogen::sml::category_types& category_type,
    const dogen::sml::meta_types& meta_type,
    const boost::optional<dogen::cpp::view_models::class_view_model>& class_vm,
    const boost::optional<dogen::cpp::view_models::enumeration_view_model>& enumeration_vm,
    const boost::optional<dogen::cpp::view_models::exception_view_model>& exception_vm,
    const boost::optional<dogen::cpp::view_models::registrar_view_model>& registrar_vm,
    const std::string& header_guard,
    const std::list<std::string>& system_includes,
    const std::list<std::string>& user_includes,
    const boost::filesystem::path& file_path,
    const boost::optional<dogen::cpp::view_models::namespace_view_model>& namespace_vm,
    const boost::optional<dogen::cpp::view_models::visitor_view_model>& visitor_vm)
    : facet_type_(facet_type),
      file_type_(file_type),
      aspect_type_(aspect_type),
      category_type_(category_type),
      meta_type_(meta_type),
      class_vm_(class_vm),
      enumeration_vm_(enumeration_vm),
      exception_vm_(exception_vm),
      registrar_vm_(registrar_vm),
      header_guard_(header_guard),
      system_includes_(system_includes),
      user_includes_(user_includes),
      file_path_(file_path),
      namespace_vm_(namespace_vm),
      visitor_vm_(visitor_vm) { }

void file_view_model::swap(file_view_model& other) noexcept {
    using std::swap;
    swap(facet_type_, other.facet_type_);
    swap(file_type_, other.file_type_);
    swap(aspect_type_, other.aspect_type_);
    swap(category_type_, other.category_type_);
    swap(meta_type_, other.meta_type_);
    swap(class_vm_, other.class_vm_);
    swap(enumeration_vm_, other.enumeration_vm_);
    swap(exception_vm_, other.exception_vm_);
    swap(registrar_vm_, other.registrar_vm_);
    swap(header_guard_, other.header_guard_);
    swap(system_includes_, other.system_includes_);
    swap(user_includes_, other.user_includes_);
    swap(file_path_, other.file_path_);
    swap(namespace_vm_, other.namespace_vm_);
    swap(visitor_vm_, other.visitor_vm_);
}

bool file_view_model::operator==(const file_view_model& rhs) const {
    return facet_type_ == rhs.facet_type_ &&
        file_type_ == rhs.file_type_ &&
        aspect_type_ == rhs.aspect_type_ &&
        category_type_ == rhs.category_type_ &&
        meta_type_ == rhs.meta_type_ &&
        class_vm_ == rhs.class_vm_ &&
        enumeration_vm_ == rhs.enumeration_vm_ &&
        exception_vm_ == rhs.exception_vm_ &&
        registrar_vm_ == rhs.registrar_vm_ &&
        header_guard_ == rhs.header_guard_ &&
        system_includes_ == rhs.system_includes_ &&
        user_includes_ == rhs.user_includes_ &&
        file_path_ == rhs.file_path_ &&
        namespace_vm_ == rhs.namespace_vm_ &&
        visitor_vm_ == rhs.visitor_vm_;
}

file_view_model& file_view_model::operator=(file_view_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::config::cpp_facet_types file_view_model::facet_type() const {
    return facet_type_;
}

void file_view_model::facet_type(const dogen::config::cpp_facet_types& v) {
    facet_type_ = v;
}

dogen::cpp::file_types file_view_model::file_type() const {
    return file_type_;
}

void file_view_model::file_type(const dogen::cpp::file_types& v) {
    file_type_ = v;
}

dogen::cpp::aspect_types file_view_model::aspect_type() const {
    return aspect_type_;
}

void file_view_model::aspect_type(const dogen::cpp::aspect_types& v) {
    aspect_type_ = v;
}

dogen::sml::category_types file_view_model::category_type() const {
    return category_type_;
}

void file_view_model::category_type(const dogen::sml::category_types& v) {
    category_type_ = v;
}

dogen::sml::meta_types file_view_model::meta_type() const {
    return meta_type_;
}

void file_view_model::meta_type(const dogen::sml::meta_types& v) {
    meta_type_ = v;
}

const boost::optional<dogen::cpp::view_models::class_view_model>& file_view_model::class_vm() const {
    return class_vm_;
}

boost::optional<dogen::cpp::view_models::class_view_model>& file_view_model::class_vm() {
    return class_vm_;
}

void file_view_model::class_vm(const boost::optional<dogen::cpp::view_models::class_view_model>& v) {
    class_vm_ = v;
}

void file_view_model::class_vm(const boost::optional<dogen::cpp::view_models::class_view_model>&& v) {
    class_vm_ = std::move(v);
}

const boost::optional<dogen::cpp::view_models::enumeration_view_model>& file_view_model::enumeration_vm() const {
    return enumeration_vm_;
}

boost::optional<dogen::cpp::view_models::enumeration_view_model>& file_view_model::enumeration_vm() {
    return enumeration_vm_;
}

void file_view_model::enumeration_vm(const boost::optional<dogen::cpp::view_models::enumeration_view_model>& v) {
    enumeration_vm_ = v;
}

void file_view_model::enumeration_vm(const boost::optional<dogen::cpp::view_models::enumeration_view_model>&& v) {
    enumeration_vm_ = std::move(v);
}

const boost::optional<dogen::cpp::view_models::exception_view_model>& file_view_model::exception_vm() const {
    return exception_vm_;
}

boost::optional<dogen::cpp::view_models::exception_view_model>& file_view_model::exception_vm() {
    return exception_vm_;
}

void file_view_model::exception_vm(const boost::optional<dogen::cpp::view_models::exception_view_model>& v) {
    exception_vm_ = v;
}

void file_view_model::exception_vm(const boost::optional<dogen::cpp::view_models::exception_view_model>&& v) {
    exception_vm_ = std::move(v);
}

const boost::optional<dogen::cpp::view_models::registrar_view_model>& file_view_model::registrar_vm() const {
    return registrar_vm_;
}

boost::optional<dogen::cpp::view_models::registrar_view_model>& file_view_model::registrar_vm() {
    return registrar_vm_;
}

void file_view_model::registrar_vm(const boost::optional<dogen::cpp::view_models::registrar_view_model>& v) {
    registrar_vm_ = v;
}

void file_view_model::registrar_vm(const boost::optional<dogen::cpp::view_models::registrar_view_model>&& v) {
    registrar_vm_ = std::move(v);
}

const std::string& file_view_model::header_guard() const {
    return header_guard_;
}

std::string& file_view_model::header_guard() {
    return header_guard_;
}

void file_view_model::header_guard(const std::string& v) {
    header_guard_ = v;
}

void file_view_model::header_guard(const std::string&& v) {
    header_guard_ = std::move(v);
}

const std::list<std::string>& file_view_model::system_includes() const {
    return system_includes_;
}

std::list<std::string>& file_view_model::system_includes() {
    return system_includes_;
}

void file_view_model::system_includes(const std::list<std::string>& v) {
    system_includes_ = v;
}

void file_view_model::system_includes(const std::list<std::string>&& v) {
    system_includes_ = std::move(v);
}

const std::list<std::string>& file_view_model::user_includes() const {
    return user_includes_;
}

std::list<std::string>& file_view_model::user_includes() {
    return user_includes_;
}

void file_view_model::user_includes(const std::list<std::string>& v) {
    user_includes_ = v;
}

void file_view_model::user_includes(const std::list<std::string>&& v) {
    user_includes_ = std::move(v);
}

const boost::filesystem::path& file_view_model::file_path() const {
    return file_path_;
}

boost::filesystem::path& file_view_model::file_path() {
    return file_path_;
}

void file_view_model::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void file_view_model::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const boost::optional<dogen::cpp::view_models::namespace_view_model>& file_view_model::namespace_vm() const {
    return namespace_vm_;
}

boost::optional<dogen::cpp::view_models::namespace_view_model>& file_view_model::namespace_vm() {
    return namespace_vm_;
}

void file_view_model::namespace_vm(const boost::optional<dogen::cpp::view_models::namespace_view_model>& v) {
    namespace_vm_ = v;
}

void file_view_model::namespace_vm(const boost::optional<dogen::cpp::view_models::namespace_view_model>&& v) {
    namespace_vm_ = std::move(v);
}

const boost::optional<dogen::cpp::view_models::visitor_view_model>& file_view_model::visitor_vm() const {
    return visitor_vm_;
}

boost::optional<dogen::cpp::view_models::visitor_view_model>& file_view_model::visitor_vm() {
    return visitor_vm_;
}

void file_view_model::visitor_vm(const boost::optional<dogen::cpp::view_models::visitor_view_model>& v) {
    visitor_vm_ = v;
}

void file_view_model::visitor_vm(const boost::optional<dogen::cpp::view_models::visitor_view_model>&& v) {
    visitor_vm_ = std::move(v);
}

} } }