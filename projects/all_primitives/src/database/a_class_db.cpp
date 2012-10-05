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
#include <boost/format.hpp>
#include <pqxx/result.hxx>
#include <pqxx/transaction.hxx>
#include "dogen/all_primitives/database/a_class_db.hpp"

namespace {

enum fields {
    bool_property_field = 0,
    char_property_field = 1,
    uchar_property_field = 2,
    int_property_field = 3,
    uint_property_field = 4,
    long_property_field = 5,
    ulong_property_field = 6,
    long_long_property_field = 7,
    ulong_long_property_field = 8,
    short_property_field = 9,
    ushort_property_field = 10,
    versioned_key_field = 11
};

const std::string load_name("statement_all_primitives_a_class_load");
const std::string load_id_name("statement_all_primitives_a_class_load_id");
const std::string load_work_name("work_all_primitives_a_class_load");
const std::string load_sql("select * from all_primitives_a_class_load($0, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);");

const std::string erase_name("statement_all_primitives_a_class_erase");
const std::string erase_id_name("statement_all_primitives_a_class_erase_id");
const std::string erase_work_name("work_all_primitives_a_class_erase");
const std::string erase_sql("select * from all_primitives_a_class_erase($0, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);");

const std::string save_name("statement_all_primitives_a_class_save");
const std::string save_work_name("work_all_primitives_a_class_save");
const std::string save_sql("select all_primitives_a_class_save($0, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);");

}

namespace dogen {
namespace all_primitives {

std::string a_class_data_exchanger::
format_sql(const std::string& format_str, const boost::optional<versioned_key> id) {
    return (boost::format(format_str) % (id ? "$1" : "null")).str();
}



} }
