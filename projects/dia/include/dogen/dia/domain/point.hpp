/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_POINT_HPP
#define DOGEN_DIA_DOMAIN_POINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class point_serializer; } }

/**
 * @brief Represents a point in a diagram.
 */
class point {
public:
    point() = default;
    point(const point&) = default;
    ~point() = default;
    point(point&&) = default;
    point& operator=(const point&) = default;

private:
    friend class dogen::dia::serialization::detail::point_serializer;

public:
    explicit point(std::string value) : value_(value) { }

public:
    /**
     * @brief Text representation of a point with X/Y coordinates.
     */
    /**@{*/
    std::string value() const { return(value_); }
    void value(std::string value) { value_ = value; }
    /**@}*/

public:
    bool operator==(const dogen::dia::point& value) const {
        return value_ == value.value();
    }

    bool operator!=(const dogen::dia::point& value) const {
        return(!this->operator==(value));
    }

private:
    std::string value_;
};

} }

#endif
