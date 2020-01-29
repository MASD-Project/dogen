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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_BUILD_VISUAL_STUDIO_COMPONENT_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_BUILD_VISUAL_STUDIO_COMPONENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.assets/types/meta_model/element.hpp"

namespace dogen::assets::meta_model::build {

/**
 * @brief Gathers the information required to make Visual Studio projects and solutions for
 * a component.
 */
class visual_studio_component final : public dogen::assets::meta_model::element {
public:
    visual_studio_component() = default;
    visual_studio_component(const visual_studio_component&) = default;
    visual_studio_component(visual_studio_component&&) = default;

    virtual ~visual_studio_component() noexcept { }

public:
    visual_studio_component(
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
        const bool is_element_extension,
        const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
        const std::string& project_guid,
        const std::string& project_solution_guid,
        const std::string& version,
        const std::string& project_name,
        const std::string& tools_version);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& project_guid() const;
    std::string& project_guid();
    void project_guid(const std::string& v);
    void project_guid(const std::string&& v);

    const std::string& project_solution_guid() const;
    std::string& project_solution_guid();
    void project_solution_guid(const std::string& v);
    void project_solution_guid(const std::string&& v);

    const std::string& version() const;
    std::string& version();
    void version(const std::string& v);
    void version(const std::string&& v);

    const std::string& project_name() const;
    std::string& project_name();
    void project_name(const std::string& v);
    void project_name(const std::string&& v);

    const std::string& tools_version() const;
    std::string& tools_version();
    void tools_version(const std::string& v);
    void tools_version(const std::string&& v);

public:
    bool operator==(const visual_studio_component& rhs) const;
    bool operator!=(const visual_studio_component& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(visual_studio_component& other) noexcept;
    visual_studio_component& operator=(visual_studio_component other);

private:
    std::string project_guid_;
    std::string project_solution_guid_;
    std::string version_;
    std::string project_name_;
    std::string tools_version_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::build::visual_studio_component& lhs,
    dogen::assets::meta_model::build::visual_studio_component& rhs) {
    lhs.swap(rhs);
}

}

#endif
