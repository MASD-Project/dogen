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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_STRUCTURAL_MODULE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_STRUCTURAL_MODULE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/types/meta_model/orm/module_properties.hpp"

namespace dogen::assets::meta_model::structural {

/**
 * @brief Container for other assets elements.
 *
 * Aggregates a group of logically related elements into a unit.
 */
class module final : public dogen::assets::meta_model::element {
public:
    module(const module&) = default;

public:
    module();

    virtual ~module() noexcept { }

public:
    module(module&& rhs);

public:
    module(
        const dogen::assets::meta_model::name& name,
        const std::string& documentation,
        const dogen::assets::meta_model::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::assets::meta_model::name& meta_name,
        const dogen::assets::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::unordered_map<dogen::assets::meta_model::technical_space, boost::optional<dogen::assets::meta_model::decoration::element_properties> >& decoration,
        const std::unordered_set<std::string>& contains,
        const bool is_root,
        const bool is_global_module,
        const boost::optional<dogen::assets::meta_model::orm::module_properties>& orm_properties);

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

    const boost::optional<dogen::assets::meta_model::orm::module_properties>& orm_properties() const;
    boost::optional<dogen::assets::meta_model::orm::module_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::assets::meta_model::orm::module_properties>& v);
    void orm_properties(const boost::optional<dogen::assets::meta_model::orm::module_properties>&& v);

public:
    bool operator==(const module& rhs) const;
    bool operator!=(const module& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(module& other) noexcept;
    module& operator=(module other);

private:
    std::unordered_set<std::string> contains_;
    bool is_root_;
    bool is_global_module_;
    boost::optional<dogen::assets::meta_model::orm::module_properties> orm_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::structural::module& lhs,
    dogen::assets::meta_model::structural::module& rhs) {
    lhs.swap(rhs);
}

}

#endif
