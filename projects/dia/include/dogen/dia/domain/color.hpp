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
#ifndef DOGEN_DIA_DOMAIN_COLOR_HPP
#define DOGEN_DIA_DOMAIN_COLOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class color_serializer; } }

/**
 * @brief Represents a color in a diagram.
 */
class color {
public:
    color() = default;
    color(const color&) = default;
    ~color() = default;
    color(color&&) = default;
    color& operator=(const color&) = default;

private:
    friend class dogen::dia::serialization::detail::color_serializer;

public:
    explicit color(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of an RGB value in hex.
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

public:
    bool operator==(const dogen::dia::color& value) const {
        return(value_ == value.value());
    }

    bool operator!=(const dogen::dia::color& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif
