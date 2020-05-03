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
#ifndef DOGEN_TEXT_TYPES_FORMATTERS_DEPENDENCIES_FORMATTER_HPP
#define DOGEN_TEXT_TYPES_FORMATTERS_DEPENDENCIES_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include "dogen.logical/types/entities/technical_space.hpp"

namespace dogen::text::formatters {

/**
 * @brief Generates dependencies import statements for the requested
 * technical space.
 */
class dependencies_formatter final {
private:
    /**
     * @brief Generates preprocessor include statements.
     */
    void format_cpp_includes(std::ostream& s,
        const std::list<std::string>& dependencies) const;

    /**
     * @brief Generates using statements.
     */
    void format_csharp_usings(std::ostream& s,
        const std::list<std::string>& dependencies) const;

public:
    void format(std::ostream& s, const logical::entities::technical_space ts,
        const std::list<std::string>& dependencies) const;
};

}

#endif
