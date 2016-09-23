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

inclusion_directives_repository formatter_properties_repository_factory::
create_inclusion_directives_repository(
    const dynamic::repository& srp, const formatters::container& fc,
    const locator& l, const yarn::model& m) const {
    inclusion_directives_repository_factory f;
    return f.make(srp, fc, l, m);
}

inclusion_dependencies_repository formatter_properties_repository_factory::
create_inclusion_dependencies_repository(
    const inclusion_dependencies_builder_factory& bf,
    const formatters::container& fc, const yarn::model& m) const {
    inclusion_dependencies_repository_factory f;
    return f.make(bf, fc, m);
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
    const enablement_repository& erp,
    const std::unordered_map<std::string, std::string>& fdff) const {

    std::unordered_map<yarn::name, merged_formatter_data> r;
    for (const auto& pair : pdrp.by_name()) {
        auto& entry(r[pair.first]);
        entry.path_derivatives_ = pair.second;
        entry.facet_directory_for_facet = fdff;
    }

    for (const auto& pair : idrp.by_name())
        r[pair.first].inclusion_dependencies = pair.second;

    for (const auto& pair : erp.by_name()) {
        auto& entry(r[pair.first]);
        entry.enablement = pair.second;

        for (const auto p : pair.second) {
            if (p.second)
                entry.enabled_formatters.insert(p.first);
        }
    }

    return r;
}

formatter_properties_repository
formatter_properties_repository_factory::create_formatter_properties(
    const std::unordered_map<yarn::name, merged_formatter_data>& mfd) const {

    formatter_properties_repository r;
    formatter_properties_factory f;
    for (const auto& pair : mfd) {
        r.by_id()[pair.first.id()] = f.make(
            pair.second.path_derivatives_,
            pair.second.inclusion_dependencies,
            pair.second.enablement,
            pair.second.enabled_formatters,
            pair.second.facet_directory_for_facet);
    }

    return r;
}

formatter_properties_repository formatter_properties_repository_factory::
make(const dynamic::repository& srp, const dynamic::object& root_object,
    const std::unordered_map<std::string, std::string>& fdff,
    const path_derivatives_repository& pdrp, const locator& l,
    const formatters::container& fc, const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Building formatter properties repository.";
    const auto idrp(create_inclusion_directives_repository(srp, fc, l, m));
    const auto erp(create_enablement_repository(srp, root_object, fc, m));

    const inclusion_dependencies_builder_factory bf(erp, idrp);
    const auto dprp(create_inclusion_dependencies_repository(bf, fc, m));

    const auto mfd(merge(pdrp, dprp, erp, fdff));
    const auto r(create_formatter_properties(mfd));

    BOOST_LOG_SEV(lg, debug) << "Built formatter properties repository: " << r;
    return r;
}

} } } }
