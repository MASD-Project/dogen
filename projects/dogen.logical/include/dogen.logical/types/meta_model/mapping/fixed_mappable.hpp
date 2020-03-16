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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_MAPPING_FIXED_MAPPABLE_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_MAPPING_FIXED_MAPPABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/meta_model/element.hpp"

namespace dogen::logical::meta_model::mapping {

/**
 * @brief A mappable meta-model element for a special purpose.
 *
 * At present, the only fixed mappables used by Dogen are related to the mapping of
 * variability types.
 */
class fixed_mappable final : public dogen::logical::meta_model::element {
public:
    fixed_mappable() = default;
    fixed_mappable(const fixed_mappable&) = default;
    fixed_mappable(fixed_mappable&&) = default;

    virtual ~fixed_mappable() noexcept { }

public:
    fixed_mappable(
        const dogen::logical::meta_model::name& name,
        const std::string& documentation,
        const dogen::logical::meta_model::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::logical::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::logical::meta_model::name& meta_name,
        const dogen::logical::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >& decoration,
        const std::string& destination);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& destination() const;
    std::string& destination();
    void destination(const std::string& v);
    void destination(const std::string&& v);

public:
    bool operator==(const fixed_mappable& rhs) const;
    bool operator!=(const fixed_mappable& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::meta_model::element& other) const override;

public:
    void swap(fixed_mappable& other) noexcept;
    fixed_mappable& operator=(fixed_mappable other);

private:
    std::string destination_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::mapping::fixed_mappable& lhs,
    dogen::logical::meta_model::mapping::fixed_mappable& rhs) {
    lhs.swap(rhs);
}

}

#endif
