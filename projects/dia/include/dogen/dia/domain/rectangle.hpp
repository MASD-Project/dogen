/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_RECTANGLE_HPP
#define DOGEN_DIA_DOMAIN_RECTANGLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class rectangle_serializer; } }

/**
 * @brief Represents a rectangle in a diagram.
 */
class rectangle {
public:
    rectangle() = default;
    rectangle(const rectangle&) = default;
    ~rectangle() = default;
    rectangle(rectangle&&) = default;
    rectangle& operator=(const rectangle&) = default;

public:
    explicit rectangle(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of a rectangle with a pair of X/Y coordinates.
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

private:
    friend class dogen::dia::serialization::detail::rectangle_serializer;

public:
    bool operator==(const dogen::dia::rectangle& value) const {
        return(value_ == value.value());
    }

    bool operator!=(const dogen::dia::rectangle& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif
