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
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/io/entities/variability/abstract_profile_io.hpp"
#include "dogen.logical/types/entities/variability/profile_template.hpp"
#include "dogen.logical/io/entities/variability/profile_template_entry_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::variability::profile_template_entry>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::variability {

profile_template::profile_template(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::entities::name& meta_name,
    const dogen::logical::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::logical::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::string& stereotype,
    const std::list<dogen::logical::entities::name>& parents,
    const std::string& key_prefix,
    const std::list<dogen::logical::entities::variability::profile_template_entry>& entries)
    : dogen::logical::entities::variability::abstract_profile(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      generability_status,
      decoration,
      stereotype,
      parents,
      key_prefix),
      entries_(entries) { }

void profile_template::accept(const element_visitor& v) const {
    v.visit(*this);
}

void profile_template::accept(element_visitor& v) const {
    v.visit(*this);
    }

void profile_template::accept(const element_visitor& v) {
    v.visit(*this);
}

void profile_template::accept(element_visitor& v) {
    v.visit(*this);
}

void profile_template::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::variability::profile_template\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::variability::abstract_profile::to_stream(s);
    s << ", "
      << "\"entries\": " << entries_
      << " }";
}

void profile_template::swap(profile_template& other) noexcept {
    dogen::logical::entities::variability::abstract_profile::swap(other);

    using std::swap;
    swap(entries_, other.entries_);
}

bool profile_template::equals(const dogen::logical::entities::element& other) const {
    const profile_template* const p(dynamic_cast<const profile_template* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool profile_template::operator==(const profile_template& rhs) const {
    return dogen::logical::entities::variability::abstract_profile::compare(rhs) &&
        entries_ == rhs.entries_;
}

profile_template& profile_template::operator=(profile_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::logical::entities::variability::profile_template_entry>& profile_template::entries() const {
    return entries_;
}

std::list<dogen::logical::entities::variability::profile_template_entry>& profile_template::entries() {
    return entries_;
}

void profile_template::entries(const std::list<dogen::logical::entities::variability::profile_template_entry>& v) {
    entries_ = v;
}

void profile_template::entries(const std::list<dogen::logical::entities::variability::profile_template_entry>&& v) {
    entries_ = std::move(v);
}

}
