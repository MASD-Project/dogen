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
#ifndef DOGEN_LEXICAL_CAST_DATABASE_ENGINE_LC_HPP
#define DOGEN_LEXICAL_CAST_DATABASE_ENGINE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen/types/database_engine.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::database_engine& v) {
    using dogen::database_engine;

    switch (v) {
    case database_engine::invalid:
        return "database_engine::invalid";
    case database_engine::postgres:
        return "database_engine::postgres";
    case database_engine::sqlite:
        return "database_engine::sqlite";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::database_engine lexical_cast(const std::string & s) {
    using dogen::database_engine;

    if (s == "invalid" || s == "database_engine::invalid")
        return database_engine::invalid;
    if (s == "postgres" || s == "database_engine::postgres")
        return database_engine::postgres;
    if (s == "sqlite" || s == "database_engine::sqlite")
        return database_engine::sqlite;
    throw boost::bad_lexical_cast();
}

}

#endif
