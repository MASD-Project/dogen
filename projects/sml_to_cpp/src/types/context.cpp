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
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/visitor_info.hpp"
#include "dogen/sml_to_cpp/types/context.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::class_info>& lhs,
const boost::shared_ptr<dogen::cpp::class_info>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::exception_info>& lhs,
const boost::shared_ptr<dogen::cpp::exception_info>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::enum_info>& lhs,
const boost::shared_ptr<dogen::cpp::enum_info>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::registrar_info>& lhs,
const boost::shared_ptr<dogen::cpp::registrar_info>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::namespace_info>& lhs,
const boost::shared_ptr<dogen::cpp::namespace_info>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::visitor_info>& lhs,
const boost::shared_ptr<dogen::cpp::visitor_info>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace sml_to_cpp {

context::context(
    const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::class_info> >& classes,
    const std::unordered_map<dogen::sml::qname, dogen::sml_to_cpp::relationships>& relationships,
    const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::exception_info> >& exceptions,
    const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::enum_info> >& enumerations,
    const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::registrar_info> >& registrars,
    const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::namespace_info> >& namespaces,
    const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::visitor_info> >& visitors)
    : classes_(classes),
      relationships_(relationships),
      exceptions_(exceptions),
      enumerations_(enumerations),
      registrars_(registrars),
      namespaces_(namespaces),
      visitors_(visitors) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(classes_, other.classes_);
    swap(relationships_, other.relationships_);
    swap(exceptions_, other.exceptions_);
    swap(enumerations_, other.enumerations_);
    swap(registrars_, other.registrars_);
    swap(namespaces_, other.namespaces_);
    swap(visitors_, other.visitors_);
}

bool context::operator==(const context& rhs) const {
    return classes_ == rhs.classes_ &&
        relationships_ == rhs.relationships_ &&
        exceptions_ == rhs.exceptions_ &&
        enumerations_ == rhs.enumerations_ &&
        registrars_ == rhs.registrars_ &&
        namespaces_ == rhs.namespaces_ &&
        visitors_ == rhs.visitors_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::class_info> >& context::classes() const {
    return classes_;
}

std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::class_info> >& context::classes() {
    return classes_;
}

void context::classes(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::class_info> >& v) {
    classes_ = v;
}

void context::classes(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::class_info> >&& v) {
    classes_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml_to_cpp::relationships>& context::relationships() const {
    return relationships_;
}

std::unordered_map<dogen::sml::qname, dogen::sml_to_cpp::relationships>& context::relationships() {
    return relationships_;
}

void context::relationships(const std::unordered_map<dogen::sml::qname, dogen::sml_to_cpp::relationships>& v) {
    relationships_ = v;
}

void context::relationships(const std::unordered_map<dogen::sml::qname, dogen::sml_to_cpp::relationships>&& v) {
    relationships_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::exception_info> >& context::exceptions() const {
    return exceptions_;
}

std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::exception_info> >& context::exceptions() {
    return exceptions_;
}

void context::exceptions(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::exception_info> >& v) {
    exceptions_ = v;
}

void context::exceptions(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::exception_info> >&& v) {
    exceptions_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::enum_info> >& context::enumerations() const {
    return enumerations_;
}

std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::enum_info> >& context::enumerations() {
    return enumerations_;
}

void context::enumerations(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::enum_info> >& v) {
    enumerations_ = v;
}

void context::enumerations(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::enum_info> >&& v) {
    enumerations_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::registrar_info> >& context::registrars() const {
    return registrars_;
}

std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::registrar_info> >& context::registrars() {
    return registrars_;
}

void context::registrars(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::registrar_info> >& v) {
    registrars_ = v;
}

void context::registrars(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::registrar_info> >&& v) {
    registrars_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::namespace_info> >& context::namespaces() const {
    return namespaces_;
}

std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::namespace_info> >& context::namespaces() {
    return namespaces_;
}

void context::namespaces(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::namespace_info> >& v) {
    namespaces_ = v;
}

void context::namespaces(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::namespace_info> >&& v) {
    namespaces_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::visitor_info> >& context::visitors() const {
    return visitors_;
}

std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::visitor_info> >& context::visitors() {
    return visitors_;
}

void context::visitors(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::visitor_info> >& v) {
    visitors_ = v;
}

void context::visitors(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::visitor_info> >&& v) {
    visitors_ = std::move(v);
}

} }