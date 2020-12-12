/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_DIA_TYPES_ENTITIES_FONT_HPP
#define DOGEN_DIA_TYPES_ENTITIES_FONT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::dia::entities {

/**
 * @brief Represents a font in a diagram.
 */
class font final {
public:
    font() = default;
    font(const font&) = default;
    font(font&&) = default;
    ~font() = default;

public:
    font(
        const std::string& family,
        const std::string& style,
        const std::string& name);

public:
    const std::string& family() const;
    std::string& family();
    void family(const std::string& v);
    void family(const std::string&& v);

    const std::string& style() const;
    std::string& style();
    void style(const std::string& v);
    void style(const std::string&& v);

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

public:
    bool operator==(const font& rhs) const;
    bool operator!=(const font& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(font& other) noexcept;
    font& operator=(font other);

private:
    std::string family_;
    std::string style_;
    std::string name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::font& lhs,
    dogen::dia::entities::font& rhs) {
    lhs.swap(rhs);
}

}

#endif
