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
#ifndef MASD_DOGEN_TAILOR_PARSER_VALIDATION_ERROR_HPP
#define MASD_DOGEN_TAILOR_PARSER_VALIDATION_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.utility/exception/utility_exception.hpp"

namespace dogen::tailor {

/**
 * @brief A fatal error has occurred during option parsing.
 */
class parser_validation_error
    : public masd::dogen::utility::exception::exception {
public:
    parser_validation_error(std::string message)
        : masd::dogen::utility::exception::exception(message) { }
    parser_validation_error() { }

    virtual ~parser_validation_error() throw() {}
};

}

#endif
