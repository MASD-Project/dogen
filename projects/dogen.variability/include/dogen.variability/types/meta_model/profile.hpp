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
#ifndef DOGEN_VARIABILITY_TYPES_META_MODEL_PROFILE_HPP
#define DOGEN_VARIABILITY_TYPES_META_MODEL_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen.variability/types/meta_model/element.hpp"
#include "dogen.variability/types/meta_model/configuration_point.hpp"

namespace dogen::variability::meta_model {

class profile final : public dogen::variability::meta_model::element {
public:
    profile(const profile&) = default;
    profile(profile&&) = default;

public:
    profile();

    virtual ~profile() noexcept { }

public:
    profile(
        const dogen::variability::meta_model::name& name,
        const std::string& description,
        const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& configuration_points,
        const std::list<std::string>& parents,
        const std::unordered_set<std::string>& stereotype,
        const bool merged,
        const std::string& base_layer_profile);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief All configuration points associated with this element.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& configuration_points() const;
    std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& configuration_points();
    void configuration_points(const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& v);
    void configuration_points(const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>&& v);
    /**@}*/

    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

    const std::unordered_set<std::string>& stereotype() const;
    std::unordered_set<std::string>& stereotype();
    void stereotype(const std::unordered_set<std::string>& v);
    void stereotype(const std::unordered_set<std::string>&& v);

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
    bool equals(const dogen::variability::meta_model::element& other) const override;

public:
    void swap(profile& other) noexcept;
    profile& operator=(profile other);

private:
    std::unordered_map<std::string, dogen::variability::meta_model::configuration_point> configuration_points_;
    std::list<std::string> parents_;
    std::unordered_set<std::string> stereotype_;
    bool merged_;
    std::string base_layer_profile_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::meta_model::profile& lhs,
    dogen::variability::meta_model::profile& rhs) {
    lhs.swap(rhs);
}

}

#endif
