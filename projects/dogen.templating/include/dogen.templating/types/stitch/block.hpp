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
#ifndef DOGEN_TEMPLATING_TYPES_STITCH_BLOCK_HPP
#define DOGEN_TEMPLATING_TYPES_STITCH_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.templating/types/stitch/block_types.hpp"

namespace dogen {
namespace templating {
namespace stitch {

class block final {
public:
    block(const block&) = default;
    block(block&&) = default;
    ~block() = default;

public:
    block();

public:
    block(
        const dogen::templating::stitch::block_types type,
        const std::string& content);

public:
    dogen::templating::stitch::block_types type() const;
    void type(const dogen::templating::stitch::block_types v);

    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);

public:
    bool operator==(const block& rhs) const;
    bool operator!=(const block& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(block& other) noexcept;
    block& operator=(block other);

private:
    dogen::templating::stitch::block_types type_;
    std::string content_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::templating::stitch::block& lhs,
    dogen::templating::stitch::block& rhs) {
    lhs.swap(rhs);
}

}

#endif
