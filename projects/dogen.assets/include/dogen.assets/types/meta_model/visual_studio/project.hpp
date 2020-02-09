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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VISUAL_STUDIO_PROJECT_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VISUAL_STUDIO_PROJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/types/meta_model/visual_studio/item_group.hpp"

namespace dogen::assets::meta_model::visual_studio {

/**
 * @brief Represents a Visual Studio project.
 */
class project final : public dogen::assets::meta_model::element {
public:
    project() = default;
    project(const project&) = default;
    project(project&&) = default;

    virtual ~project() noexcept { }

public:
    project(
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
        const std::string& guid,
        const std::string& type_guid,
        const std::list<dogen::assets::meta_model::visual_studio::item_group>& item_groups,
        const std::string& project_name);

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
     * @brief GUID that uniquely identifies this element.
     */
    /**@{*/
    const std::string& guid() const;
    std::string& guid();
    void guid(const std::string& v);
    void guid(const std::string&& v);
    /**@}*/

    /**
     * @brief GUID used by Visual Studio to identify projects of this type.
     */
    /**@{*/
    const std::string& type_guid() const;
    std::string& type_guid();
    void type_guid(const std::string& v);
    void type_guid(const std::string&& v);
    /**@}*/

    /**
     * @brief Set of item groups in the project.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::visual_studio::item_group>& item_groups() const;
    std::list<dogen::assets::meta_model::visual_studio::item_group>& item_groups();
    void item_groups(const std::list<dogen::assets::meta_model::visual_studio::item_group>& v);
    void item_groups(const std::list<dogen::assets::meta_model::visual_studio::item_group>&& v);
    /**@}*/

    /**
     * @brief Formatted name of the project.
     */
    /**@{*/
    const std::string& project_name() const;
    std::string& project_name();
    void project_name(const std::string& v);
    void project_name(const std::string&& v);
    /**@}*/

public:
    bool operator==(const project& rhs) const;
    bool operator!=(const project& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(project& other) noexcept;
    project& operator=(project other);

private:
    std::string guid_;
    std::string type_guid_;
    std::list<dogen::assets::meta_model::visual_studio::item_group> item_groups_;
    std::string project_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::visual_studio::project& lhs,
    dogen::assets::meta_model::visual_studio::project& rhs) {
    lhs.swap(rhs);
}

}

#endif
