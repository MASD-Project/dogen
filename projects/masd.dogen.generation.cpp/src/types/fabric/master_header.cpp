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
#include "masd.dogen.coding/io/meta_model/name_io.hpp"
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.generation.cpp/types/fabric/master_header.hpp"
#include "masd.dogen.generation.cpp/types/fabric/element_visitor.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<masd::dogen::coding::meta_model::name>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, std::list<masd::dogen::coding::meta_model::name> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, std::unordered_map<std::string, std::list<masd::dogen::coding::meta_model::name> > >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace masd::dogen::generation::cpp::fabric {

master_header::master_header(
    const masd::dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const boost::optional<masd::dogen::coding::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::coding::meta_model::name& meta_name,
    const bool is_element_extension,
    const masd::dogen::extraction::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<std::string, std::unordered_map<std::string, std::list<masd::dogen::coding::meta_model::name> > >& inclusion_by_facet)
    : masd::dogen::coding::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties),
      inclusion_by_facet_(inclusion_by_facet) { }

void master_header::accept(const masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void master_header::accept(masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void master_header::accept(const masd::dogen::coding::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void master_header::accept(masd::dogen::coding::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void master_header::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::generation::cpp::fabric::master_header\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"inclusion_by_facet\": " << inclusion_by_facet_
      << " }";
}

void master_header::swap(master_header& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(inclusion_by_facet_, other.inclusion_by_facet_);
}

bool master_header::equals(const masd::dogen::coding::meta_model::element& other) const {
    const master_header* const p(dynamic_cast<const master_header* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool master_header::operator==(const master_header& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        inclusion_by_facet_ == rhs.inclusion_by_facet_;
}

master_header& master_header::operator=(master_header other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::list<masd::dogen::coding::meta_model::name> > >& master_header::inclusion_by_facet() const {
    return inclusion_by_facet_;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::list<masd::dogen::coding::meta_model::name> > >& master_header::inclusion_by_facet() {
    return inclusion_by_facet_;
}

void master_header::inclusion_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<masd::dogen::coding::meta_model::name> > >& v) {
    inclusion_by_facet_ = v;
}

void master_header::inclusion_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<masd::dogen::coding::meta_model::name> > >&& v) {
    inclusion_by_facet_ = std::move(v);
}

}
