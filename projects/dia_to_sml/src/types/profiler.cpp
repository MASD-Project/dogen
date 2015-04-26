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
#include "dogen/utility/string/splitter.hpp"
#include "dogen/dia_to_sml/io/profile_io.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"
#include "dogen/dia_to_sml/types/profiler.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.profiler"));

const std::string concept("concept");
const std::string enumeration("enumeration");
const std::string exception("exception");
const std::string value_object("value object");
const std::string service("service");
const std::string factory("factory");
const std::string repository("repository");
const std::string nongeneratable("nongeneratable");
const std::string visitable("visitable");
const std::string immutable("immutable");
const std::string entity("entity");
const std::string keyed_entity("keyed entity");
const std::string fluent("fluent");
const std::string versioned("versioned");
const std::string aggregate_root("aggregate root");

}

namespace dogen {
namespace dia_to_sml {

void profiler::
process_object_type(profile& o, const object_types ot) const {
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
process_stereotype(profile& o, const std::string& s) const {
    using utility::string::splitter;
    const auto stereotypes(splitter::split_csv(s));

    for (const auto& stereotype : stereotypes) {
        if (stereotype == enumeration)
            o.is_enumeration(true);
        else if (stereotype == exception)
            o.is_exception(true);
        else if (stereotype == entity)
            o.is_entity(true);
        else if (stereotype == value_object)
            o.is_value_object(true);
        else if (stereotype == service)
            o.is_service(true);
        else if (stereotype == nongeneratable)
            o.is_non_generatable(true);
        else if (stereotype == visitable)
            o.is_visitable(true);
        else if (stereotype == immutable)
            o.is_immutable(true);
        else if (stereotype == keyed_entity)
            o.is_keyed_entity(true);
        else if (stereotype == fluent)
            o.is_fluent(true);
        else if (stereotype == versioned)
            o.is_versioned(true);
        else if (stereotype == aggregate_root)
            o.is_aggregate_root(true);
        else if (stereotype == concept)
            o.is_concept(true);
        else if (stereotype == factory)
            o.is_factory(true);
        else if (stereotype == repository)
            o.is_repository(true);
        else
            o.unknown_stereotypes().push_back(stereotype);
    }
}

profile profiler::generate(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Generating profile for: " << o.id();

    profile r;
    process_object_type(r, o.object_type());
    process_stereotype(r, o.stereotype());

    BOOST_LOG_SEV(lg, debug) << "Generated profile for "  << o.id()
                             << ". result: " << r;
    return r;
}

} }
