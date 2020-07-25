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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_HPP

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
#include "dogen.variability/types/entities/potential_binding.hpp"
#include "dogen.variability/types/entities/configuration_point.hpp"

namespace dogen::variability::entities {

class configuration final : public dogen::variability::entities::element {
public:
    configuration(const configuration&) = default;
    configuration(configuration&&) = default;

public:
    configuration();

    virtual ~configuration() noexcept { }

public:
    configuration(
        const dogen::identification::entities::name& name,
        const std::string& description,
        const std::unordered_map<std::string, dogen::variability::entities::configuration_point>& configuration_points,
        const std::list<dogen::variability::entities::potential_binding>& profile_bindings,
        const std::list<dogen::variability::entities::potential_binding>& configuration_bindings,
        const dogen::variability::entities::binding_point source_binding_point,
        const bool from_target);

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
     * @brief Bindings to profiles.
     */
    /**@{*/
    const std::list<dogen::variability::entities::potential_binding>& profile_bindings() const;
    std::list<dogen::variability::entities::potential_binding>& profile_bindings();
    void profile_bindings(const std::list<dogen::variability::entities::potential_binding>& v);
    void profile_bindings(const std::list<dogen::variability::entities::potential_binding>&& v);
    /**@}*/

    /**
     * @brief Relationships between this bound configuration and other bound configurations.
     *
     * These relationships are inferred from the relationships of the underlying model
     * elements.
     */
    /**@{*/
    const std::list<dogen::variability::entities::potential_binding>& configuration_bindings() const;
    std::list<dogen::variability::entities::potential_binding>& configuration_bindings();
    void configuration_bindings(const std::list<dogen::variability::entities::potential_binding>& v);
    void configuration_bindings(const std::list<dogen::variability::entities::potential_binding>&& v);
    /**@}*/

    /**
     * @brief Where was this configuration sourced from with regards to binding.
     */
    /**@{*/
    dogen::variability::entities::binding_point source_binding_point() const;
    void source_binding_point(const dogen::variability::entities::binding_point v);
    /**@}*/

    /**
     * @brief If true, this configuration was sourced from an element in the target model.
     */
    /**@{*/
    bool from_target() const;
    void from_target(const bool v);
    /**@}*/

public:
    bool operator==(const configuration& rhs) const;
    bool operator!=(const configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::variability::entities::element& other) const override;

public:
    void swap(configuration& other) noexcept;
    configuration& operator=(configuration other);

private:
    std::unordered_map<std::string, dogen::variability::entities::configuration_point> configuration_points_;
    std::list<dogen::variability::entities::potential_binding> profile_bindings_;
    std::list<dogen::variability::entities::potential_binding> configuration_bindings_;
    dogen::variability::entities::binding_point source_binding_point_;
    bool from_target_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::configuration& lhs,
    dogen::variability::entities::configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
