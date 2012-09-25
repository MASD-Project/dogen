/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_ENUMERATION_HPP
#define DOGEN_DIA_DOMAIN_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class enumeration_serializer; } }

/**
 * @brief Represents a enumeration in a diagram.
 */
class enumeration {
public:
    enumeration() = default;
    enumeration(const enumeration&) = default;
    ~enumeration() = default;
    enumeration(enumeration&&) = default;
    enumeration& operator=(const enumeration&) = default;

private:
    friend class dogen::dia::serialization::detail::enumeration_serializer;

public:
    explicit enumeration(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of a enumeration.
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

public:
    bool operator==(const dogen::dia::enumeration& value) const {
        return value_ == value.value();
    }

    bool operator!=(const dogen::dia::enumeration& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif
