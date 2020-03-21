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
#ifndef DOGEN_M2T_TYPES_TRANSFORMS_FORMATTING_CONFIGURATION_HPP
#define DOGEN_M2T_TYPES_TRANSFORMS_FORMATTING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.m2t/types/entities/formatting_styles.hpp"

namespace dogen::m2t::transforms {

class formatting_configuration final {
public:
    formatting_configuration(const formatting_configuration&) = default;
    formatting_configuration(formatting_configuration&&) = default;
    ~formatting_configuration() = default;

public:
    formatting_configuration();

public:
    formatting_configuration(
        const dogen::m2t::entities::formatting_styles style,
        const std::string& input);

public:
    dogen::m2t::entities::formatting_styles style() const;
    void style(const dogen::m2t::entities::formatting_styles v);

    const std::string& input() const;
    std::string& input();
    void input(const std::string& v);
    void input(const std::string&& v);

public:
    bool operator==(const formatting_configuration& rhs) const;
    bool operator!=(const formatting_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formatting_configuration& other) noexcept;
    formatting_configuration& operator=(formatting_configuration other);

private:
    dogen::m2t::entities::formatting_styles style_;
    std::string input_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::transforms::formatting_configuration& lhs,
    dogen::m2t::transforms::formatting_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
