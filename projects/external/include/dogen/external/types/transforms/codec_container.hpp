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
#ifndef DOGEN_EXTERNAL_TYPES_TRANSFORMS_CODEC_CONTAINER_HPP
#define DOGEN_EXTERNAL_TYPES_TRANSFORMS_CODEC_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen {
namespace external {
namespace transforms {

class codec_container final {
public:
    codec_container() = default;
    codec_container(const codec_container&) = default;
    codec_container(codec_container&&) = default;
    ~codec_container() = default;
    codec_container& operator=(const codec_container&) = default;

public:
    bool operator==(const codec_container& rhs) const;
    bool operator!=(const codec_container& rhs) const {
        return !this->operator==(rhs);
    }

};

} } }

#endif
