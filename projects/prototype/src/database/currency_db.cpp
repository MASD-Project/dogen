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
#include <boost/format.hpp>
#include <pqxx/result.hxx>
#include <pqxx/transaction.hxx>
#include "dogen/prototype/domain/versioned_key.hpp"
#include "dogen/prototype/database/currency_db.hpp"

namespace {

enum fields {
    // id_field = 0,
    // version_field = 1,
    // numeric_code_field = 2,
    // name_field = 3,
    // alpha_code_field = 4,
    // decimal_places_field = 5,

    // FIXME: just to get it working without db changes
    id_field = 0,
    version_field = 6,
    numeric_code_field = 0,
    name_field = 1,
    alpha_code_field = 2,
    decimal_places_field = 3
};

const std::string load_name("statement_currency_data_exchange_load");
const std::string load_id_name("statement_currency_data_exchange_load_id");
const std::string load_work_name("work_currency_data_exchange_load");
const std::string load_sql("select * from kitanda.currency_load(%s);");

const std::string delete_name("statement_currency_data_exchange_delete");
const std::string delete_id_name("statement_currency_data_exchange_delete_id");
const std::string delete_work_name("work_currency_data_exchange_delete");
const std::string delete_sql("select * from kitanda.currency_delete(%s);");

const std::string save_name("statement_currency_data_exchange_save");
const std::string save_work_name("work_currency_data_exchange_save");
const std::string save_sql("select kitanda.currency_save($1, $2, $3, $4, $5);");

}

namespace dogen {
namespace prototype {

std::string currency_data_exchanger::
format_sql(const std::string& format_str, const boost::optional<versioned_key> id) {
    return (boost::format(format_str) % (id ? "$1" : "null")).str();
}

std::vector<dogen::prototype::currency>
currency_data_exchanger::load_internal(pqxx::connection& connection,
    const boost::optional<versioned_key> vk) {
    const std::string name(vk ? load_id_name : load_name);
    const std::string sql(format_sql(load_sql, vk));
    connection.prepare(name, sql);

    pqxx::work work(connection, load_work_name);
    pqxx::result result;
    if (vk)
        result = work.prepared(name)(vk->id()).exec();
    else
        result = work.prepared(name).exec();

    std::vector<dogen::prototype::currency> currencies;
    currencies.reserve(result.size());
    for (pqxx::result::const_iterator i(result.begin());
         i != result.end();
         ++i) {

        const dogen::prototype::versioned_key vk2(
            i[id_field].as<unsigned int>(),
            i[version_field].as<unsigned int>());

        currencies.push_back(
            dogen::prototype::currency(i[name_field].as<std::string>(),
                i[alpha_code_field].as<std::string>(),
                i[decimal_places_field].as<unsigned int>(),
                i[numeric_code_field].as<unsigned int>(),
                vk2));
    }
    return(currencies);
}

void currency_data_exchanger::erase_internal(pqxx::connection& connection,
    const boost::optional<versioned_key> vk) {
    const std::string name(vk ? delete_id_name : delete_name);
    const std::string sql(format_sql(delete_sql, vk));

    pqxx::work work(connection, load_work_name);
    connection.prepare(name, sql);

    if (vk)
        work.prepared(name)(vk->id()).exec();
    else
        work.prepared(name).exec();

    work.commit();
}

std::vector<dogen::prototype::currency> currency_data_exchanger::
load(pqxx::connection& connection) {
    return load_internal(connection);
}

std::vector<dogen::prototype::currency> currency_data_exchanger::load(
    pqxx::connection& connection,
    const dogen::prototype::versioned_key& id) {
    return load_internal(connection, boost::optional<versioned_key>(id));
}

void currency_data_exchanger::save(pqxx::connection& connection,
    std::vector<dogen::prototype::currency>& currencies) {
    pqxx::work work(connection, save_work_name);

    const std::string name(save_name);
    const std::string sql(save_sql);
    connection.prepare(name, sql);

    using dogen::prototype::currency;
    for (std::vector<currency>::iterator i(currencies.begin());
         i != currencies.end();
         ++i) {
        currency& currency(*i);

        pqxx::result result(work.prepared(name)
            // FIXME: just to get it working without db changes
            //     (currency.versioned_key().id())
            //     (currency.versioned_key().version())
            //     (currency.numeric_code())
            //     (currency.name())
            //     (currency.alpha_code())
            //     (currency.decimal_places()).exec());
            (currency.numeric_code())
            (currency.name())
            (currency.alpha_code())
            (currency.decimal_places())
            (currency.versioned_key().version()).exec());

        dogen::prototype::versioned_key vk(currency.versioned_key());
        vk.version(vk.version() + 1);
        currency.versioned_key(vk);
    }
    work.commit();
}

void currency_data_exchanger::erase(pqxx::connection& connection) {
    erase_internal(connection);
}

void currency_data_exchanger::erase(pqxx::connection& connection,
    const dogen::prototype::versioned_key& id) {
    erase_internal(connection, id);
}

} }
