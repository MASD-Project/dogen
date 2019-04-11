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
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.coding/types/meta_model/configuration.hpp"
#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"
#include "masd.dogen.coding/io/meta_model/configuration_entry_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_set<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<masd::dogen::coding::meta_model::configuration_entry>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace masd::dogen::coding::meta_model {

configuration::configuration(
    const masd::dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::coding::meta_model::name& meta_name,
    const masd::dogen::coding::meta_model::technical_space intrinsic_technical_space,
    const bool is_element_extension,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<masd::dogen::coding::meta_model::decoration>& decoration,
    const std::unordered_set<std::string>& labels,
    const std::list<masd::dogen::coding::meta_model::configuration_entry>& entries)
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
      intrinsic_technical_space,
      is_element_extension,
      artefact_properties,
      archetype_location_properties,
      decoration),
      labels_(labels),
      entries_(entries) { }

void configuration::accept(const element_visitor& v) const {
    v.visit(*this);
}

void configuration::accept(element_visitor& v) const {
    v.visit(*this);
    }

void configuration::accept(const element_visitor& v) {
    v.visit(*this);
}

void configuration::accept(element_visitor& v) {
    v.visit(*this);
}

void configuration::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::coding::meta_model::configuration\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"labels\": " << labels_ << ", "
      << "\"entries\": " << entries_
      << " }";
}

void configuration::swap(configuration& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(labels_, other.labels_);
    swap(entries_, other.entries_);
}

bool configuration::equals(const masd::dogen::coding::meta_model::element& other) const {
    const configuration* const p(dynamic_cast<const configuration* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool configuration::operator==(const configuration& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        labels_ == rhs.labels_ &&
        entries_ == rhs.entries_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& configuration::labels() const {
    return labels_;
}

std::unordered_set<std::string>& configuration::labels() {
    return labels_;
}

void configuration::labels(const std::unordered_set<std::string>& v) {
    labels_ = v;
}

void configuration::labels(const std::unordered_set<std::string>&& v) {
    labels_ = std::move(v);
}

const std::list<masd::dogen::coding::meta_model::configuration_entry>& configuration::entries() const {
    return entries_;
}

std::list<masd::dogen::coding::meta_model::configuration_entry>& configuration::entries() {
    return entries_;
}

void configuration::entries(const std::list<masd::dogen::coding::meta_model::configuration_entry>& v) {
    entries_ = v;
}

void configuration::entries(const std::list<masd::dogen::coding::meta_model::configuration_entry>&& v) {
    entries_ = std::move(v);
}

}
