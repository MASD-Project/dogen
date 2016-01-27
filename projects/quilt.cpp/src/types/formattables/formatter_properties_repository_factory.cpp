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
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directives_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_repository_factory.hpp"
#include "dogen/quilt.cpp/io/formattables/formatter_properties_repository_io.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.formatter_properties_repository_factory"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void formatter_properties_repository_factory::initialise_registrar(
    const formatters::container& c, registrar& rg) const {
    BOOST_LOG_SEV(lg, debug) << "Started registering all providers.";
    for (const auto f : c.all_formatters()) {
        BOOST_LOG_SEV(lg, debug) << "Registered: "
                                 << f->ownership_hierarchy().formatter_name();
        f->register_inclusion_dependencies_provider(rg);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished registering all providers.";
}

inclusion_directives_repository formatter_properties_repository_factory::
create_inclusion_directives_repository(
    const dynamic::repository& srp,
    const formatters::container& fc,
    const path_derivatives_repository& pdrp,
    const yarn::model& m) const {
    inclusion_directives_repository_factory f;
    return f.make(srp, fc, pdrp, m);
}

inclusion_dependencies_repository formatter_properties_repository_factory::
create_inclusion_dependencies_repository(
    const inclusion_dependencies_builder_factory& bf,
    const container& pc, const yarn::model& m) const {
    inclusion_dependencies_repository_factory f;
    return f.make(bf, pc, m);
}

enablement_repository formatter_properties_repository_factory::
create_enablement_repository(const dynamic::repository& srp,
    const dynamic::object& root_object, const formatters::container& fc,
    const yarn::model& m) const {
    enablement_repository_factory f;
    return f.make(srp, root_object, fc, m);
}

std::unordered_map<
    yarn::name,
    formatter_properties_repository_factory::merged_formatter_data
    >
formatter_properties_repository_factory::merge(
    const path_derivatives_repository& pdrp,
    const inclusion_dependencies_repository& idrp,
    const enablement_repository& erp) const {

    std::unordered_map<yarn::name, merged_formatter_data> r;
    for (const auto& pair : pdrp.path_derivatives_by_name())
        r[pair.first].path_derivatives_ = pair.second;

    for (const auto& pair : idrp.inclusion_dependencies_by_name())
        r[pair.first].inclusion_dependencies = pair.second;

    for (const auto& pair : erp.enablement_by_name())
        r[pair.first].enablement = pair.second;

    return r;
}

formatter_properties_repository
formatter_properties_repository_factory::create_formatter_properties(
    const std::unordered_map<yarn::name, merged_formatter_data>& mfd) const {

    formatter_properties_repository r;
    formatter_properties_factory f;
    for (const auto& pair : mfd) {
        r.formatter_properties_by_name()[pair.first.qualified()] = f.make(
            pair.second.path_derivatives_,
            pair.second.inclusion_dependencies,
            pair.second.enablement);
    }

    return r;
}

formatter_properties_repository formatter_properties_repository_factory::
make(const dynamic::repository& srp, const dynamic::object& root_object,
    const settings::bundle_repository& brp,
    const path_derivatives_repository& pdrp, const formatters::container& fc,
    const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Building formatter properties repository.";
    const auto idrp(create_inclusion_directives_repository(srp, fc, pdrp, m));
    const auto erp(create_enablement_repository(srp, root_object, fc, m));

    registrar rg;
    initialise_registrar(fc, rg);
    const auto pc(rg.container());
    const inclusion_dependencies_builder_factory bf(erp, brp, idrp);
    const auto dprp(create_inclusion_dependencies_repository(bf, pc, m));

    const auto mfd(merge(pdrp, dprp, erp));
    const auto r(create_formatter_properties(mfd));

    BOOST_LOG_SEV(lg, debug) << "Built formatter properties repository: " << r;
    return r;
}

} } } }
