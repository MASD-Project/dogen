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
#include "dogen/boost_model/database/class_derived_db.hpp"

namespace {

enum fields {
    prop_0_field = 0,
    versioned_key_field = 1,
    prop_1_field = 2
};

const std::string load_name("statement_boost_model_class_derived_load");
const std::string load_id_name("statement_boost_model_class_derived_load_id");
const std::string load_work_name("work_boost_model_class_derived_load");
const std::string load_sql("select * from boost_model_class_derived_load($0, $1, $2);");

const std::string erase_name("statement_boost_model_class_derived_erase");
const std::string erase_id_name("statement_boost_model_class_derived_erase_id");
const std::string erase_work_name("work_boost_model_class_derived_erase");
const std::string erase_sql("select * from boost_model_class_derived_erase($0, $1, $2);");

const std::string save_name("statement_boost_model_class_derived_save");
const std::string save_work_name("work_boost_model_class_derived_save");
const std::string save_sql("select boost_model_class_derived_save($0, $1, $2);");

}

namespace dogen {
namespace boost_model {

std::string class_derived_data_exchanger::
format_sql(const std::string& format_str, const boost::optional<versioned_key> id) {
    return (boost::format(format_str) % (id ? "$1" : "null")).str();
}



} }
