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
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.logical/io/entities/orm/letter_case_io.hpp"
#include "dogen.logical/io/entities/orm/database_system_io.hpp"
#include "dogen.text.cpp/types/formattables/adaptation_error.hpp"
#include "dogen.text.cpp/types/transforms/model_to_text_transform.hpp"
#include "dogen.text.cpp/types/formattables/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.formattables.adapter"));

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

namespace dogen::text::cpp::formattables {

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

model adapter::adapt(const transforms::repository& frp,
    const text::entities::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Adapting logical model to formattables."
                             << " Logical elements in model: "
                             << m.logical_physical_regions().size();

    model r;
    r.name(m.logical().name());
    if (m.logical().orm_properties()) {
        const auto op(*m.logical().orm_properties());
        if (op.letter_case())
            r.odb_sql_name_case(to_odb_sql_name_case(*op.letter_case()));
    }

    for (const auto& region : m.logical_physical_regions()) {
        auto ptr(region.logical_element());
        const auto& e(*ptr);
        const auto id(e.name().id());
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
            BOOST_THROW_EXCEPTION(
                adaptation_error(duplicate_master + id.value()));
        }
        fbl.element(region.logical_element());
        fbl.artefacts(region.physical_region());

        /*
         * Check to see if the element has any formatters. Some
         * elements such as object templates do not have formatters at
         * present.
         */
        const auto mt(e.meta_name().id());
        const auto j(frp.stock_artefact_formatters_by_meta_name().find(mt));
        if (j == frp.stock_artefact_formatters_by_meta_name().end()) {
            BOOST_LOG_SEV(lg, debug) << "Element has no formatters: " << id;
            continue;
        }
        BOOST_LOG_SEV(lg, debug) << "Element has formatters " << id;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished adapting logical to formattables."
                             << "Size: " << r.formattables().size();
    return r;
}

}
