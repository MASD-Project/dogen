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
#ifndef DOGEN_CONFIG_TYPES_SQL_SETTINGS_HPP
#define DOGEN_CONFIG_TYPES_SQL_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/config/serialization/sql_settings_fwd_ser.hpp"

namespace dogen {
namespace config {

class sql_settings final {
public:
    sql_settings(const sql_settings&) = default;
    sql_settings(sql_settings&&) = default;
    ~sql_settings() = default;

public:
    sql_settings();

public:
    sql_settings(
        const bool verbose,
        const bool disable_backend,
        const bool create_schema,
        const std::string& schema_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const sql_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, sql_settings& v, unsigned int version);

public:
    /*
     * @brief Print additional diagnostic information to standard output.
     */
    /**@{*/
    bool verbose() const;
    void verbose(const bool v);
    /**@}*/

    /*
     * @brief Disable the C++ backend entirely.
     */
    /**@{*/
    bool disable_backend() const;
    void disable_backend(const bool v);
    /**@}*/

    /*
     * @brief If true, the DDL for creating a new schema is
     * generated.
     */
    /**@{*/
    bool create_schema() const;
    void create_schema(const bool v);
    /**@}*/

    /*
     * @brief Name of the database schema in which to place the domain
     * types.
     */
    /**@{*/
    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);
    /**@}*/

public:
    bool operator==(const sql_settings& rhs) const;
    bool operator!=(const sql_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(sql_settings& other) noexcept;
    sql_settings& operator=(sql_settings other);

private:
    bool verbose_;
    bool disable_backend_;
    bool create_schema_;
    std::string schema_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::sql_settings& lhs,
    dogen::config::sql_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
