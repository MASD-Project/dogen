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
#include <boost/format.hpp>
#include <pqxx/result.hxx>
#include <pqxx/transaction.hxx>
#include "dogen/classes_in_a_package/database/package_1/class_4_db.hpp"

namespace {

enum fields {
    versioned_key_field = 0
};

const std::string load_name("statement_classes_in_a_package_package_1_class_4_load");
const std::string load_id_name("statement_classes_in_a_package_package_1_class_4_load_id");
const std::string load_work_name("work_classes_in_a_package_package_1_class_4_load");
const std::string load_sql("select * from classes_in_a_package_package_1_class_4_load($0);");

const std::string erase_name("statement_classes_in_a_package_package_1_class_4_erase");
const std::string erase_id_name("statement_classes_in_a_package_package_1_class_4_erase_id");
const std::string erase_work_name("work_classes_in_a_package_package_1_class_4_erase");
const std::string erase_sql("select * from classes_in_a_package_package_1_class_4_erase($0);");

const std::string save_name("statement_classes_in_a_package_package_1_class_4_save");
const std::string save_work_name("work_classes_in_a_package_package_1_class_4_save");
const std::string save_sql("select classes_in_a_package_package_1_class_4_save($0);");

}

namespace dogen {
namespace classes_in_a_package {
namespace package_1 {

std::string class_4_data_exchanger::
format_sql(const std::string& format_str, const boost::optional<versioned_key> id) {
    return (boost::format(format_str) % (id ? "$1" : "null")).str();
}



} } }
