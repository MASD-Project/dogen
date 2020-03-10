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
#include "dogen.variability/io/meta_model/template_kind_io.hpp"
#include "dogen.assets/io/meta_model/variability/abstract_profile_entry_io.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template_entry.hpp"

namespace dogen::assets::meta_model::variability {

profile_template_entry::profile_template_entry()
    : template_kind_(static_cast<dogen::variability::meta_model::template_kind>(0)) { }

profile_template_entry::profile_template_entry(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::assets::meta_model::name& name,
    const std::string& key,
    const std::list<std::string>& value,
    const dogen::archetypes::location& location,
    const dogen::variability::meta_model::template_kind template_kind)
    : dogen::assets::meta_model::variability::abstract_profile_entry(
      documentation,
      configuration,
      name,
      key,
      value,
      location),
      template_kind_(template_kind) { }

void profile_template_entry::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::profile_template_entry\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::variability::abstract_profile_entry::to_stream(s);
    s << ", "
      << "\"template_kind\": " << template_kind_
      << " }";
}

void profile_template_entry::swap(profile_template_entry& other) noexcept {
    dogen::assets::meta_model::variability::abstract_profile_entry::swap(other);

    using std::swap;
    swap(template_kind_, other.template_kind_);
}

bool profile_template_entry::equals(const dogen::assets::meta_model::variability::abstract_profile_entry& other) const {
    const profile_template_entry* const p(dynamic_cast<const profile_template_entry* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool profile_template_entry::operator==(const profile_template_entry& rhs) const {
    return dogen::assets::meta_model::variability::abstract_profile_entry::compare(rhs) &&
        template_kind_ == rhs.template_kind_;
}

profile_template_entry& profile_template_entry::operator=(profile_template_entry other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::variability::meta_model::template_kind profile_template_entry::template_kind() const {
    return template_kind_;
}

void profile_template_entry::template_kind(const dogen::variability::meta_model::template_kind v) {
    template_kind_ = v;
}

}
