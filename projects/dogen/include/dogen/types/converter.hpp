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
#ifndef DOGEN_TYPES_CONVERTER_HPP
#define DOGEN_TYPES_CONVERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/types/configuration.hpp"

namespace dogen {

/**
 * @brief Converts a supported model type into another.
 */
class converter {
public:
    converter() = default;
    converter(const converter&) = delete;
    converter(converter&&) = delete;
    virtual ~converter() noexcept = default;
    converter& operator=(const converter&) = delete;

public:
    virtual void convert(const configuration& cfg,
        const boost::filesystem::path& source,
        const boost::filesystem::path& destination) const = 0;
};

}

#endif
