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
#include <boost/test/unit_test.hpp>
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/schema-catalog.hxx>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/tds_test_good.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/database/types/all.hpp"
#include "dogen/database/io/all_io.hpp"
#include "dogen/database/test_data/all_td.hpp"
#include "dogen/database/odb/no_keys-odb.hpp"

using namespace odb::core;

namespace  {

const std::string test_suite("database_spec");
const std::string test_module("database");

}

BOOST_AUTO_TEST_SUITE(database)

BOOST_AUTO_TEST_CASE(inserting_no_keys_instances_results_in_expected_rows_in_table) {
    SETUP_TEST_LOG_SOURCE("inserting_no_keys_instances_results_in_expected_rows_in_table");

    std::unique_ptr<odb::database> db (
        new odb::pgsql::database (
            "build",
            "build",
            "sanzala",
            "localhost"
            ));

    {
        odb::transaction t(db->begin());
        odb::schema_catalog::create_schema(*db);
        BOOST_LOG_SEV(lg, debug) << "Generating schema.";

    }

    {
        odb::transaction t(db->begin());
        const auto deleted_rows(db->erase_query<dogen::database::no_keys>());
        BOOST_LOG_SEV(lg, debug) << "Deleted existing rows. Total: "
                                 << deleted_rows;
        t.commit();
    }

    std::vector<dogen::database::no_keys> v;
    const unsigned int how_many(5);
    v.resize(how_many);
    {
        odb::transaction t(db->begin());
        dogen::database::no_keys_generator sequence;
        for (unsigned int i(0); i < how_many; ++i) {
            v.push_back(sequence());
            BOOST_LOG_SEV(lg, debug) << "Created: " << v.back();
            db->persist(v.back());
            BOOST_LOG_SEV(lg, debug) << "Object has been persisted";
        }
        t.commit();
    }

    {
        transaction t(db->begin());
        typedef odb::query<dogen::database::no_keys> query;
        typedef odb::result<dogen::database::no_keys> result;

        result r(db->query<dogen::database::no_keys>());
        for (auto i(r.begin ()); i != r.end (); ++i) {
            BOOST_LOG_SEV(lg, debug) << "Actual: " << *i;
            bool found(false);
            for (const auto e : v) {
                if (e == *i) {
                    found = true;
                    BOOST_LOG_SEV(lg, debug) << "Found actual.";
                    continue;
                }
            }
            BOOST_CHECK(found);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
