/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_ATTRIBUTE_HPP
#define DOGEN_DIA_DOMAIN_ATTRIBUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <utility>
#include <boost/variant.hpp>
#include "dogen/dia/domain/color.hpp"
#include "dogen/dia/domain/point.hpp"
#include "dogen/dia/domain/real.hpp"
#include "dogen/dia/domain/integer.hpp"
#include "dogen/dia/domain/boolean.hpp"
#include "dogen/dia/domain/string.hpp"
#include "dogen/dia/domain/rectangle.hpp"
#include "dogen/dia/domain/composite.hpp"
#include "dogen/dia/domain/font.hpp"
#include "dogen/dia/domain/enumeration.hpp"

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class attribute_serializer; } }

struct empty {
    int dummy;
    bool operator==(const empty&) const { return true; }
};

/**
 * @brief Attribute in a Dia diagram.
 */
class attribute {
public:
    typedef boost::variant<
    empty,
    color,
    point,
    real,
    integer,
    boolean,
    string,
    rectangle,
    font,
    enumeration,
    std::vector<composite>
    > attribute_value;

public:
    attribute() = default;
    attribute(const attribute&) = default;
    ~attribute() = default;
    attribute& operator=(const attribute&) = default;

private:
    friend class dogen::dia::serialization::detail::attribute_serializer;

public:
    attribute(std::string name, attribute_value value)
        : name_(name), value_(value) { }

    explicit attribute(attribute&& other) : name_(std::move(other.name_)),
                                   value_(std::move(other.value_)) { }

public:
    /**
     * @brief Name of the attribute.
     */
    /**@{*/
    std::string name() const { return(name_); }
    void name(std::string value) { name_ = value; }
    /**@}*/

    /**
     * @brief Value of the attribute.
     */
    /**@{*/
    attribute_value value() const { return(value_); }
    void value(attribute_value value) { value_ = value; }
    /**@}*/

public:
    bool operator==(const dogen::dia::attribute& value) const {
        return
            name_ == value.name() &&
            value_ == value.value();
    }

    bool operator!=(const dogen::dia::attribute& value) const {
        return(!this->operator==(value));
    }

private:
    std::string name_;
    attribute_value value_;
};

} }

#endif
