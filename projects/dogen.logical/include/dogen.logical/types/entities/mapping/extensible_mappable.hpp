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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_MAPPING_EXTENSIBLE_MAPPABLE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_MAPPING_EXTENSIBLE_MAPPABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/mapping/destination.hpp"

namespace dogen::logical::entities::mapping {

/**
 * @brief A mappable meta-model element for the general purpose of mapping.
 *
 * Mappables can be used to create a Platform Independent Model (PIM), which is
 * then mapped to concrete types to form a Platform Specific Model (PSM). Users can
 * extend the mappings as required.
 */
class extensible_mappable final : public dogen::logical::entities::element {
public:
    extensible_mappable() = default;
    extensible_mappable(const extensible_mappable&) = default;
    extensible_mappable(extensible_mappable&&) = default;

    virtual ~extensible_mappable() noexcept { }

public:
    extensible_mappable(
        const dogen::identification::entities::logical_name& name,
        const std::string& documentation,
        const dogen::identification::entities::codec_provenance& provenance,
        const dogen::identification::entities::logical_id& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<dogen::logical::entities::helper_properties>& helper_properties,
        const std::list<dogen::logical::entities::mapping::destination>& destinations);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief All the destinations that this source has been mapped to.
     */
    /**@{*/
    const std::list<dogen::logical::entities::mapping::destination>& destinations() const;
    std::list<dogen::logical::entities::mapping::destination>& destinations();
    void destinations(const std::list<dogen::logical::entities::mapping::destination>& v);
    void destinations(const std::list<dogen::logical::entities::mapping::destination>&& v);
    /**@}*/

public:
    bool operator==(const extensible_mappable& rhs) const;
    bool operator!=(const extensible_mappable& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(extensible_mappable& other) noexcept;
    extensible_mappable& operator=(extensible_mappable other);

private:
    std::list<dogen::logical::entities::mapping::destination> destinations_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::mapping::extensible_mappable& lhs,
    dogen::logical::entities::mapping::extensible_mappable& rhs) {
    lhs.swap(rhs);
}

}

#endif
