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
#ifndef DOGEN_TYPES_SPEC_DUMPER_HPP
#define DOGEN_TYPES_SPEC_DUMPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/types/specs.hpp"
#include "dogen/types/configuration.hpp"

namespace dogen {

/**
 * @brief Dumps internal information from Dogen.
 */
class spec_dumper {
public:
    spec_dumper() = default;
    spec_dumper(const spec_dumper&) = delete;
    spec_dumper(spec_dumper&&) = delete;
    virtual ~spec_dumper() noexcept = default;
    spec_dumper& operator=(const spec_dumper&) = delete;

public:
    virtual specs dump(const configuration& cfg) const = 0;
};

}

#endif
