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
#include "dogen/cpp/types/context.hpp"

namespace dogen {
namespace cpp {

context::context(context&& rhs)
    : qname_to_class_info_(std::move(rhs.qname_to_class_info_)),
      exceptions_(std::move(rhs.exceptions_)),
      classes_(std::move(rhs.classes_)),
      enumerations_(std::move(rhs.enumerations_)),
      registrar_(std::move(rhs.registrar_)),
      namespaces_(std::move(rhs.namespaces_)),
      visitors_(std::move(rhs.visitors_)),
      string_tables_(std::move(rhs.string_tables_)) { }

context::context(
    const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& qname_to_class_info,
    const std::list<dogen::cpp::exception_info>& exceptions,
    const std::list<dogen::cpp::class_info>& classes,
    const std::list<dogen::cpp::enum_info>& enumerations,
    const boost::optional<dogen::cpp::registrar_info>& registrar,
    const std::list<dogen::cpp::namespace_info>& namespaces,
    const std::list<dogen::cpp::visitor_info>& visitors,
    const std::list<dogen::cpp::string_table_info>& string_tables)
    : qname_to_class_info_(qname_to_class_info),
      exceptions_(exceptions),
      classes_(classes),
      enumerations_(enumerations),
      registrar_(registrar),
      namespaces_(namespaces),
      visitors_(visitors),
      string_tables_(string_tables) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(qname_to_class_info_, other.qname_to_class_info_);
    swap(exceptions_, other.exceptions_);
    swap(classes_, other.classes_);
    swap(enumerations_, other.enumerations_);
    swap(registrar_, other.registrar_);
    swap(namespaces_, other.namespaces_);
    swap(visitors_, other.visitors_);
    swap(string_tables_, other.string_tables_);
}

bool context::operator==(const context& rhs) const {
    return qname_to_class_info_ == rhs.qname_to_class_info_ &&
        exceptions_ == rhs.exceptions_ &&
        classes_ == rhs.classes_ &&
        enumerations_ == rhs.enumerations_ &&
        registrar_ == rhs.registrar_ &&
        namespaces_ == rhs.namespaces_ &&
        visitors_ == rhs.visitors_ &&
        string_tables_ == rhs.string_tables_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& context::qname_to_class_info() const {
    return qname_to_class_info_;
}

std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& context::qname_to_class_info() {
    return qname_to_class_info_;
}

void context::qname_to_class_info(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& v) {
    qname_to_class_info_ = v;
}

void context::qname_to_class_info(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>&& v) {
    qname_to_class_info_ = std::move(v);
}

const std::list<dogen::cpp::exception_info>& context::exceptions() const {
    return exceptions_;
}

std::list<dogen::cpp::exception_info>& context::exceptions() {
    return exceptions_;
}

void context::exceptions(const std::list<dogen::cpp::exception_info>& v) {
    exceptions_ = v;
}

void context::exceptions(const std::list<dogen::cpp::exception_info>&& v) {
    exceptions_ = std::move(v);
}

const std::list<dogen::cpp::class_info>& context::classes() const {
    return classes_;
}

std::list<dogen::cpp::class_info>& context::classes() {
    return classes_;
}

void context::classes(const std::list<dogen::cpp::class_info>& v) {
    classes_ = v;
}

void context::classes(const std::list<dogen::cpp::class_info>&& v) {
    classes_ = std::move(v);
}

const std::list<dogen::cpp::enum_info>& context::enumerations() const {
    return enumerations_;
}

std::list<dogen::cpp::enum_info>& context::enumerations() {
    return enumerations_;
}

void context::enumerations(const std::list<dogen::cpp::enum_info>& v) {
    enumerations_ = v;
}

void context::enumerations(const std::list<dogen::cpp::enum_info>&& v) {
    enumerations_ = std::move(v);
}

const boost::optional<dogen::cpp::registrar_info>& context::registrar() const {
    return registrar_;
}

boost::optional<dogen::cpp::registrar_info>& context::registrar() {
    return registrar_;
}

void context::registrar(const boost::optional<dogen::cpp::registrar_info>& v) {
    registrar_ = v;
}

void context::registrar(const boost::optional<dogen::cpp::registrar_info>&& v) {
    registrar_ = std::move(v);
}

const std::list<dogen::cpp::namespace_info>& context::namespaces() const {
    return namespaces_;
}

std::list<dogen::cpp::namespace_info>& context::namespaces() {
    return namespaces_;
}

void context::namespaces(const std::list<dogen::cpp::namespace_info>& v) {
    namespaces_ = v;
}

void context::namespaces(const std::list<dogen::cpp::namespace_info>&& v) {
    namespaces_ = std::move(v);
}

const std::list<dogen::cpp::visitor_info>& context::visitors() const {
    return visitors_;
}

std::list<dogen::cpp::visitor_info>& context::visitors() {
    return visitors_;
}

void context::visitors(const std::list<dogen::cpp::visitor_info>& v) {
    visitors_ = v;
}

void context::visitors(const std::list<dogen::cpp::visitor_info>&& v) {
    visitors_ = std::move(v);
}

const std::list<dogen::cpp::string_table_info>& context::string_tables() const {
    return string_tables_;
}

std::list<dogen::cpp::string_table_info>& context::string_tables() {
    return string_tables_;
}

void context::string_tables(const std::list<dogen::cpp::string_table_info>& v) {
    string_tables_ = v;
}

void context::string_tables(const std::list<dogen::cpp::string_table_info>&& v) {
    string_tables_ = std::move(v);
}

} }