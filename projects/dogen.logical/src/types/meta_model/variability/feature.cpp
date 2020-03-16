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
#include "dogen.logical/types/meta_model/variability/feature.hpp"
#include "dogen.logical/io/meta_model/variability/abstract_feature_io.hpp"

namespace dogen::logical::meta_model::variability {

feature::feature(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::logical::meta_model::name& name,
    const std::string& original_key,
    const std::string& key,
    const std::string& identifiable_key,
    const std::string& unparsed_type,
    const std::string& mapped_type,
    const dogen::logical::meta_model::name_tree& parsed_type,
    const std::string& default_value,
    const dogen::variability::meta_model::value_type value_type,
    const boost::optional<dogen::variability::meta_model::binding_point>& binding_point,
    const bool is_optional,
    const bool requires_optionality)
    : dogen::logical::meta_model::variability::abstract_feature(
      documentation,
      configuration,
      name,
      original_key,
      key,
      identifiable_key,
      unparsed_type,
      mapped_type,
      parsed_type,
      default_value,
      value_type,
      binding_point,
      is_optional,
      requires_optionality) { }

void feature::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::meta_model::variability::feature\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::meta_model::variability::abstract_feature::to_stream(s);
    s << " }";
}

void feature::swap(feature& other) noexcept {
    dogen::logical::meta_model::variability::abstract_feature::swap(other);

}

bool feature::equals(const dogen::logical::meta_model::variability::abstract_feature& other) const {
    const feature* const p(dynamic_cast<const feature* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature::operator==(const feature& rhs) const {
    return dogen::logical::meta_model::variability::abstract_feature::compare(rhs);
}

feature& feature::operator=(feature other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}
