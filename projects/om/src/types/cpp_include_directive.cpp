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
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/io/cpp_include_types_io.hpp"
#include "dogen/om/types/cpp_include_directive.hpp"

namespace dogen {
namespace om {

cpp_include_directive::cpp_include_directive()
    : type_(static_cast<dogen::om::cpp_include_types>(0)) { }

cpp_include_directive::cpp_include_directive(cpp_include_directive&& rhs)
    : dogen::om::cpp_feature(
        std::forward<dogen::om::cpp_feature>(rhs)),
      relative_path_(std::move(rhs.relative_path_)),
      type_(std::move(rhs.type_)) { }

cpp_include_directive::cpp_include_directive(
    const std::string& name,
    const boost::filesystem::path& relative_path,
    const dogen::om::cpp_include_types& type)
    : dogen::om::cpp_feature(name),
      relative_path_(relative_path),
      type_(type) { }

void cpp_include_directive::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_include_directive\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"relative_path\": " << "\"" << relative_path_.generic_string() << "\"" << ", "
      << "\"type\": " << type_
      << " }";
}

void cpp_include_directive::swap(cpp_include_directive& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(relative_path_, other.relative_path_);
    swap(type_, other.type_);
}

bool cpp_include_directive::equals(const dogen::om::cpp_feature& other) const {
    const cpp_include_directive* const p(dynamic_cast<const cpp_include_directive* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_include_directive::operator==(const cpp_include_directive& rhs) const {
    return cpp_feature::compare(rhs) &&
        relative_path_ == rhs.relative_path_ &&
        type_ == rhs.type_;
}

cpp_include_directive& cpp_include_directive::operator=(cpp_include_directive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& cpp_include_directive::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& cpp_include_directive::relative_path() {
    return relative_path_;
}

void cpp_include_directive::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void cpp_include_directive::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

dogen::om::cpp_include_types cpp_include_directive::type() const {
    return type_;
}

void cpp_include_directive::type(const dogen::om::cpp_include_types& v) {
    type_ = v;
}

} }