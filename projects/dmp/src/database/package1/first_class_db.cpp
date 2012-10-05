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
#include "dogen/dmp/database/package1/first_class_db.hpp"

namespace {

enum fields {
    public_attribute_field = 0,
    private_attribute_field = 1,
    versioned_key_field = 2
};

const std::string load_name("statement_package1_first_class_load");
const std::string load_id_name("statement_package1_first_class_load_id");
const std::string load_work_name("work_package1_first_class_load");
const std::string load_sql("select * from package1_first_class_load($0, $1, $2);");

const std::string erase_name("statement_package1_first_class_erase");
const std::string erase_id_name("statement_package1_first_class_erase_id");
const std::string erase_work_name("work_package1_first_class_erase");
const std::string erase_sql("select * from package1_first_class_erase($0, $1, $2);");

const std::string save_name("statement_package1_first_class_save");
const std::string save_work_name("work_package1_first_class_save");
const std::string save_sql("select package1_first_class_save($0, $1, $2);");

}

namespace dogen {
namespace dmp {
namespace package1 {

std::string first_class_data_exchanger::
format_sql(const std::string& format_str, const boost::optional<versioned_key> id) {
    return (boost::format(format_str) % (id ? "$1" : "null")).str();
}



} } }
