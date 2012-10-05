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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_BOOLEAN_HPP
#define DOGEN_DIA_DOMAIN_BOOLEAN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class boolean_serializer; } }

/**
 * @brief Represents a boolean value
 */
class boolean {
public:
    boolean() = default;
    boolean(const boolean&) = default;
    ~boolean() = default;
    boolean(boolean&&) = default;
    boolean& operator=(const boolean&) = default;

private:
    friend class dogen::dia::serialization::detail::boolean_serializer;

public:
    boolean(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of a boolean value
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

    bool operator==(const dogen::dia::boolean& value) const {
        return(value_ == value.value());
    }

    bool operator!=(const dogen::dia::boolean& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif
