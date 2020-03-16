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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/building_error.hpp"
#include "dogen.physical/types/location_repository_parts_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("physical.location_repository_parts_builder"));

const std::string empty_archetype("Archetype is empty.");
const std::string empty_facet_name("Facet name is empty.");
const std::string empty_model_name("Model name is empty.");
const std::string duplicate_archetype("Duplicate formatter id: ");
const std::string empty_meta_name("Meta-name cannot be empty.");
const std::string empty_intra_backend_segment(
    "Intra-backend segment cannot be empty.");
const std::string empty_family("Family cannot be empty.");

}

namespace dogen::physical {

void location_repository_parts_builder::
validate(const std::string& meta_name, const std::string& family,
    const std::string& intra_backend_segment, const location& al) {

    if(meta_name.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_meta_name;
        BOOST_THROW_EXCEPTION(building_error(empty_meta_name));
    }

    if(family.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_family;
        BOOST_THROW_EXCEPTION(building_error(empty_family));
    }

    if(intra_backend_segment.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_intra_backend_segment;
        BOOST_THROW_EXCEPTION(building_error(empty_intra_backend_segment));
    }

    if (al.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_archetype;
        BOOST_THROW_EXCEPTION(building_error(empty_archetype));
    }

    if (al.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_facet_name;
        BOOST_THROW_EXCEPTION(building_error(empty_facet_name));
    }

    if (al.backend().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_model_name;
        BOOST_THROW_EXCEPTION(building_error(empty_model_name));
    }
}

void location_repository_parts_builder::
add(const std::string& meta_name, const std::string& family,
    const std::string& intra_backend_segment,
    const std::string& canonical_archetype, const location& al) {

    validate(meta_name, family, intra_backend_segment, al);
    parts_.all().push_back(al);

    auto& alg(parts_.by_meta_name()[meta_name]);
    alg.locations().push_back(al);

    auto& albf(parts_.by_family()[family]);
    albf.push_back(al);

    auto& albibs(parts_.by_intra_backend_segment());
    albibs[intra_backend_segment].push_back(al);

    /*
     * If the archetype location points to a canonical archetype,
     * update the canonical archetype mapping.
     */
    auto& cal(alg.canonical_locations());
    if (!canonical_archetype.empty()) {
        const auto arch(al.archetype());
        const auto fct(al.facet());
        const auto& carch(canonical_archetype);
        const auto inserted(cal.insert(std::make_pair(arch, carch)).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_archetype << arch;
            BOOST_THROW_EXCEPTION(building_error(duplicate_archetype + arch));
        }
        BOOST_LOG_SEV(lg, debug) << "Mapped " << carch << " to " << arch;
    }
}

location_repository_parts
location_repository_parts_builder::build() {
    return parts_;
}

}
