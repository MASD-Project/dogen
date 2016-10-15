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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/yarn.dia/io/profile_io.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/profiler.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.profiler"));

const std::string concept("concept");
const std::string enumeration("enumeration");
const std::string exception("exception");
const std::string nongeneratable("nongeneratable");

}

namespace dogen {
namespace yarn {
namespace dia {

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
        else if (stereotype == concept)
            o.is_concept(true);
        else
            o.unknown_stereotypes().push_back(stereotype);
    }
}

void profiler::post_process(profile& p) const {
    bool nothing_set(!p.is_enumeration() && !p.is_exception() &&
        !p.is_concept());

    if (p.is_uml_class() && nothing_set)
        p.is_object(true);
}

profile profiler::generate(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Generating profile for: " << o.id();

    profile r;
    process_object_type(r, o.object_type());
    process_stereotype(r, o.stereotype());
    post_process(r);

    BOOST_LOG_SEV(lg, debug) << "Generated profile for "  << o.id()
                             << ". result: " << r;
    return r;
}

} } }
