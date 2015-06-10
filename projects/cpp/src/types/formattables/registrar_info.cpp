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
#include <boost/algorithm/string.hpp>
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/types/formattables/registrar_info.hpp"

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
namespace cpp {
namespace formattables {

registrar_info::registrar_info(
    const std::string& identity,
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const dogen::cpp::settings::bundle& settings,
    const std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties>& formatter_properties,
    const std::list<std::string>& leaves,
    const std::list<std::string>& model_dependencies)
    : dogen::cpp::formattables::entity(
      identity,
      name,
      qualified_name,
      documentation,
      namespaces,
      settings,
      formatter_properties),
      leaves_(leaves),
      model_dependencies_(model_dependencies) { }

void registrar_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::registrar_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"model_dependencies\": " << model_dependencies_
      << " }";
}

void registrar_info::swap(registrar_info& other) noexcept {
    entity::swap(other);

    using std::swap;
    swap(leaves_, other.leaves_);
    swap(model_dependencies_, other.model_dependencies_);
}

bool registrar_info::equals(const dogen::cpp::formattables::formattable& other) const {
    const registrar_info* const p(dynamic_cast<const registrar_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool registrar_info::operator==(const registrar_info& rhs) const {
    return entity::compare(rhs) &&
        leaves_ == rhs.leaves_ &&
        model_dependencies_ == rhs.model_dependencies_;
}

registrar_info& registrar_info::operator=(registrar_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& registrar_info::leaves() const {
    return leaves_;
}

std::list<std::string>& registrar_info::leaves() {
    return leaves_;
}

void registrar_info::leaves(const std::list<std::string>& v) {
    leaves_ = v;
}

void registrar_info::leaves(const std::list<std::string>&& v) {
    leaves_ = std::move(v);
}

const std::list<std::string>& registrar_info::model_dependencies() const {
    return model_dependencies_;
}

std::list<std::string>& registrar_info::model_dependencies() {
    return model_dependencies_;
}

void registrar_info::model_dependencies(const std::list<std::string>& v) {
    model_dependencies_ = v;
}

void registrar_info::model_dependencies(const std::list<std::string>&& v) {
    model_dependencies_ = std::move(v);
}

} } }
