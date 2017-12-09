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
#ifndef DOGEN_YARN_DIA_TYPES_NEW_ADAPTER_HPP
#define DOGEN_YARN_DIA_TYPES_NEW_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen {
namespace yarn {
namespace dia {

class new_adapter final {
public:
    new_adapter() = default;
    new_adapter(const new_adapter&) = default;
    new_adapter(new_adapter&&) = default;
    ~new_adapter() = default;
    new_adapter& operator=(const new_adapter&) = default;

public:
    bool operator==(const new_adapter& rhs) const;
    bool operator!=(const new_adapter& rhs) const {
        return !this->operator==(rhs);
    }

};

} } }

#endif
