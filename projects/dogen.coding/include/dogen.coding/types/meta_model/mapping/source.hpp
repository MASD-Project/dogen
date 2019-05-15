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
#ifndef DOGEN_CODING_TYPES_META_MODEL_MAPPING_SOURCE_HPP
#define DOGEN_CODING_TYPES_META_MODEL_MAPPING_SOURCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <unordered_map>
#include "dogen.coding/types/meta_model/name.hpp"
#include "dogen.coding/types/meta_model/element.hpp"
#include "dogen.coding/types/meta_model/name_tree.hpp"
#include "dogen.coding/types/meta_model/technical_space.hpp"
#include "dogen.coding/hash/meta_model/technical_space_hash.hpp"
#include "dogen.coding/types/meta_model/mapping/destination.hpp"

namespace dogen::coding::meta_model::mapping {

/**
 * @brief Represents a source of mapping.
 */
class source final : public dogen::coding::meta_model::element {
public:
    source() = default;
    source(const source&) = default;
    source(source&&) = default;

    virtual ~source() noexcept { }

public:
    source(
        const dogen::coding::meta_model::name& name,
        const std::string& documentation,
        const dogen::coding::meta_model::origin_types origin_type,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::coding::meta_model::name& meta_name,
        const dogen::coding::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const bool is_element_extension,
        const std::unordered_map<std::string, dogen::coding::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<dogen::coding::meta_model::decoration::element_properties>& decoration,
        const std::list<dogen::coding::meta_model::mapping::destination>& destinations,
        const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& names_by_technical_space,
        const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& name_trees_by_technical_space);

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
    const std::list<dogen::coding::meta_model::mapping::destination>& destinations() const;
    std::list<dogen::coding::meta_model::mapping::destination>& destinations();
    void destinations(const std::list<dogen::coding::meta_model::mapping::destination>& v);
    void destinations(const std::list<dogen::coding::meta_model::mapping::destination>&& v);
    /**@}*/

    /**
     * @brief Destinations after they have been resolved into names, and mapped to a technical
     * space.
     */
    /**@{*/
    const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& names_by_technical_space() const;
    std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& names_by_technical_space();
    void names_by_technical_space(const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >& v);
    void names_by_technical_space(const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> >&& v);
    /**@}*/

    /**
     * @brief Destinations after they have been resolved into name trees, and mapped to a
     * technical space.
     */
    /**@{*/
    const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& name_trees_by_technical_space() const;
    std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& name_trees_by_technical_space();
    void name_trees_by_technical_space(const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >& v);
    void name_trees_by_technical_space(const std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> >&& v);
    /**@}*/

public:
    bool operator==(const source& rhs) const;
    bool operator!=(const source& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::coding::meta_model::element& other) const override;

public:
    void swap(source& other) noexcept;
    source& operator=(source other);

private:
    std::list<dogen::coding::meta_model::mapping::destination> destinations_;
    std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> > names_by_technical_space_;
    std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> > name_trees_by_technical_space_;
};

}

namespace std {

template<>
inline void swap(
    dogen::coding::meta_model::mapping::source& lhs,
    dogen::coding::meta_model::mapping::source& rhs) {
    lhs.swap(rhs);
}

}

#endif
