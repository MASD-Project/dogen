/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASS_IN_A_PACKAGE_DATABASE_PACKAGE1_FIRST_CLASS_DB_HPP
#define DOGEN_CLASS_IN_A_PACKAGE_DATABASE_PACKAGE1_FIRST_CLASS_DB_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include <pqxx/connection.hxx>
#include <vector>
#include "dogen/class_in_a_package/domain/package1/first_class.hpp"

namespace dogen {
namespace class_in_a_package {
namespace package1 {

class first_class_data_exchanger {
public:
    first_class_data_exchanger() = default;
    first_class_data_exchanger(const first_class_data_exchanger&) = delete;
    ~first_class_data_exchanger() = default;
    first_class_data_exchanger(first_class_data_exchanger&&) = delete;

private:
    std::string format_sql(const std::string& format_str,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

    std::vector<dogen::class_in_a_package::package1::first_class> load_internal(
        pqxx::connection& connection,
        const boost::optional<versioned_key> id =boost::optional<versioned_key>());

    void erase_internal(pqxx::connection& connection,
        const boost::optional<versioned_key> id = boost::optional<versioned_key>());

public:
    std::vector<dogen::class_in_a_package::package1::first_class> load(
        pqxx::connection& connection,
        const boost::optional<versioned_key> id =boost::optional<versioned_key>());

    void save(
        pqxx::connection& connection,
        std::vector<dogen::class_in_a_package::package1::first_class> values);

    void erase(pqxx::connection& connection);
    void erase(pqxx::connection& connection, versioned_key id);
};

} } }
#endif
