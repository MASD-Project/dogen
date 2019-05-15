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
#include "dogen.coding/io/meta_model/name_io.hpp"
#include "dogen.coding/io/meta_model/element_io.hpp"
#include "dogen.coding/io/meta_model/name_tree_io.hpp"
#include "dogen.coding/types/meta_model/mapping/source.hpp"
#include "dogen.coding/io/meta_model/technical_space_io.hpp"
#include "dogen.coding/types/meta_model/element_visitor.hpp"
#include "dogen.coding/io/meta_model/mapping/destination_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::coding::meta_model::mapping::destination>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::coding::meta_model::name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::coding::meta_model::name_tree>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen::coding::meta_model::mapping {

source::source(
    const dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const dogen::coding::meta_model::origin_types origin_type,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::coding::meta_model::name& meta_name,
    const dogen::coding::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const bool is_element_extension,
    const std::unordered_map<std::string, dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<dogen::coding::meta_model::decoration::element_properties>& decoration,
    const std::list<dogen::coding::meta_model::mapping::destination>& destinations,
    const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& names_by_technical_space,
    const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& name_trees_by_technical_space)
    : dogen::coding::meta_model::element(
      name,
      documentation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      is_element_extension,
      artefact_properties,
      archetype_location_properties,
      decoration),
      destinations_(destinations),
      names_by_technical_space_(names_by_technical_space),
      name_trees_by_technical_space_(name_trees_by_technical_space) { }

void source::accept(const element_visitor& v) const {
    v.visit(*this);
}

void source::accept(element_visitor& v) const {
    v.visit(*this);
    }

void source::accept(const element_visitor& v) {
    v.visit(*this);
}

void source::accept(element_visitor& v) {
    v.visit(*this);
}

void source::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::coding::meta_model::mapping::source\"" << ", "
      << "\"__parent_0__\": ";
    dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"destinations\": " << destinations_ << ", "
      << "\"names_by_technical_space\": " << names_by_technical_space_ << ", "
      << "\"name_trees_by_technical_space\": " << name_trees_by_technical_space_
      << " }";
}

void source::swap(source& other) noexcept {
    dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(destinations_, other.destinations_);
    swap(names_by_technical_space_, other.names_by_technical_space_);
    swap(name_trees_by_technical_space_, other.name_trees_by_technical_space_);
}

bool source::equals(const dogen::coding::meta_model::element& other) const {
    const source* const p(dynamic_cast<const source* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool source::operator==(const source& rhs) const {
    return dogen::coding::meta_model::element::compare(rhs) &&
        destinations_ == rhs.destinations_ &&
        names_by_technical_space_ == rhs.names_by_technical_space_ &&
        name_trees_by_technical_space_ == rhs.name_trees_by_technical_space_;
}

source& source::operator=(source other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::coding::meta_model::mapping::destination>& source::destinations() const {
    return destinations_;
}

std::list<dogen::coding::meta_model::mapping::destination>& source::destinations() {
    return destinations_;
}

void source::destinations(const std::list<dogen::coding::meta_model::mapping::destination>& v) {
    destinations_ = v;
}

void source::destinations(const std::list<dogen::coding::meta_model::mapping::destination>&& v) {
    destinations_ = std::move(v);
}

const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& source::names_by_technical_space() const {
    return names_by_technical_space_;
}

std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& source::names_by_technical_space() {
    return names_by_technical_space_;
}

void source::names_by_technical_space(const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& v) {
    names_by_technical_space_ = v;
}

void source::names_by_technical_space(const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >&& v) {
    names_by_technical_space_ = std::move(v);
}

const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& source::name_trees_by_technical_space() const {
    return name_trees_by_technical_space_;
}

std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& source::name_trees_by_technical_space() {
    return name_trees_by_technical_space_;
}

void source::name_trees_by_technical_space(const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& v) {
    name_trees_by_technical_space_ = v;
}

void source::name_trees_by_technical_space(const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >&& v) {
    name_trees_by_technical_space_ = std::move(v);
}

}
