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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_PROTOTYPE_DATABASE_CURRENCY_DB_HPP
#define DOGEN_PROTOTYPE_DATABASE_CURRENCY_DB_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <boost/optional.hpp>
#include <pqxx/connection.hxx>
#include "dogen/prototype/domain/currency.hpp"

namespace dogen {
namespace prototype {

class currency_data_exchanger {
private:
    std::string format_sql(const std::string& format_str,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

    std::vector<dogen::prototype::currency> load_internal(
        pqxx::connection& connection,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

    void erase_internal(pqxx::connection& connection,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

public:
    /**
     * @brief Loads all currencies in the database.
     */
    std::vector<dogen::prototype::currency> load(pqxx::connection& connection);

    /**
     * @brief Loads all currencies matching primary key id present in
     * the database.
     */
    std::vector<dogen::prototype::currency> load(
        pqxx::connection& connection,
        const dogen::prototype::versioned_key& id);

    void save(pqxx::connection& connection,
        std::vector<dogen::prototype::currency>& currencies);

    void erase(pqxx::connection& connection);

    void erase(pqxx::connection& connection,
        const dogen::prototype::versioned_key& id);
};

} }

#endif
