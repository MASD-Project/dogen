/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
