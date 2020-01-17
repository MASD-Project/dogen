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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_PROFILE_TEMPLATE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_PROFILE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template_entry.hpp"

namespace dogen::assets::meta_model::variability {

class profile_template final : public dogen::assets::meta_model::element {
public:
    profile_template() = default;
    profile_template(const profile_template&) = default;
    profile_template(profile_template&&) = default;

    virtual ~profile_template() noexcept { }

public:
    profile_template(
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
        const std::unordered_set<std::string>& labels,
        const std::list<dogen::assets::meta_model::variability::profile_template_entry>& entries,
        const std::list<dogen::assets::meta_model::name>& parents);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::unordered_set<std::string>& labels() const;
    std::unordered_set<std::string>& labels();
    void labels(const std::unordered_set<std::string>& v);
    void labels(const std::unordered_set<std::string>&& v);

    const std::list<dogen::assets::meta_model::variability::profile_template_entry>& entries() const;
    std::list<dogen::assets::meta_model::variability::profile_template_entry>& entries();
    void entries(const std::list<dogen::assets::meta_model::variability::profile_template_entry>& v);
    void entries(const std::list<dogen::assets::meta_model::variability::profile_template_entry>&& v);

    /**
     * @brief Parents of this profile template.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& parents() const;
    std::list<dogen::assets::meta_model::name>& parents();
    void parents(const std::list<dogen::assets::meta_model::name>& v);
    void parents(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

public:
    bool operator==(const profile_template& rhs) const;
    bool operator!=(const profile_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(profile_template& other) noexcept;
    profile_template& operator=(profile_template other);

private:
    std::unordered_set<std::string> labels_;
    std::list<dogen::assets::meta_model::variability::profile_template_entry> entries_;
    std::list<dogen::assets::meta_model::name> parents_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::variability::profile_template& lhs,
    dogen::assets::meta_model::variability::profile_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
