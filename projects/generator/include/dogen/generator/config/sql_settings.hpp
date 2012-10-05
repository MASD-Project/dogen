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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_GENERATOR_CONFIG_SQL_SETTINGS_HPP
#define DOGEN_GENERATOR_CONFIG_SQL_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace generator {
namespace config {

class sql_settings {
public:
    sql_settings(const sql_settings&) = default;
    ~sql_settings() = default;
    sql_settings& operator=(const sql_settings&) = default;
    sql_settings(sql_settings&&) = default;

public:
    sql_settings() :
        verbose_(false),
        disable_backend_(false),
        create_schema_(false) {}

public:
    /**
     * @brief Print additional diagnostic information to standard output.
     */
    /**@{*/
    bool verbose() const { return verbose_; }
    sql_settings& verbose(bool value) {
        verbose_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Disable the C++ backend entirely.
     */
    /**@{*/
    bool disable_backend() const { return disable_backend_; }
    sql_settings& disable_backend(bool value) {
        disable_backend_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief If true, the DDL for creating a new schema is
     * generated.
     */
    /**@{*/
    bool create_schema() const { return create_schema_; }
    sql_settings& create_schema(bool value) {
        create_schema_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Name of the database schema in which to place the domain
     * types.
     */
    /**@{*/
    std::string schema_name() const { return schema_name_; }
    sql_settings& schema_name(std::string value) {
        schema_name_ = value;
        return *this;
    }
    /**@*/

private:
    bool verbose_;
    bool disable_backend_;
    bool create_schema_;
    std::string schema_name_;
};

std::ostream& operator<<(std::ostream& stream, sql_settings value);

} } }

#endif
