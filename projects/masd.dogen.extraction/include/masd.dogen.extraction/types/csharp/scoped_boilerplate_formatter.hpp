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
#ifndef MASD_DOGEN_FORMATTNG_TYPES_CSHARP_SCOPED_BOILERPLATE_FORMATTER_HPP
#define MASD_DOGEN_FORMATTNG_TYPES_CSHARP_SCOPED_BOILERPLATE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <boost/optional.hpp>
#include "masd.dogen.extraction/types/csharp/boilerplate_formatter.hpp"

namespace masd::dogen::extraction::csharp {

/**
 * @brief RAII wrapper around the boilerplate formatter.
 */
class scoped_boilerplate_formatter {
public:
    scoped_boilerplate_formatter(
        std::ostream& s, const std::string& preamble,
        const std::string& postamble, const std::list<std::string>& usings);

    ~scoped_boilerplate_formatter();

private:
    std::ostream& stream_;
    const std::string preamble_;
    const std::string postamble_;
    const std::list<std::string> usings_;
    const boilerplate_formatter formatter_;
};

}

#endif
