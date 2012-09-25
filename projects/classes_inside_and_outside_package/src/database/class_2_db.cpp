/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/format.hpp>
#include <pqxx/result.hxx>
#include <pqxx/transaction.hxx>
#include "dogen/classes_inside_and_outside_package/database/class_2_db.hpp"

namespace {

enum fields {
    versioned_key_field = 0
};

const std::string load_name("statement_classes_inside_and_outside_package_class_2_load");
const std::string load_id_name("statement_classes_inside_and_outside_package_class_2_load_id");
const std::string load_work_name("work_classes_inside_and_outside_package_class_2_load");
const std::string load_sql("select * from classes_inside_and_outside_package_class_2_load($0);");

const std::string erase_name("statement_classes_inside_and_outside_package_class_2_erase");
const std::string erase_id_name("statement_classes_inside_and_outside_package_class_2_erase_id");
const std::string erase_work_name("work_classes_inside_and_outside_package_class_2_erase");
const std::string erase_sql("select * from classes_inside_and_outside_package_class_2_erase($0);");

const std::string save_name("statement_classes_inside_and_outside_package_class_2_save");
const std::string save_work_name("work_classes_inside_and_outside_package_class_2_save");
const std::string save_sql("select classes_inside_and_outside_package_class_2_save($0);");

}

namespace dogen {
namespace classes_inside_and_outside_package {

std::string class_2_data_exchanger::
format_sql(const std::string& format_str, const boost::optional<versioned_key> id) {
    return (boost::format(format_str) % (id ? "$1" : "null")).str();
}



} }
