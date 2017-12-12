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
#ifndef DOGEN_FORMATTERS_TYPES_LICENCE_HYDRATOR_HPP
#define DOGEN_FORMATTERS_TYPES_LICENCE_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <iosfwd>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace formatters {

/**
 * @brief Hydrates the licence text from a stream or file.
 */
class licence_text_hydrator {
public:
    licence_text_hydrator() = default;
    licence_text_hydrator(const licence_text_hydrator&) = default;
    licence_text_hydrator(licence_text_hydrator&&) = default;
    ~licence_text_hydrator() = default;

public:
    /**
     * @brief Hydrate a licence text from a stream.
     */
    std::string hydrate(std::istream& s) const;

    /**
     * @brief Hydrate a licence text from the supplied path.
     */
    std::string hydrate(const boost::filesystem::path& p) const;
};

} }

#endif
