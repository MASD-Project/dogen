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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_CONFIGURATION_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "masd.dogen.variability/types/meta_model/element.hpp"
#include "masd.dogen.variability/types/meta_model/binding_type.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_point.hpp"

namespace masd::dogen::variability::meta_model {

class configuration final : public masd::dogen::variability::meta_model::element {
public:
    configuration() = default;
    configuration(const configuration&) = default;

    virtual ~configuration() noexcept { }

public:
    configuration(configuration&& rhs);

public:
    configuration(
        const masd::dogen::variability::meta_model::name& name,
        const std::string& description,
        const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& configuration_points,
        const boost::optional<masd::dogen::variability::meta_model::binding_type>& binding);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief All configuration points in this configuration.
     */
    /**@{*/
    const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& configuration_points() const;
    std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& configuration_points();
    void configuration_points(const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& v);
    void configuration_points(const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>&& v);
    /**@}*/

    /**
     * @brief Type of binding available for this configuration, if bound.
     */
    /**@{*/
    const boost::optional<masd::dogen::variability::meta_model::binding_type>& binding() const;
    boost::optional<masd::dogen::variability::meta_model::binding_type>& binding();
    void binding(const boost::optional<masd::dogen::variability::meta_model::binding_type>& v);
    void binding(const boost::optional<masd::dogen::variability::meta_model::binding_type>&& v);
    /**@}*/

public:
    bool operator==(const configuration& rhs) const;
    bool operator!=(const configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::variability::meta_model::element& other) const override;

public:
    void swap(configuration& other) noexcept;
    configuration& operator=(configuration other);

private:
    std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point> configuration_points_;
    boost::optional<masd::dogen::variability::meta_model::binding_type> binding_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::meta_model::configuration& lhs,
    masd::dogen::variability::meta_model::configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
