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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_PROFILE_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.variability/types/entities/element.hpp"
#include "dogen.variability/types/entities/binding_point.hpp"
#include "dogen.variability/types/entities/configuration_point.hpp"

namespace dogen::variability::entities {

class profile final : public dogen::variability::entities::element {
public:
    profile(const profile&) = default;
    profile(profile&&) = default;

public:
    profile();

    virtual ~profile() noexcept { }

public:
    profile(
        const dogen::identification::entities::name& name,
        const std::string& description,
        const std::unordered_map<std::string, dogen::variability::entities::configuration_point>& configuration_points,
        const dogen::variability::entities::binding_point binding_point,
        const std::list<std::string>& parents,
        const std::string& stereotype,
        const bool merged,
        const std::string& base_layer_profile);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief All configuration points associated with this element.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::variability::entities::configuration_point>& configuration_points() const;
    std::unordered_map<std::string, dogen::variability::entities::configuration_point>& configuration_points();
    void configuration_points(const std::unordered_map<std::string, dogen::variability::entities::configuration_point>& v);
    void configuration_points(const std::unordered_map<std::string, dogen::variability::entities::configuration_point>&& v);
    /**@}*/

    /**
     * @brief How the feature binds against other model elements.
     */
    /**@{*/
    dogen::variability::entities::binding_point binding_point() const;
    void binding_point(const dogen::variability::entities::binding_point v);
    /**@}*/

    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

    const std::string& stereotype() const;
    std::string& stereotype();
    void stereotype(const std::string& v);
    void stereotype(const std::string&& v);

    /**
     * @brief If true, the profile has been merged with all of its parents.
     */
    /**@{*/
    bool merged() const;
    void merged(const bool v);
    /**@}*/

    /**
     * @brief Which base layer does this profile rely on, if any.
     */
    /**@{*/
    const std::string& base_layer_profile() const;
    std::string& base_layer_profile();
    void base_layer_profile(const std::string& v);
    void base_layer_profile(const std::string&& v);
    /**@}*/

public:
    bool operator==(const profile& rhs) const;
    bool operator!=(const profile& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::variability::entities::element& other) const override;

public:
    void swap(profile& other) noexcept;
    profile& operator=(profile other);

private:
    std::unordered_map<std::string, dogen::variability::entities::configuration_point> configuration_points_;
    dogen::variability::entities::binding_point binding_point_;
    std::list<std::string> parents_;
    std::string stereotype_;
    bool merged_;
    std::string base_layer_profile_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::profile& lhs,
    dogen::variability::entities::profile& rhs) {
    lhs.swap(rhs);
}

}

#endif
