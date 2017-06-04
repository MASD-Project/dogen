/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/quilt.cpp/io/fabric/odb_targets_io.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/msbuild_targets.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

msbuild_targets::msbuild_targets(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const bool is_element_extension,
    const dogen::yarn::element_properties& element_properties,
    const dogen::quilt::cpp::fabric::odb_targets& odb_targets)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension,
      element_properties),
      odb_targets_(odb_targets) { }

void msbuild_targets::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void msbuild_targets::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void msbuild_targets::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void msbuild_targets::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void msbuild_targets::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::msbuild_targets\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::element::to_stream(s);
    s << ", "
      << "\"odb_targets\": " << odb_targets_
      << " }";
}

void msbuild_targets::swap(msbuild_targets& other) noexcept {
    dogen::yarn::element::swap(other);

    using std::swap;
    swap(odb_targets_, other.odb_targets_);
}

bool msbuild_targets::equals(const dogen::yarn::element& other) const {
    const msbuild_targets* const p(dynamic_cast<const msbuild_targets* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool msbuild_targets::operator==(const msbuild_targets& rhs) const {
    return dogen::yarn::element::compare(rhs) &&
        odb_targets_ == rhs.odb_targets_;
}

msbuild_targets& msbuild_targets::operator=(msbuild_targets other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::quilt::cpp::fabric::odb_targets& msbuild_targets::odb_targets() const {
    return odb_targets_;
}

dogen::quilt::cpp::fabric::odb_targets& msbuild_targets::odb_targets() {
    return odb_targets_;
}

void msbuild_targets::odb_targets(const dogen::quilt::cpp::fabric::odb_targets& v) {
    odb_targets_ = v;
}

void msbuild_targets::odb_targets(const dogen::quilt::cpp::fabric::odb_targets&& v) {
    odb_targets_ = std::move(v);
}

} } } }
