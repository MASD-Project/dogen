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
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/yarn/io/orm_module_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::yarn::orm_module_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen {
namespace yarn {

module::module()
    : is_root_(static_cast<bool>(0)),
      is_global_module_(static_cast<bool>(0)) { }

module::module(module&& rhs)
    : dogen::yarn::element(
        std::forward<dogen::yarn::element>(rhs)),
      members_(std::move(rhs.members_)),
      is_root_(std::move(rhs.is_root_)),
      is_global_module_(std::move(rhs.is_global_module_)),
      orm_properties_(std::move(rhs.orm_properties_)) { }

module::module(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const bool is_element_extension,
    const dogen::yarn::element_properties& element_properties,
    const std::list<std::string>& members,
    const bool is_root,
    const bool is_global_module,
    const boost::optional<dogen::yarn::orm_module_properties>& orm_properties)
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
      members_(members),
      is_root_(is_root),
      is_global_module_(is_global_module),
      orm_properties_(orm_properties) { }

void module::accept(const element_visitor& v) const {
    v.visit(*this);
}

void module::accept(element_visitor& v) const {
    v.visit(*this);
    }

void module::accept(const element_visitor& v) {
    v.visit(*this);
}

void module::accept(element_visitor& v) {
    v.visit(*this);
}

void module::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::module\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::element::to_stream(s);
    s << ", "
      << "\"members\": " << members_ << ", "
      << "\"is_root\": " << is_root_ << ", "
      << "\"is_global_module\": " << is_global_module_ << ", "
      << "\"orm_properties\": " << orm_properties_
      << " }";
}

void module::swap(module& other) noexcept {
    dogen::yarn::element::swap(other);

    using std::swap;
    swap(members_, other.members_);
    swap(is_root_, other.is_root_);
    swap(is_global_module_, other.is_global_module_);
    swap(orm_properties_, other.orm_properties_);
}

bool module::equals(const dogen::yarn::element& other) const {
    const module* const p(dynamic_cast<const module* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool module::operator==(const module& rhs) const {
    return dogen::yarn::element::compare(rhs) &&
        members_ == rhs.members_ &&
        is_root_ == rhs.is_root_ &&
        is_global_module_ == rhs.is_global_module_ &&
        orm_properties_ == rhs.orm_properties_;
}

module& module::operator=(module other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& module::members() const {
    return members_;
}

std::list<std::string>& module::members() {
    return members_;
}

void module::members(const std::list<std::string>& v) {
    members_ = v;
}

void module::members(const std::list<std::string>&& v) {
    members_ = std::move(v);
}

bool module::is_root() const {
    return is_root_;
}

void module::is_root(const bool v) {
    is_root_ = v;
}

bool module::is_global_module() const {
    return is_global_module_;
}

void module::is_global_module(const bool v) {
    is_global_module_ = v;
}

const boost::optional<dogen::yarn::orm_module_properties>& module::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::yarn::orm_module_properties>& module::orm_properties() {
    return orm_properties_;
}

void module::orm_properties(const boost::optional<dogen::yarn::orm_module_properties>& v) {
    orm_properties_ = v;
}

void module::orm_properties(const boost::optional<dogen::yarn::orm_module_properties>&& v) {
    orm_properties_ = std::move(v);
}

} }
