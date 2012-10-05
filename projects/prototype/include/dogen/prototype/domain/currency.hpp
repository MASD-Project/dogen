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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_PROTOTYPE_DOMAIN_CURRENCY_HPP
#define DOGEN_PROTOTYPE_DOMAIN_CURRENCY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/prototype/domain/versioned_key.hpp"

namespace dogen {
namespace prototype {

class currency_serializer;

/*
 * @brief Currency, as defined by ISO 4217.
 *
 * The standard states:
 *
 * ISO's currency codes, which are based on the ISO country codes, are
 * published in the standard ISO 4217:2008 Codes for the
 * representation of currencies and funds.
 *
 * This standard specifies the structure for a three-letter alphabetic
 * code and an equivalent three-digit numeric code for the
 * representation of currencies and funds. For those currencies having
 * minor units, it also shows the decimal relationship between such
 * units and the currency itself.
 */
class currency {
private:
    friend class currency_serializer;

public:
    currency();

    currency(const std::string& name,
        const std::string& alpha_code,
        const unsigned int decimal_places,
        const unsigned int numeric_code,
        const dogen::prototype::versioned_key versioned_key =
        dogen::prototype::versioned_key());

public:
    void to_stream(std::ostream& stream) const;

public:
    /**
     * @brief Currency name.
     */
    /*@{*/
    std::string name() const { return(name_); }
    void name(const std::string& value) { name_ = value; }
    /*@}*/

    /**
     * @brief Three-letter currency code.
     */
    /*@{*/
    std::string alpha_code() const { return(alpha_code_); }
    void alpha_code(const std::string& value) { alpha_code_ = value; }
    /*@}*/

    /**
     * @brief Represents the numeric code in ISO 4217.
     */
    /*@{*/
    unsigned int numeric_code() const { return(numeric_code_); }
    void numeric_code(unsigned int value) { numeric_code_ = value; }
    /*@}*/

    /**
     * @brief Number of digits after the decimal point.
     */
    /*@{*/
    unsigned int decimal_places() const { return(decimal_places_); }
    void decimal_places(const unsigned int& value) { decimal_places_ = value; }
    /*@}*/

    /**
     * @brief
     */
    /*@{*/
    dogen::prototype::versioned_key versioned_key() const {
        return(versioned_key_);
    }
    void versioned_key(dogen::prototype::versioned_key value) {
        versioned_key_ = value;
    }
    /*@}*/

public:
    bool operator<(const currency& rhs) const {
        return(numeric_code_ < rhs.numeric_code());
    }

    bool operator==(const currency& rhs) const {
        return(name_ == rhs.name() &&
            alpha_code_ == rhs.alpha_code() &&
            decimal_places_ == rhs.decimal_places() &&
            numeric_code_ == rhs.numeric_code() &&
            versioned_key_ == rhs.versioned_key());
    }

    bool operator!=(const currency& rhs) const {
        return(!this->operator==(rhs));
    }

    bool is_equivalent(const currency& rhs) const {
        return(name_ == rhs.name() &&
               alpha_code_ == rhs.alpha_code() &&
               decimal_places_ == rhs.decimal_places());
    }

private:
    std::string name_;
    std::string alpha_code_;
    unsigned int decimal_places_;
    unsigned int numeric_code_;
    dogen::prototype::versioned_key versioned_key_;
};

} }

#endif
