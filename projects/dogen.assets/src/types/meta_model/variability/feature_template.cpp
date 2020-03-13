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
#include "dogen.assets/io/meta_model/variability/abstract_feature_io.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template.hpp"

namespace dogen::assets::meta_model::variability {

feature_template::feature_template(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::assets::meta_model::name& name,
    const std::string& original_key,
    const std::string& key,
    const std::string& identifiable_key,
    const std::string& unparsed_type,
    const std::string& mapped_type,
    const dogen::assets::meta_model::name_tree& parsed_type,
    const std::string& value,
    const dogen::variability::meta_model::value_type value_type,
    const boost::optional<dogen::variability::meta_model::binding_point>& binding_point,
    const bool is_optional,
    const bool requires_optionality)
    : dogen::assets::meta_model::variability::abstract_feature(
      documentation,
      configuration,
      name,
      original_key,
      key,
      identifiable_key,
      unparsed_type,
      mapped_type,
      parsed_type,
      value,
      value_type,
      binding_point,
      is_optional,
      requires_optionality) { }

void feature_template::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::feature_template\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::variability::abstract_feature::to_stream(s);
    s << " }";
}

void feature_template::swap(feature_template& other) noexcept {
    dogen::assets::meta_model::variability::abstract_feature::swap(other);

}

bool feature_template::equals(const dogen::assets::meta_model::variability::abstract_feature& other) const {
    const feature_template* const p(dynamic_cast<const feature_template* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature_template::operator==(const feature_template& rhs) const {
    return dogen::assets::meta_model::variability::abstract_feature::compare(rhs);
}

feature_template& feature_template::operator=(feature_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}
