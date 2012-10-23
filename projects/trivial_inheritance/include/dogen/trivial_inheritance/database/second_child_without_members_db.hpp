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
#ifndef DOGEN_TRIVIAL_INHERITANCE_DATABASE_SECOND_CHILD_WITHOUT_MEMBERS_DB_HPP
#define DOGEN_TRIVIAL_INHERITANCE_DATABASE_SECOND_CHILD_WITHOUT_MEMBERS_DB_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include <pqxx/connection.hxx>
#include <vector>
#include "dogen/trivial_inheritance/domain/second_child_without_members.hpp"

namespace dogen {
namespace trivial_inheritance {

class second_child_without_members_data_exchanger {
public:
    second_child_without_members_data_exchanger() = default;
    second_child_without_members_data_exchanger(const second_child_without_members_data_exchanger&) = delete;
    ~second_child_without_members_data_exchanger() = default;
    second_child_without_members_data_exchanger(second_child_without_members_data_exchanger&&) = delete;

private:
    std::string format_sql(const std::string& format_str,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

    std::vector<dogen::trivial_inheritance::second_child_without_members> load_internal(
        pqxx::connection& connection,
        const boost::optional<versioned_key> id =boost::optional<versioned_key>());

    void erase_internal(pqxx::connection& connection,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

public:
    std::vector<dogen::trivial_inheritance::second_child_without_members> load(
        pqxx::connection& connection,
        const boost::optional<versioned_key> id =boost::optional<versioned_key>());

    void save(
        pqxx::connection& connection,
        std::vector<dogen::trivial_inheritance::second_child_without_members> values);

    void erase(pqxx::connection& connection);
    void erase(pqxx::connection& connection, versioned_key id);
};

} }
#endif
