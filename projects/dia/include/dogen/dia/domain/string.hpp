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
#ifndef DOGEN_DIA_DOMAIN_STRING_HPP
#define DOGEN_DIA_DOMAIN_STRING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class string_serializer; } }

/**
 * @brief Represents a string value.
 */
class string {
public:
    string() = default;
    string(const string&) = default;
    ~string() = default;
    string(string&&) = default;
    string& operator=(const string&) = default;

private:
    friend class dogen::dia::serialization::detail::string_serializer;

public:
    explicit string(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of a string value.
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

public:
    bool operator==(const dogen::dia::string& value) const {
        return(value_ == value.value());
    }

    bool operator!=(const dogen::dia::string& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif
