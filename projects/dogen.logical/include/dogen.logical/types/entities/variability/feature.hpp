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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_FEATURE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_FEATURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/entities/variability/abstract_feature.hpp"

namespace dogen::logical::entities::variability {

/**
 * @brief Represents a feature in variability space.
 */
class feature final : public dogen::logical::entities::variability::abstract_feature {
public:
    feature() = default;
    feature(const feature&) = default;
    feature(feature&&) = default;

    virtual ~feature() noexcept { }

public:
    feature(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::logical_name& name,
        const std::string& original_key,
        const std::string& key,
        const std::string& identifiable_key,
        const std::string& unparsed_type,
        const std::string& mapped_type,
        const dogen::identification::entities::logical_name_tree& parsed_type,
        const std::string& default_value,
        const dogen::variability::entities::value_type value_type,
        const boost::optional<dogen::variability::entities::binding_point>& binding_point,
        const bool is_optional,
        const bool requires_optionality);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const feature& rhs) const;
    bool operator!=(const feature& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::variability::abstract_feature& other) const override;

public:
    void swap(feature& other) noexcept;
    feature& operator=(feature other);

};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::variability::feature& lhs,
    dogen::logical::entities::variability::feature& rhs) {
    lhs.swap(rhs);
}

}

#endif
