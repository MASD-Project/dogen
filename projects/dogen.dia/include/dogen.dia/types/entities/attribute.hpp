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
#ifndef DOGEN_DIA_TYPES_ENTITIES_ATTRIBUTE_HPP
#define DOGEN_DIA_TYPES_ENTITIES_ATTRIBUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/variant.hpp>
#include "dogen.dia/types/entities/font.hpp"
#include "dogen.dia/types/entities/real.hpp"
#include "dogen.dia/types/entities/color.hpp"
#include "dogen.dia/types/entities/point.hpp"
#include "dogen.dia/types/entities/string.hpp"
#include "dogen.dia/types/entities/boolean.hpp"
#include "dogen.dia/types/entities/integer.hpp"
#include "dogen.dia/types/entities/composite.hpp"
#include "dogen.dia/types/entities/rectangle.hpp"
#include "dogen.dia/types/entities/enumeration.hpp"

namespace dogen::dia::entities {

/**
 * @brief Attribute in a Dia diagram.
 */
class attribute final {
public:
    attribute() = default;
    attribute(const attribute&) = default;
    attribute(attribute&&) = default;
    ~attribute() = default;

public:
    attribute(
        const std::string& name,
        const std::vector<boost::variant<dogen::dia::entities::color, dogen::dia::entities::real, dogen::dia::entities::integer, dogen::dia::entities::font, dogen::dia::entities::boolean, dogen::dia::entities::point, dogen::dia::entities::string, dogen::dia::entities::enumeration, dogen::dia::entities::rectangle, dogen::dia::entities::composite> >& values);

public:
    /**
     * @brief Name of the attribute.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Values for the attribute.
     */
    /**@{*/
    const std::vector<boost::variant<dogen::dia::entities::color, dogen::dia::entities::real, dogen::dia::entities::integer, dogen::dia::entities::font, dogen::dia::entities::boolean, dogen::dia::entities::point, dogen::dia::entities::string, dogen::dia::entities::enumeration, dogen::dia::entities::rectangle, dogen::dia::entities::composite> >& values() const;
    std::vector<boost::variant<dogen::dia::entities::color, dogen::dia::entities::real, dogen::dia::entities::integer, dogen::dia::entities::font, dogen::dia::entities::boolean, dogen::dia::entities::point, dogen::dia::entities::string, dogen::dia::entities::enumeration, dogen::dia::entities::rectangle, dogen::dia::entities::composite> >& values();
    void values(const std::vector<boost::variant<dogen::dia::entities::color, dogen::dia::entities::real, dogen::dia::entities::integer, dogen::dia::entities::font, dogen::dia::entities::boolean, dogen::dia::entities::point, dogen::dia::entities::string, dogen::dia::entities::enumeration, dogen::dia::entities::rectangle, dogen::dia::entities::composite> >& v);
    void values(const std::vector<boost::variant<dogen::dia::entities::color, dogen::dia::entities::real, dogen::dia::entities::integer, dogen::dia::entities::font, dogen::dia::entities::boolean, dogen::dia::entities::point, dogen::dia::entities::string, dogen::dia::entities::enumeration, dogen::dia::entities::rectangle, dogen::dia::entities::composite> >&& v);
    /**@}*/

public:
    bool operator==(const attribute& rhs) const;
    bool operator!=(const attribute& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(attribute& other) noexcept;
    attribute& operator=(attribute other);

private:
    std::string name_;
    std::vector<boost::variant<dogen::dia::entities::color, dogen::dia::entities::real, dogen::dia::entities::integer, dogen::dia::entities::font, dogen::dia::entities::boolean, dogen::dia::entities::point, dogen::dia::entities::string, dogen::dia::entities::enumeration, dogen::dia::entities::rectangle, dogen::dia::entities::composite> > values_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::attribute& lhs,
    dogen::dia::entities::attribute& rhs) {
    lhs.swap(rhs);
}

}

#endif
