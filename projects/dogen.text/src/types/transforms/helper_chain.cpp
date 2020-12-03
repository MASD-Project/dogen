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
#include <boost/make_shared.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.logical/io/entities/helper_properties_io.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/registrar.hpp"
#include "dogen.text/types/transforms/helper_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.transforms.helper_chain"));

const std::string no_helpers_for_family("No helpers found for family: ");
const std::string helpless_family("No registered helpers found for family: ");

}

namespace dogen::text::transforms {

using logical::entities::element;
using physical::entities::artefact;

std::shared_ptr<text::transforms::registrar> helper_chain::registrar_;
physical::entities::model* helper_chain::model_;

text::transforms::registrar& helper_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<text::transforms::registrar>();

    return *registrar_;
}

std::list<std::shared_ptr<helper_transform>> helper_chain::
get_helpers(const artefact& a,
    const logical::entities::helper_properties& hp) const {
    /*
     * A family must have at least one helper registered. This is a
     * good way to detect spurious families in data files.
     */
    const auto fam(hp.current().family());
    const auto& helpers(registrar().helper_repository().helpers_by_family());
    const auto i(helpers.find(fam));
    if (i == helpers.end()) {
        BOOST_LOG_SEV(lg, error) << no_helpers_for_family << fam;
        BOOST_THROW_EXCEPTION(transformation_error(no_helpers_for_family + fam));
    }
    BOOST_LOG_SEV(lg, debug) << "Found helpers for family: " << fam;

    /*
     * Not all formatters need help, so its fine not to have a
     * helper registered against a particular formatter.
     */
    const auto pmid(a.meta_name().id());
    const auto j(i->second.find(pmid));
    if (j != i->second.end()) {
        BOOST_LOG_SEV(lg, debug) << "Found helpers for transform: " << pmid;
        return j->second;
    }

    BOOST_LOG_SEV(lg, debug) << "Could not find helpers for transform:" << pmid;
    return std::list<std::shared_ptr<transforms::helper_transform>>();
}

void helper_chain::apply(std::ostream& os, const logical::entities::model& m,
    const element& e, const artefact& a) {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Generating helper methods for element: "
                             << id.value();

    if (e.helper_properties().empty())
        BOOST_LOG_SEV(lg, debug) << "No helper methods found.";

    for (const auto& hlp_props : e.helper_properties()) {
        BOOST_LOG_SEV(lg, debug) << "Helper configuration: " << hlp_props;
        const auto helpers(get_helpers(a, hlp_props));

        /*
         * Check to see if the helper is enabled, given the system's
         * current configuration. If enabled, format it.
         */
        for (const auto& hlp : helpers) {
            const auto id(hlp->id());
            if (!hlp->is_enabled(*model_, e, a, hlp_props)) {
                BOOST_LOG_SEV(lg, debug) << "Helper is not enabled." << id;
                continue;
            }

            BOOST_LOG_SEV(lg, debug) << "Transforming with helper: " << id;
            hlp->apply(os, m, hlp_props);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished generating helper methods.";
}

}
