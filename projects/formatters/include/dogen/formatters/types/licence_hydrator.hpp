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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_FORMATTERS_TYPES_LICENCE_HYDRATOR_HPP
#define DOGEN_FORMATTERS_TYPES_LICENCE_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <istream>
#include "dogen/formatters/types/licence.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Hydrates a licence based on the contents of the stream.
 */
class licence_hydrator {
public:
    typedef licence value_type;

public:
    licence_hydrator() = delete;
    licence_hydrator(const licence_hydrator&) = default;
    licence_hydrator(licence_hydrator&&) = default;
    ~licence_hydrator() = default;

public:
    /**
     *
     * Initialises the hydrator.
     *
     * @param copyright_holders holders to apply to every licence
     * hydrated.
     */
    explicit licence_hydrator(const std::list<std::string>& copyright_holders);

    /**
     * @brief Hydrate a licence based on the contents of the stream.
     */
    value_type hydrate(std::istream& s) const;

private:
    const std::list<std::string>& copyright_holders_;
};

} }

#endif
