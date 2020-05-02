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
#include "dogen.logical/io/entities/orm/letter_case_io.hpp"
#include "dogen.logical/io/entities/orm/database_system_io.hpp"
#include "dogen.m2t.cpp/types/formattables/artefact_properties.hpp"
#include "dogen.m2t.cpp/types/formattables/adaptation_error.hpp"
#include "dogen.m2t.cpp/types/transforms/model_to_text_transform.hpp"
#include "dogen.m2t.cpp/types/formattables/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.cpp.formattables.adapter"));

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

namespace dogen::m2t::cpp::formattables {

std::string
adapter::to_odb_database(const logical::entities::orm::database_system ds) {
    using logical::entities::orm::database_system;

    switch (ds) {
    case database_system::mysql: return mysql;
    case database_system::postgresql: return postgresql;
    case database_system::oracle: return oracle;
    case database_system::sql_server: return sql_server;
    case database_system::sqlite: return sqlite;
    default: {
        const auto s(boost::lexical_cast<std::string>(ds));
        BOOST_LOG_SEV(lg, error) << invalid_daatabase_system << s;
        BOOST_THROW_EXCEPTION(adaptation_error(invalid_daatabase_system + s));
    } }
}

std::string adapter::
to_odb_sql_name_case(const logical::entities::orm::letter_case lc) const {
    using logical::entities::orm::letter_case;

    switch (lc) {
    case letter_case::upper_case: return upper_case;
    case letter_case::lower_case: return lower_case;
    default: {
        const auto s(boost::lexical_cast<std::string>(lc));
        BOOST_LOG_SEV(lg, error) << invalid_case << s;
        BOOST_THROW_EXCEPTION(adaptation_error(invalid_case + s));
    } }
}

std::list<std::string> adapter::
make_databases(const logical::entities::orm::model_properties& omp) const {
    std::list<std::string> r;

    if (omp.database_systems().size() > 1)
        r.push_back("common");

    for (const auto ds : omp.database_systems())
        r.push_back(to_odb_database(ds));

    return r;
}

model adapter::adapt(const transforms::repository& frp,
    const m2t::entities::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Adapting logical model to formattables."
                             << " Elements in model: " << m.elements().size();

    model r;
    r.name(m.name());

    const auto& fp(m.global_enablement_properties().facet_properties());
    for (const auto& pair : fp) {
        facet_properties fp;
        fp.enabled(pair.second.enabled());
        r.facet_properties().insert(std::make_pair(pair.first, fp));
    }

    if (m.orm_properties()) {
        const auto op(*m.orm_properties());
        r.odb_databases(make_databases(op));
        if (op.letter_case())
            r.odb_sql_name_case(to_odb_sql_name_case(*op.letter_case()));
    }

    for (const auto& ea : m.elements()) {
        auto ptr(ea.element());
        const auto& e(*ptr);
        const auto id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        /*
         * We need to check to see if we've already inserted an
         * element due to the segmentation of elements - we may need
         * to process the master element and one or more extensions.
         */
        auto i(r.formattables().find(id));
        if (i == r.formattables().end()) {
            formattable fbl;
            const auto pair(std::make_pair(id, fbl));
            const auto ret(r.formattables().insert(pair));
            i = ret.first;
            BOOST_LOG_SEV(lg, debug) << "Inserted element: " << id;
        } else
            BOOST_LOG_SEV(lg, debug) << "Element already inserted. ";

        /*
         * Setup the master segment depending on the extension flag.
         */
        auto& fbl(i->second);
        if (fbl.element()) {
            BOOST_LOG_SEV(lg, error) << duplicate_master << id;
            BOOST_THROW_EXCEPTION(adaptation_error(duplicate_master + id));
        }
        fbl.element(ea.element());
        fbl.artefacts(ea.artefacts());

        /*
         * Check to see if the element has any formatters. Some
         * elements such as object templates do not have formatters at
         * present.
         */
        const auto mt(e.meta_name().qualified().dot());
        const auto j(frp.stock_artefact_formatters_by_meta_name().find(mt));
        if (j == frp.stock_artefact_formatters_by_meta_name().end()) {
            BOOST_LOG_SEV(lg, debug) << "Element has no formatters: " << id;
            continue;
        }
        BOOST_LOG_SEV(lg, debug) << "Element has formatters " << id;

        /*
         * Perform the artefact expansion by looking at all the
         * archetypes available via the formatters. Note that we check
         * for duplicates on insertion because of the element
         * segmentation scenario. Its there just to ensure we don't
         * have a formatter processing both a master and an extension.
         */
        auto& art_props(fbl.element_properties().artefact_properties());
        for (const auto& fmt : j->second) {
            const auto n(fmt->archetype().meta_name());
            const auto arch(n.qualified());
            const auto pair(std::make_pair(arch, artefact_properties()));
            const auto inserted(art_props.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_archetype << arch;
                BOOST_THROW_EXCEPTION(
                    adaptation_error(duplicate_archetype + arch));
            }

            BOOST_LOG_SEV(lg, debug) << "Added formatter: " << arch
                                     << " to element: " << id;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished adapting logical to formattables."
                             << "Size: " << r.formattables().size();
    return r;
}

}
