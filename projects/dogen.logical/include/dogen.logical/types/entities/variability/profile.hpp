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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_PROFILE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/variability/profile_entry.hpp"
#include "dogen.logical/types/entities/variability/abstract_profile.hpp"

namespace dogen::logical::entities::variability {

/**
 * @brief Represents a profile from the variability subsystem.
 */
class profile final : public dogen::logical::entities::variability::abstract_profile {
public:
    profile() = default;
    profile(const profile&) = default;
    profile(profile&&) = default;

    virtual ~profile() noexcept { }

public:
    profile(
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
        const std::string& stereotype,
        const std::list<dogen::identification::entities::logical_name>& parents,
        const std::string& key_prefix,
        const std::list<dogen::logical::entities::variability::profile_entry>& entries,
        const std::string& binding_point);

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
     * @brief Configuration entries in this profile.
     */
    /**@{*/
    const std::list<dogen::logical::entities::variability::profile_entry>& entries() const;
    std::list<dogen::logical::entities::variability::profile_entry>& entries();
    void entries(const std::list<dogen::logical::entities::variability::profile_entry>& v);
    void entries(const std::list<dogen::logical::entities::variability::profile_entry>&& v);
    /**@}*/

    /**
     * @brief Binding point for the profile.
     */
    /**@{*/
    const std::string& binding_point() const;
    std::string& binding_point();
    void binding_point(const std::string& v);
    void binding_point(const std::string&& v);
    /**@}*/

public:
    bool operator==(const profile& rhs) const;
    bool operator!=(const profile& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(profile& other) noexcept;
    profile& operator=(profile other);

private:
    std::list<dogen::logical::entities::variability::profile_entry> entries_;
    std::string binding_point_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::variability::profile& lhs,
    dogen::logical::entities::variability::profile& rhs) {
    lhs.swap(rhs);
}

}

#endif
