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
#ifndef DOGEN_LOGICAL_LEXICAL_CAST_META_MODEL_ORM_DATABASE_SYSTEM_LC_HPP
#define DOGEN_LOGICAL_LEXICAL_CAST_META_MODEL_ORM_DATABASE_SYSTEM_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.logical/types/meta_model/orm/database_system.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::logical::meta_model::orm::database_system& v) {
    using dogen::logical::meta_model::orm::database_system;

    switch (v) {
    case database_system::invalid:
        return "database_system::invalid";
    case database_system::mysql:
        return "database_system::mysql";
    case database_system::postgresql:
        return "database_system::postgresql";
    case database_system::oracle:
        return "database_system::oracle";
    case database_system::sql_server:
        return "database_system::sql_server";
    case database_system::sqlite:
        return "database_system::sqlite";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::logical::meta_model::orm::database_system lexical_cast(const std::string & s) {
    using dogen::logical::meta_model::orm::database_system;

    if (s == "invalid" || s == "database_system::invalid")
        return database_system::invalid;
    if (s == "mysql" || s == "database_system::mysql")
        return database_system::mysql;
    if (s == "postgresql" || s == "database_system::postgresql")
        return database_system::postgresql;
    if (s == "oracle" || s == "database_system::oracle")
        return database_system::oracle;
    if (s == "sql_server" || s == "database_system::sql_server")
        return database_system::sql_server;
    if (s == "sqlite" || s == "database_system::sqlite")
        return database_system::sqlite;
    throw boost::bad_lexical_cast();
}

}

#endif
