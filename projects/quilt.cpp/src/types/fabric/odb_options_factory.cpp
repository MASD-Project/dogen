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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/io/orm_database_systems_io.hpp"
#include "dogen/yarn/types/orm_database_systems.hpp"
#include "dogen/quilt.cpp/types/fabric/building_error.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.fabric.odb_options_factory"));

const std::string odb_options_name("options.odb");
const std::string mysql("mysql");
const std::string postgresql("pgsql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqllite("sqllite");

const std::string invalid_daatabase_system(
    "Database system is invalid or unsupported: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

std::list<std::string> odb_options_factory::
make_databases(const yarn::orm_model_configuration& cfg) const {
    std::list<std::string> r;
    using yarn::orm_database_systems;
    for (const auto ds : cfg.database_systems()) {
        switch (ds) {
        case orm_database_systems::mysql: r.push_back(mysql); break;
        case orm_database_systems::postgresql: r.push_back(postgresql); break;
        case orm_database_systems::oracle: r.push_back(oracle); break;
        case orm_database_systems::sql_server: r.push_back(sql_server); break;
        case orm_database_systems::sqllite: r.push_back(sqllite); break;
        default: {
            const auto s(boost::lexical_cast<std::string>(ds));
            BOOST_LOG_SEV(lg, error) << invalid_daatabase_system << s;
            BOOST_THROW_EXCEPTION(building_error(invalid_daatabase_system + s));
        } }
    }

    return r;
}

boost::shared_ptr<yarn::element>
odb_options_factory::make(const yarn::intermediate_model& im) const {

    BOOST_LOG_SEV(lg, debug) << "Generating ODB Options.";

    yarn::name_factory nf;
    const auto n(nf.build_element_in_model(im.name(), odb_options_name));
    auto r(boost::make_shared<odb_options>());
    r->name(n);
    r->origin_type(im.origin_type());

    if (im.orm_configuration()) {
        const auto cfg(*im.orm_configuration());
        r->databases(make_databases(cfg));
        r->letter_case(cfg.letter_case());
    }

    BOOST_LOG_SEV(lg, debug) << "Generated ODB Options.";

    return r;
}

} } } }
