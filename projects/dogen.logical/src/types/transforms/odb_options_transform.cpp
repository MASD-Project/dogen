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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/orm/letter_case_io.hpp"
#include "dogen.logical/io/entities/orm/database_system_io.hpp"
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/odb_options_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.odb_options_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string mysql("mysql");
const std::string postgresql("pgsql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqlite("sqlite");

const std::string upper_case("upper");
const std::string lower_case("lower");

const std::string duplicate_archetype("Duplicate archetype: ");
const std::string duplicate_master(
    "More than one master segment found. Last: ");
const std::string invalid_daatabase_system(
    "Database system is invalid or unsupported: ");
const std::string invalid_case("Letter case is invalid or unsupported: ");

}

namespace dogen::logical::transforms {

using logical::entities::orm::letter_case;
using logical::entities::orm::database_system;

std::string odb_options_transform::to_odb_database(const database_system ds) {
    switch (ds) {
    case database_system::mysql: return mysql;
    case database_system::postgresql: return postgresql;
    case database_system::oracle: return oracle;
    case database_system::sql_server: return sql_server;
    case database_system::sqlite: return sqlite;
    default: {
        const auto s(boost::lexical_cast<std::string>(ds));
        BOOST_LOG_SEV(lg, error) << invalid_daatabase_system << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(invalid_daatabase_system + s));
    } }
}

std::string odb_options_transform::to_odb_sql_name_case(const letter_case lc) {
    switch (lc) {
    case letter_case::upper_case: return upper_case;
    case letter_case::lower_case: return lower_case;
    default: {
        const auto s(boost::lexical_cast<std::string>(lc));
        BOOST_LOG_SEV(lg, error) << invalid_case << s;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_case + s));
    } }
}

std::list<std::string> odb_options_transform::
make_databases(const logical::entities::orm::model_properties& omp) {
    std::list<std::string> r;

    if (omp.database_systems().size() > 1)
        r.push_back("common");

    for (const auto ds : omp.database_systems())
        r.push_back(to_odb_database(ds));

    return r;
}

void odb_options_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "ODB options",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * If the model has no ORM properties then there is nothing to
     * update.
     */
    if (!m.orm_properties())
        return;

    const auto& op(*m.orm_properties());
    for (auto& pair : m.orm_elements().common_odb_options()) {
        auto& coo(*pair.second);
        coo.databases(make_databases(op));
        if (op.letter_case())
            coo.sql_name_case(to_odb_sql_name_case(*op.letter_case()));
    }

    stp.end_transform(m);
}

}
