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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/profiling_error.hpp"
#include "dogen/dia_to_sml/types/identifier_parser.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"
#include "dogen/dia_to_sml/types/profiler.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.profiler"));

const std::string invalid_stereotype("Invalid value for stereotype: ");

const std::string enumeration("enumeration");
const std::string exception("exception");
const std::string entity("entity");
const std::string value("value");
const std::string service("service");
const std::string nongeneratable("nongeneratable");

}

namespace dogen {
namespace dia_to_sml {

void profiler::
process_object_type(object_profile& o, const object_types ot) const {
    if (ot == object_types::uml_large_package)
        o.is_uml_large_package(true);
    else if (ot == object_types::uml_class)
        o.is_uml_class(true);
    else if (ot == object_types::uml_generalization)
        o.is_uml_generalization(true);
    else if (ot == object_types::uml_association)
        o.is_uml_association(true);
    else if (ot == object_types::uml_note)
        o.is_uml_note(true);
    else if (ot == object_types::uml_message)
        o.is_uml_message(true);
    else if (ot == object_types::uml_realization)
        o.is_uml_realization(true);
}

void profiler::
process_stereotype(object_profile& o, const std::string& s) const {
    const auto stereotypes(identifier_parser::parse_csv_string(s));

    for (const auto stereotype : stereotypes) {
        if (s == enumeration)
            o.is_enumeration(true);
        else if (s == exception)
            o.is_exception(true);
        else if (s == entity)
            o.is_entity(true);
        else if (s == value)
            o.is_value(true);
        else if (s == service)
            o.is_service(true);
        else if (s == nongeneratable)
            o.is_non_generatable(true);
        else {
            BOOST_LOG_SEV(lg, error) << invalid_stereotype << s;
            BOOST_THROW_EXCEPTION(profiling_error(invalid_stereotype + s));
        }
    }
}

object_profile profiler::profile(const processed_object& o) {
    object_profile r;
    process_object_type(r, o.object_type());
    process_stereotype(r, o.stereotype());
    return r;
}

} }
