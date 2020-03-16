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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_POINT_TEMPLATE_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_POINT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.variability/types/entities/element.hpp"

namespace dogen::variability::entities {

class configuration_point_template final : public dogen::variability::entities::element {
public:
    configuration_point_template() = default;
    configuration_point_template(const configuration_point_template&) = default;
    configuration_point_template(configuration_point_template&&) = default;

    virtual ~configuration_point_template() noexcept { }

public:
    configuration_point_template(
        const dogen::variability::entities::name& name,
        const std::string& description,
        const std::string& instantiation_domain_name,
        const std::list<std::string>& untyped_value);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Name of the domain to use for template instantiation.
     *
     * @pre The instantiation domain name must exist.
     */
    /**@{*/
    const std::string& instantiation_domain_name() const;
    std::string& instantiation_domain_name();
    void instantiation_domain_name(const std::string& v);
    void instantiation_domain_name(const std::string&& v);
    /**@}*/

    const std::list<std::string>& untyped_value() const;
    std::list<std::string>& untyped_value();
    void untyped_value(const std::list<std::string>& v);
    void untyped_value(const std::list<std::string>&& v);

public:
    bool operator==(const configuration_point_template& rhs) const;
    bool operator!=(const configuration_point_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::variability::entities::element& other) const override;

public:
    void swap(configuration_point_template& other) noexcept;
    configuration_point_template& operator=(configuration_point_template other);

private:
    std::string instantiation_domain_name_;
    std::list<std::string> untyped_value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::configuration_point_template& lhs,
    dogen::variability::entities::configuration_point_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
