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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_CONFIGURATION_POINT_TEMPLATE_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_CONFIGURATION_POINT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "masd.dogen.archetypes/types/location.hpp"
#include "masd.dogen.variability/types/meta_model/element.hpp"
#include "masd.dogen.variability/types/meta_model/template_kind.hpp"

namespace masd::dogen::variability::meta_model {

class configuration_point_template final : public masd::dogen::variability::meta_model::element {
public:
    configuration_point_template(const configuration_point_template&) = default;
    configuration_point_template(configuration_point_template&&) = default;

public:
    configuration_point_template();

    virtual ~configuration_point_template() noexcept { }

public:
    configuration_point_template(
        const masd::dogen::variability::meta_model::name& name,
        const std::string& description,
        const masd::dogen::archetypes::location& location,
        const std::list<std::string>& untyped_value,
        const masd::dogen::variability::meta_model::template_kind kind);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief The location of this element in archetype space.
     */
    /**@{*/
    const masd::dogen::archetypes::location& location() const;
    masd::dogen::archetypes::location& location();
    void location(const masd::dogen::archetypes::location& v);
    void location(const masd::dogen::archetypes::location&& v);
    /**@}*/

    const std::list<std::string>& untyped_value() const;
    std::list<std::string>& untyped_value();
    void untyped_value(const std::list<std::string>& v);
    void untyped_value(const std::list<std::string>&& v);

    masd::dogen::variability::meta_model::template_kind kind() const;
    void kind(const masd::dogen::variability::meta_model::template_kind v);

public:
    bool operator==(const configuration_point_template& rhs) const;
    bool operator!=(const configuration_point_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::variability::meta_model::element& other) const override;

public:
    void swap(configuration_point_template& other) noexcept;
    configuration_point_template& operator=(configuration_point_template other);

private:
    masd::dogen::archetypes::location location_;
    std::list<std::string> untyped_value_;
    masd::dogen::variability::meta_model::template_kind kind_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::meta_model::configuration_point_template& lhs,
    masd::dogen::variability::meta_model::configuration_point_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
