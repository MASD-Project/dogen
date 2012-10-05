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
#ifndef DOGEN_DIA_DOMAIN_FONT_HPP
#define DOGEN_DIA_DOMAIN_FONT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class font_serializer; } }

/**
 * @brief Represents a font in a diagram.
 */
class font {
public:
    font() = default;
    font(const font&) = default;
    ~font() = default;
    font(font&&) = default;
    font& operator=(const font&) = default;

private:
    friend class dogen::dia::serialization::detail::font_serializer;

public:
    font(std::string family, std::string style, std::string name)
        : family_(family), style_(style), name_(name) { }

public:
    /**
     * @brief
     */
    /**@{*/
    std::string family() const { return(family_); }
    void family(std::string family) { family_ = family; }
    /**@}*/

    /**
     * @brief
     */
    /**@{*/
    std::string style() const { return(style_); }
    void style(std::string style) { style_ = style; }
    /**@}*/

    /**
     * @brief
     */
    /**@{*/
    std::string name() const { return(name_); }
    void name(std::string name) { name_ = name; }
    /**@}*/

public:
    bool operator==(const dogen::dia::font& value) const {
        return
            family_ == value.family() &&
            style_ == value.style() &&
            name_ == value.name();
    }

    bool operator!=(const dogen::dia::font& value) const {
        return(!this->operator==(value));
    }

private:
    std::string family_;
    std::string style_;
    std::string name_;
};

} }

#endif
