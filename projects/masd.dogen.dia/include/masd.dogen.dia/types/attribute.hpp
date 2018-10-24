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
#ifndef MASD_DOGEN_DIA_TYPES_ATTRIBUTE_HPP
#define MASD_DOGEN_DIA_TYPES_ATTRIBUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/variant.hpp>
#include "masd.dogen.dia/types/font.hpp"
#include "masd.dogen.dia/types/real.hpp"
#include "masd.dogen.dia/types/color.hpp"
#include "masd.dogen.dia/types/point.hpp"
#include "masd.dogen.dia/types/string.hpp"
#include "masd.dogen.dia/types/boolean.hpp"
#include "masd.dogen.dia/types/integer.hpp"
#include "masd.dogen.dia/types/composite.hpp"
#include "masd.dogen.dia/types/rectangle.hpp"
#include "masd.dogen.dia/types/enumeration.hpp"
#include "masd.dogen.dia/serialization/attribute_fwd_ser.hpp"

namespace masd::dogen::dia {

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
        const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& values);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const masd::dogen::dia::attribute& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, masd::dogen::dia::attribute& v, unsigned int version);

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
    const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& values() const;
    std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& values();
    void values(const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& v);
    void values(const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >&& v);
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
    std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> > values_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::dia::attribute& lhs,
    masd::dogen::dia::attribute& rhs) {
    lhs.swap(rhs);
}

}

#endif
