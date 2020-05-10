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
#ifndef DOGEN_LOGICAL_TYPES_FORMATTERS_DECORATION_FORMATTER_HPP
#define DOGEN_LOGICAL_TYPES_FORMATTERS_DECORATION_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen::logical::formatters {

class decoration_formatter final {
public:
    decoration_formatter() = default;
    decoration_formatter(const decoration_formatter&) = default;
    decoration_formatter(decoration_formatter&&) = default;
    ~decoration_formatter() = default;
    decoration_formatter& operator=(const decoration_formatter&) = default;

public:
    bool operator==(const decoration_formatter& rhs) const;
    bool operator!=(const decoration_formatter& rhs) const {
        return !this->operator==(rhs);
    }

};

}

#endif
