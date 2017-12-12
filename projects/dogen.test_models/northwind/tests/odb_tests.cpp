/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/schema-catalog.hxx>
#include "dogen.utility/test/asserter.hpp"
#include "dogen.utility/io/vector_io.hpp"
#include "dogen.utility/test_data/validating_resolver.hpp"
#include "dogen.utility/test_data/tds_test_good.hpp"
#include "dogen.utility/test/logging.hpp"
#include "dogen/test_models/northwind/types/all.hpp"
#include "dogen/test_models/northwind/io/all_io.hpp"
#include "dogen/test_models/northwind/test_data/all_td.hpp"
// #include "dogen/test_models/northwind/odb/no_keys-odb.hxx"
// #include "dogen/test_models/northwind/odb/no_keys_2-odb.hxx"
// #include "dogen/test_models/northwind/odb/primary_key-odb.hxx"
// #include "dogen/test_models/northwind/odb/primary_key_2-odb.hxx"
// #include "dogen/test_models/northwind/odb/foreign_key-odb.hxx"

using namespace odb::core;

namespace  {

const std::string test_suite("odb_tests");
const std::string test_module("northwind");

// odb::database* create_db() {
//     return new odb::pgsql::database ("build", "", "musseque", "localhost");
// }

template<typename T>
long long delete_rows(odb::database& db) {
    odb::transaction t(db.begin());
    const auto r(db.erase_query<T>());
    t.commit();
    return r;
}

template<typename Sequence>
std::vector<typename Sequence::result_type>
generate(const unsigned int how_many) {
    std::vector<typename Sequence::result_type> r;
    r.reserve(how_many);
    Sequence sequence;
    std::generate_n(std::back_inserter(r), how_many, sequence);
    return r;
}

template<typename T>
void persist(odb::database& db, const std::vector<T>& v) {
    odb::transaction t(db.begin());
    for (const auto e : v)
        db.persist(e);
    t.commit();
}

}

BOOST_AUTO_TEST_SUITE(database_tests)

BOOST_AUTO_TEST_CASE(inserting_no_keys_instances_results_in_expected_rows_in_table) {
    SETUP_TEST_LOG_SOURCE("inserting_no_keys_instances_results_in_expected_rows_in_table");
/*
    std::unique_ptr<odb::database> db(create_db());
    const auto del_rows(delete_rows<dogen::test_models::northwind::no_keys>(*db));
    BOOST_LOG_SEV(lg, debug) << "Deleted existing rows. Total: " << del_rows;

    const unsigned int how_many(5);
    const auto v(generate<dogen::test_models::northwind::no_keys_generator>(how_many));
    persist(*db, v);
    BOOST_LOG_SEV(lg, debug) << "Persisted: " << v;

    {
        transaction t(db->begin());
        typedef odb::result<dogen::test_models::northwind::no_keys> result;

        result r(db->query<dogen::test_models::northwind::no_keys>());
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
*/
}

BOOST_AUTO_TEST_CASE(inserting_no_keys_2_instances_results_in_expected_rows_in_table) {
    SETUP_TEST_LOG_SOURCE("inserting_no_keys_2_instances_results_in_expected_rows_in_table");
/*
    std::unique_ptr<odb::database> db(create_db());
    const auto del_rows(delete_rows<dogen::test_models::northwind::no_keys_2>(*db));
    BOOST_LOG_SEV(lg, debug) << "Deleted existing rows. Total: " << del_rows;

    const unsigned int how_many(5);
    const auto v(generate<dogen::test_models::northwind::no_keys_2_generator>(how_many));
    persist(*db, v);
    BOOST_LOG_SEV(lg, debug) << "Persisted: " << v;

    {
        transaction t(db->begin());
        typedef odb::result<dogen::test_models::northwind::no_keys_2> result;

        result r(db->query<dogen::test_models::northwind::no_keys_2>());
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
*/
}

BOOST_AUTO_TEST_CASE(inserting_primary_key_objects_results_in_unique_rows) {
    SETUP_TEST_LOG_SOURCE("inserting_primary_key_objects_results_in_unique_rows");
/*
    std::unique_ptr<odb::database> db(create_db());
    const auto del_rows(delete_rows<dogen::test_models::northwind::primary_key>(*db));
    BOOST_LOG_SEV(lg, debug) << "Deleted existing rows. Total: " << del_rows;

    const unsigned int how_many(5);
    const auto v(generate<dogen::test_models::northwind::primary_key_generator>(how_many));
    persist(*db, v);
    BOOST_LOG_SEV(lg, debug) << "Persisted: " << v;

    {
        transaction t(db->begin());
        const auto e(v.front());
        const auto a(db->load<dogen::test_models::northwind::primary_key>(e.prop_0()));
        BOOST_LOG_SEV(lg, debug) << "Expected: " << e;
        BOOST_LOG_SEV(lg, debug) << "Actual: " << *a;
        BOOST_CHECK(*a == e);
        t.commit();
    }

    {
        transaction t(db->begin());
        auto e(v.back());
        auto a(db->load<dogen::test_models::northwind::primary_key>(e.prop_0()));
        a->prop_1("some update");
        db->update(*a);
        t.commit();
    }

    {
        transaction t(db->begin());
        auto e(v.back());
        e.prop_1("some update");
        const auto a(db->load<dogen::test_models::northwind::primary_key>(e.prop_0()));
        BOOST_LOG_SEV(lg, debug) << "Expected: " << e;
        BOOST_LOG_SEV(lg, debug) << "Actual: " << *a;
        BOOST_CHECK(*a == e);
        t.commit();
    }
*/
}

BOOST_AUTO_TEST_CASE(inserting_foreign_key_objects_requires_other_side_to_exist) {
    SETUP_TEST_LOG_SOURCE("inserting_foreign_key_objects_requires_other_side_to_exist");
/*
    std::unique_ptr<odb::database> db(create_db());
    auto del_rows(delete_rows<dogen::test_models::northwind::foreign_key>(*db));
    BOOST_LOG_SEV(lg, debug) << "Deleted rows in foreign_key. Total: "
                             << del_rows;

    del_rows = delete_rows<dogen::test_models::northwind::primary_key_2>(*db);
    BOOST_LOG_SEV(lg, debug) << "Deleted rows in primary_key_2. Total: "
                             << del_rows;

    const unsigned int how_many(5);
    const auto v(generate<dogen::test_models::northwind::primary_key_2_generator>(how_many));
    persist(*db, v);
    BOOST_LOG_SEV(lg, debug) << "Persisted: " << v;

    {
        odb::transaction t(db->begin());
        dogen::test_models::northwind::foreign_key fk;
        fk.prop_0(15);
        boost::shared_ptr<dogen::test_models::northwind::primary_key_2>
            sp(new dogen::test_models::northwind::primary_key_2(v.back()));
        fk.prop_1(sp);
        db->persist(fk);
        BOOST_LOG_SEV(lg, debug) << "Object has been persisted: " << fk;
        t.commit();
    }

    {
        transaction t(db->begin());
        typedef odb::result<dogen::test_models::northwind::foreign_key> result;

        result r(db->query<dogen::test_models::northwind::foreign_key>());
        for (auto i(r.begin ()); i != r.end (); ++i) {
            BOOST_LOG_SEV(lg, debug) << "Actual: " << *i;
            bool found(false);
            if (v.back() == *(i->prop_1())) {
                found = true;
                BOOST_LOG_SEV(lg, debug) << "Found actual.";
            }
            BOOST_CHECK(found);
        }
    }
*/
}

BOOST_AUTO_TEST_SUITE_END()
