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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_MODULE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_MODULE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/orm/module_properties.hpp"

namespace dogen::logical::entities::structural {

/**
 * @brief Container for other logical elements.
 *
 * Aggregates a group of logically related elements into a unit.
 */
class module final : public dogen::logical::entities::element {
public:
    module(const module&) = default;

public:
    module();

    virtual ~module() noexcept { }

public:
    module(module&& rhs);

public:
    module(
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
        const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<std::string>& contains,
        const bool is_root,
        const bool is_global_module,
        const boost::optional<dogen::logical::entities::orm::module_properties>& orm_properties);

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
     * @brief All elements contained by this element.
     */
    /**@{*/
    const std::list<std::string>& contains() const;
    std::list<std::string>& contains();
    void contains(const std::list<std::string>& v);
    void contains(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief If true, this module is thee root module of the model.
     */
    /**@{*/
    bool is_root() const;
    void is_root(const bool v);
    /**@}*/

    /**
     * @brief If true, this module is the pseudo module that models the global namespace.
     */
    /**@{*/
    bool is_global_module() const;
    void is_global_module(const bool v);
    /**@}*/

    const boost::optional<dogen::logical::entities::orm::module_properties>& orm_properties() const;
    boost::optional<dogen::logical::entities::orm::module_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::logical::entities::orm::module_properties>& v);
    void orm_properties(const boost::optional<dogen::logical::entities::orm::module_properties>&& v);

public:
    bool operator==(const module& rhs) const;
    bool operator!=(const module& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(module& other) noexcept;
    module& operator=(module other);

private:
    std::list<std::string> contains_;
    bool is_root_;
    bool is_global_module_;
    boost::optional<dogen::logical::entities::orm::module_properties> orm_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::structural::module& lhs,
    dogen::logical::entities::structural::module& rhs) {
    lhs.swap(rhs);
}

}

#endif
