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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VISUAL_STUDIO_PROJECT_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VISUAL_STUDIO_PROJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/visual_studio/item_group.hpp"

namespace dogen::logical::entities::visual_studio {

/**
 * @brief Represents a Visual Studio project.
 */
class project final : public dogen::logical::entities::element {
public:
    project() = default;
    project(const project&) = default;
    project(project&&) = default;

    virtual ~project() noexcept { }

public:
    project(
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
        const std::string& guid,
        const std::string& type_guid,
        const std::list<dogen::logical::entities::visual_studio::item_group>& item_groups,
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
    const std::list<dogen::logical::entities::visual_studio::item_group>& item_groups() const;
    std::list<dogen::logical::entities::visual_studio::item_group>& item_groups();
    void item_groups(const std::list<dogen::logical::entities::visual_studio::item_group>& v);
    void item_groups(const std::list<dogen::logical::entities::visual_studio::item_group>&& v);
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
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(project& other) noexcept;
    project& operator=(project other);

private:
    std::string guid_;
    std::string type_guid_;
    std::list<dogen::logical::entities::visual_studio::item_group> item_groups_;
    std::string project_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::visual_studio::project& lhs,
    dogen::logical::entities::visual_studio::project& rhs) {
    lhs.swap(rhs);
}

}

#endif
