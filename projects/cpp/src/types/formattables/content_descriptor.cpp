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
#include "dogen/cpp/types/formattables/content_descriptor.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

content_descriptor::content_descriptor()
    : file_type_(static_cast<dogen::cpp::formattables::file_types>(0)),
      facet_type_(static_cast<dogen::config::cpp_facet_types>(0)),
      aspect_type_(static_cast<dogen::cpp::formattables::aspect_types>(0)),
      content_type_(static_cast<dogen::cpp::formattables::content_types>(0)) { }

content_descriptor::content_descriptor(
    const dogen::cpp::formattables::file_types& file_type,
    const dogen::config::cpp_facet_types& facet_type,
    const dogen::cpp::formattables::aspect_types& aspect_type,
    const dogen::sml::qname& name,
    const dogen::cpp::formattables::content_types& content_type)
    : file_type_(file_type),
      facet_type_(facet_type),
      aspect_type_(aspect_type),
      name_(name),
      content_type_(content_type) { }

void content_descriptor::swap(content_descriptor& other) noexcept {
    using std::swap;
    swap(file_type_, other.file_type_);
    swap(facet_type_, other.facet_type_);
    swap(aspect_type_, other.aspect_type_);
    swap(name_, other.name_);
    swap(content_type_, other.content_type_);
}

bool content_descriptor::operator==(const content_descriptor& rhs) const {
    return file_type_ == rhs.file_type_ &&
        facet_type_ == rhs.facet_type_ &&
        aspect_type_ == rhs.aspect_type_ &&
        name_ == rhs.name_ &&
        content_type_ == rhs.content_type_;
}

content_descriptor& content_descriptor::operator=(content_descriptor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::cpp::formattables::file_types content_descriptor::file_type() const {
    return file_type_;
}

void content_descriptor::file_type(const dogen::cpp::formattables::file_types& v) {
    file_type_ = v;
}

dogen::config::cpp_facet_types content_descriptor::facet_type() const {
    return facet_type_;
}

void content_descriptor::facet_type(const dogen::config::cpp_facet_types& v) {
    facet_type_ = v;
}

dogen::cpp::formattables::aspect_types content_descriptor::aspect_type() const {
    return aspect_type_;
}

void content_descriptor::aspect_type(const dogen::cpp::formattables::aspect_types& v) {
    aspect_type_ = v;
}

const dogen::sml::qname& content_descriptor::name() const {
    return name_;
}

dogen::sml::qname& content_descriptor::name() {
    return name_;
}

void content_descriptor::name(const dogen::sml::qname& v) {
    name_ = v;
}

void content_descriptor::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

dogen::cpp::formattables::content_types content_descriptor::content_type() const {
    return content_type_;
}

void content_descriptor::content_type(const dogen::cpp::formattables::content_types& v) {
    content_type_ = v;
}

} } }
