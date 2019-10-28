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
#ifndef DOGEN_LEXICAL_CAST_RELATIONAL_DATABASE_LC_HPP
#define DOGEN_LEXICAL_CAST_RELATIONAL_DATABASE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen/types/relational_database.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::relational_database& v) {
    using dogen::relational_database;

    switch (v) {
    case relational_database::invalid:
        return "relational_database::invalid";
    case relational_database::postgres:
        return "relational_database::postgres";
    case relational_database::sqlite:
        return "relational_database::sqlite";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::relational_database lexical_cast(const std::string & s) {
    using dogen::relational_database;

    if (s == "invalid" || s == "relational_database::invalid")
        return relational_database::invalid;
    if (s == "postgres" || s == "relational_database::postgres")
        return relational_database::postgres;
    if (s == "sqlite" || s == "relational_database::sqlite")
        return relational_database::sqlite;
    throw boost::bad_lexical_cast();
}

}

#endif
