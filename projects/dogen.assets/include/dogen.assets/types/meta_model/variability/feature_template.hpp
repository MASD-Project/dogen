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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen.assets/types/meta_model/variability/abstract_feature.hpp"

namespace dogen::assets::meta_model::variability {

/**
 * @brief Represents a feature template in variability space.
 *
 * Feature templates are expanded into features within the variability model.
 */
class feature_template final : public dogen::assets::meta_model::variability::abstract_feature {
public:
    feature_template() = default;
    feature_template(const feature_template&) = default;
    feature_template(feature_template&&) = default;

    virtual ~feature_template() noexcept { }

public:
    feature_template(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const dogen::assets::meta_model::name& name,
        const std::string& key,
        const std::string& identifiable_key,
        const std::string& unparsed_type,
        const std::string& mapped_type,
        const dogen::assets::meta_model::name_tree& parsed_type,
        const std::string& value,
        const dogen::variability::meta_model::value_type value_type,
        const boost::optional<dogen::variability::meta_model::binding_point>& binding_point,
        const bool is_optional,
        const bool requires_optionality);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const feature_template& rhs) const;
    bool operator!=(const feature_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::variability::abstract_feature& other) const override;

public:
    void swap(feature_template& other) noexcept;
    feature_template& operator=(feature_template other);

};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::variability::feature_template& lhs,
    dogen::assets::meta_model::variability::feature_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
