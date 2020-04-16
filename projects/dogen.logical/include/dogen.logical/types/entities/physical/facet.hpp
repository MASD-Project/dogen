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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_FACET_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_FACET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"

namespace dogen::logical::entities::physical {

/**
 * @brief Represents a facet within a backend, such as type definitions.
 */
class facet final : public dogen::logical::entities::element {
public:
    facet() = default;
    facet(const facet&) = default;
    facet(facet&&) = default;

    virtual ~facet() noexcept { }

public:
    facet(
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
        const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::unordered_set<std::string>& contains,
        const std::string& id,
        const std::string& kernel_name,
        const std::string& backend_name,
        const std::list<dogen::logical::entities::name>& archetypes);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::unordered_set<std::string>& contains() const;
    std::unordered_set<std::string>& contains();
    void contains(const std::unordered_set<std::string>& v);
    void contains(const std::unordered_set<std::string>&& v);

    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);

    const std::string& kernel_name() const;
    std::string& kernel_name();
    void kernel_name(const std::string& v);
    void kernel_name(const std::string&& v);

    const std::string& backend_name() const;
    std::string& backend_name();
    void backend_name(const std::string& v);
    void backend_name(const std::string&& v);

    /**
     * @brief All archetypes in this facet.
     */
    /**@{*/
    const std::list<dogen::logical::entities::name>& archetypes() const;
    std::list<dogen::logical::entities::name>& archetypes();
    void archetypes(const std::list<dogen::logical::entities::name>& v);
    void archetypes(const std::list<dogen::logical::entities::name>&& v);
    /**@}*/

public:
    bool operator==(const facet& rhs) const;
    bool operator!=(const facet& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(facet& other) noexcept;
    facet& operator=(facet other);

private:
    std::unordered_set<std::string> contains_;
    std::string id_;
    std::string kernel_name_;
    std::string backend_name_;
    std::list<dogen::logical::entities::name> archetypes_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::facet& lhs,
    dogen::logical::entities::physical::facet& rhs) {
    lhs.swap(rhs);
}

}

#endif
