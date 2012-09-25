/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_ALL_PRIMITIVES_DATABASE_A_CLASS_DB_HPP
#define DOGEN_ALL_PRIMITIVES_DATABASE_A_CLASS_DB_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include <pqxx/connection.hxx>
#include <vector>
#include "dogen/all_primitives/domain/a_class.hpp"

namespace dogen {
namespace all_primitives {

class a_class_data_exchanger {
public:
    a_class_data_exchanger() = default;
    a_class_data_exchanger(const a_class_data_exchanger&) = delete;
    ~a_class_data_exchanger() = default;
    a_class_data_exchanger(a_class_data_exchanger&&) = delete;

private:
    std::string format_sql(const std::string& format_str,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

    std::vector<dogen::all_primitives::a_class> load_internal(
        pqxx::connection& connection,
        const boost::optional<versioned_key> id =boost::optional<versioned_key>());

    void erase_internal(pqxx::connection& connection,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

public:
    std::vector<dogen::all_primitives::a_class> load(
        pqxx::connection& connection,
        const boost::optional<versioned_key> id =boost::optional<versioned_key>());

    void save(
        pqxx::connection& connection,
        std::vector<dogen::all_primitives::a_class> values);

    void erase(pqxx::connection& connection);
    void erase(pqxx::connection& connection, versioned_key id);
};

} }
#endif
