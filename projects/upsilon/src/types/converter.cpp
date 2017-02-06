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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/upsilon/types/conversion_error.hpp"
#include "dogen/upsilon/types/converter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(dogen::utility::log::logger_factory("upsilon.converter"));

const std::string intrinsic_types_integer("integer");
const std::string intrinsic_types_binary("binary");
const std::string intrinsic_types_boolean("boolean");
const std::string intrinsic_types_date("date");
const std::string intrinsic_types_decimal("decimal");
const std::string intrinsic_types_double("double");
const std::string intrinsic_types_guid("guid");
const std::string intrinsic_types_integer64("integer64");
const std::string intrinsic_types_string("string");
const std::string intrinsic_types_utc_time("utctime");
const std::string intrinsic_types_utc_date_time("utcdatetime");

const std::string target_java("java");
const std::string target_cpp("cpp");
const std::string target_cs("cs");

const std::string unsupported_value("Unsupported attribute value: ");

}

namespace dogen {
namespace upsilon {

intrinsic_types converter::to_intrinsic_types(std::string s) const {
    boost::algorithm::to_lower(s);
    if (s == intrinsic_types_integer)
        return intrinsic_types::integer;
    else if (s == intrinsic_types_binary)
        return intrinsic_types::binary;
    else if (s == intrinsic_types_boolean)
        return intrinsic_types::boolean;
    else if (s == intrinsic_types_date)
        return intrinsic_types::date;
    else if (s == intrinsic_types_decimal)
        return intrinsic_types::decimal;
    else if (s == intrinsic_types_double)
        return intrinsic_types::double_x;
    else if (s == intrinsic_types_guid)
        return intrinsic_types::guid;
    else if (s == intrinsic_types_integer64)
        return intrinsic_types::integer64;
    else if (s == intrinsic_types_string)
        return intrinsic_types::string;
    else if (s == intrinsic_types_utc_time)
        return intrinsic_types::utc_time;
    else if (s == intrinsic_types_utc_date_time)
        return intrinsic_types::utc_date_time;
    else {
        BOOST_LOG_SEV(lg, error) << unsupported_value << s;
        BOOST_THROW_EXCEPTION(conversion_error(unsupported_value + s));
    }
}

target_types converter::to_target_types(std::string s) const {
    boost::algorithm::to_lower(s);
    if (s == target_java)
        return target_types::java;
    else if (s == target_cpp)
        return target_types::cpp;
    else if (s == target_cs)
        return target_types::cs;
    else {
        BOOST_LOG_SEV(lg, error) << unsupported_value << s;
        BOOST_THROW_EXCEPTION(conversion_error(unsupported_value + s));
    }
}

} }
