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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.identification/types/helpers/building_error.hpp"
#include "dogen.identification/types/helpers/physical_id_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("identification.helpers.physical_id_factory"));

const std::string unsupported_technical_space(
    "Invalid or unsupported technical space: ");

}

namespace dogen::identification::helpers {

entities::physical_id physical_id_factory::make(const std::string& logical_id,
    const std::string& physical_meta_id) {
    std::ostringstream ss;
    ss << "<" << logical_id << "><" << physical_meta_id << ">";
    const entities::physical_id r(ss.str());
    return r;
}

entities::physical_id
physical_id_factory::make(const entities::logical_id& logical_id,
    const std::string& physical_meta_id) {
    return make(logical_id.value(), physical_meta_id);
}

entities::physical_id
physical_id_factory::make(const entities::logical_id& logical_id,
    const entities::technical_space& ts) {

    switch(ts) {
    case entities::technical_space::csharp:
        return make(logical_id, "csharp");
    case entities::technical_space::cpp:
        return make(logical_id, "cpp");
    default: {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(
            building_error(unsupported_technical_space + s));
    } }
}

}
