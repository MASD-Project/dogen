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
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/io/formattables/integrated_facets_repository_io.hpp"
#include "dogen/cpp/types/formattables/integrated_facets_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.integrated_facets_repository_factory"));

}

namespace dogen {
namespace cpp {
namespace formattables {

integrated_facets_repository
integrated_facets_repository_factory::make(const dynamic::repository& rp,
    const dynamic::object& root_object,
    const formatters::container& fc) {

    const dynamic::field_selector fs(root_object);
    const dynamic::repository_selector s(rp);
    const auto& ifct(traits::integrated_facet());
    integrated_facets_repository r;

    // the logic here is slightly convoluted: for every formatter,
    // get its facet name. Then look for the integrated facets for
    // that facet. Then associate those integrated facets with the
    // formatter name - not the facet name.
    for (const auto& f : fc.all_external_formatters()) {
        const auto oh(f->ownership_hierarchy());
        const auto& fctn(oh.facet_name());
        const auto iffd(s.try_select_field_by_name(fctn, ifct));

        if (!iffd)
            continue;

        if (fs.has_field(*iffd)) {
            const auto fcts(fs.get_text_collection_content(*iffd));
            std::unordered_set<std::string> set;
            for (const auto f : fcts)
                set.insert(f);

            const auto& fn(oh.formatter_name());
            r.integrated_facets_by_formatter_name()[fn] = set;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Integrated facets repository: " << r;
    return r;
}

} } }
