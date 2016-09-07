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
#include <boost/algorithm/string.hpp>
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

registrar::registrar(
    const std::list<std::string>& leaves,
    const std::list<std::string>& model_dependencies)
    : dogen::yarn::element(),
      leaves_(leaves),
      model_dependencies_(model_dependencies) { }

void registrar::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void registrar::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void registrar::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void registrar::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}


void registrar::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::registrar\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"model_dependencies\": " << model_dependencies_
      << " }";
}

void registrar::swap(registrar& other) noexcept {
    element::swap(other);

    using std::swap;
    swap(leaves_, other.leaves_);
    swap(model_dependencies_, other.model_dependencies_);
}

bool registrar::equals(const dogen::yarn::element& other) const {
    const registrar* const p(dynamic_cast<const registrar* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool registrar::operator==(const registrar& rhs) const {
    return element::compare(rhs) &&
        leaves_ == rhs.leaves_ &&
        model_dependencies_ == rhs.model_dependencies_;
}

registrar& registrar::operator=(registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& registrar::leaves() const {
    return leaves_;
}

std::list<std::string>& registrar::leaves() {
    return leaves_;
}

void registrar::leaves(const std::list<std::string>& v) {
    leaves_ = v;
}

void registrar::leaves(const std::list<std::string>&& v) {
    leaves_ = std::move(v);
}

const std::list<std::string>& registrar::model_dependencies() const {
    return model_dependencies_;
}

std::list<std::string>& registrar::model_dependencies() {
    return model_dependencies_;
}

void registrar::model_dependencies(const std::list<std::string>& v) {
    model_dependencies_ = v;
}

void registrar::model_dependencies(const std::list<std::string>&& v) {
    model_dependencies_ = std::move(v);
}

} } } }
