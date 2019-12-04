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
#ifndef DOGEN_TYPES_DATABASE_CONFIGURATION_HPP
#define DOGEN_TYPES_DATABASE_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/types/database_engine.hpp"

namespace dogen {

/**
 * @brief Contains the config
 */
class database_configuration final {
public:
    database_configuration(const database_configuration&) = default;
    database_configuration(database_configuration&&) = default;
    ~database_configuration() = default;

public:
    database_configuration();

public:
    database_configuration(
        const std::string& host,
        const unsigned int port,
        const std::string& name,
        const std::string& user,
        const std::string& password,
        const dogen::database_engine engine,
        const bool generate_schema);

public:
    /**
     * @brief Database host to connect to.
     */
    /**@{*/
    const std::string& host() const;
    std::string& host();
    void host(const std::string& v);
    void host(const std::string&& v);
    /**@}*/

    /**
     * @brief Database port to connect to.
     */
    /**@{*/
    unsigned int port() const;
    void port(const unsigned int v);
    /**@}*/

    /**
     * @brief Name of the database to connect to.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief User to use in thedatabase connection.
     */
    /**@{*/
    const std::string& user() const;
    std::string& user();
    void user(const std::string& v);
    void user(const std::string&& v);
    /**@}*/

    const std::string& password() const;
    std::string& password();
    void password(const std::string& v);
    void password(const std::string&& v);

    /**
     * @brief Which relational database engine to connect to.
     */
    /**@{*/
    dogen::database_engine engine() const;
    void engine(const dogen::database_engine v);
    /**@}*/

    /**
     * @brief If true, deletes all tables and recreates them. Otherwise, assumes their presence.
     */
    /**@{*/
    bool generate_schema() const;
    void generate_schema(const bool v);
    /**@}*/

public:
    bool operator==(const database_configuration& rhs) const;
    bool operator!=(const database_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(database_configuration& other) noexcept;
    database_configuration& operator=(database_configuration other);

private:
    std::string host_;
    unsigned int port_;
    std::string name_;
    std::string user_;
    std::string password_;
    dogen::database_engine engine_;
    bool generate_schema_;
};

}

namespace std {

template<>
inline void swap(
    dogen::database_configuration& lhs,
    dogen::database_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
