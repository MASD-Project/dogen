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
#include <set>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.physical/types/helpers/building_error.hpp"
#include "dogen.physical/types/helpers/template_instantiation_domains_factory.hpp"

namespace {

const std::string transform_id("logical.transforms.parsing_transform");

using namespace dogen::utility::log;
auto lg(logger_factory("physical.template_instantiation_domains_factory"));

const std::string backend_postfix(".backend");
const std::string facet_postfix(".facet");
const std::string archetype_postfix(".archetype");
const std::string duplicate_value("Value was already inserted: ");

}

namespace dogen::physical::helpers {

std::unordered_map<std::string, std::vector<std::string>>
template_instantiation_domains_factory::
make(const std::list<entities::name>& ns) {
    BOOST_LOG_SEV(lg, debug) << "Building instantiation domains.";

    /*
     * First we gather all of the information in sorted form, and
     * filter out any duplicate backends of facets. We are however not
     * expecting duplicate archetypes, so throw if those show up.
     */
    std::unordered_map<std::string, std::set<std::string>> sorted;
    const auto ensure_inserted(
        [&](const std::string& k, const std::string& v) {
            bool inserted(sorted[k].insert(v).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_value << v;
                BOOST_THROW_EXCEPTION(building_error(duplicate_value + v));
            }
        });

    const auto masd_kernel("masd");
    for (const auto n: ns) {
        const auto& l(n.location());

        /*
         * Kernel
         */
        sorted[masd_kernel].insert(l.backend());
        sorted[masd_kernel].insert(l.facet());
        sorted[masd_kernel].insert(l.archetype());

        sorted[masd_kernel + backend_postfix].insert(l.backend());
        sorted[masd_kernel + facet_postfix].insert(l.facet());
        ensure_inserted(masd_kernel + archetype_postfix, l.archetype());

        /*
         * Backend
         */
        sorted[l.backend()].insert(l.facet());
        ensure_inserted(l.backend(), l.archetype());

        sorted[l.backend() + facet_postfix].insert(l.facet());
        sorted[l.backend() + archetype_postfix].insert(l.archetype());

        /*
         * Facet
         */
        ensure_inserted(l.facet(), l.archetype());
        ensure_inserted(l.facet() + archetype_postfix, l.archetype());
    }

    /*
     * Now reformat the gathered data into the required shape.
     */
    std::unordered_map<std::string, std::vector<std::string>> r;
    for (const auto& pair : sorted) {
        const auto& k(pair.first);
        const auto& v(pair.second);
        auto& vec(r[k]);
        vec.reserve(v.size());
        for (const auto& s : v)
            vec.push_back(s);
    }

    BOOST_LOG_SEV(lg, debug) << "Built instantiation domains: " << r;

    return r;
}

}
