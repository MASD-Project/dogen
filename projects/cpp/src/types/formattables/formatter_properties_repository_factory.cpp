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
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_repository_factory.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository_factory.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_factory.hpp"
#include "dogen/cpp/types/formattables/enablement_repository_factory.hpp"
#include "dogen/cpp/io/formattables/formatter_properties_repository_io.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formattables.path_derivatives_expander"));

}

namespace dogen {
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

path_derivatives_repository formatter_properties_repository_factory::
create_path_derivatives_repository(const config::cpp_options& opts,
    const dynamic::repository& rp, const dynamic::object& ro,
    const formatters::container& fc,
    const sml::model& m) const {
    path_derivatives_repository_factory f;
    return f.make(opts, rp, ro, fc, m);
}

inclusion_directives_repository formatter_properties_repository_factory::
create_inclusion_directives_repository(
    const dynamic::repository& srp,
    const formatters::container& fc,
    const path_derivatives_repository& pdrp,
    const sml::model& m) const {
    inclusion_directives_repository_factory f;
    return f.make(srp, fc, pdrp, m);
}

inclusion_dependencies_repository formatter_properties_repository_factory::
create_inclusion_dependencies_repository(
    const dynamic::repository& srp, const container& pc,
    const inclusion_directives_repository& idrp, const sml::model& m) const {
    inclusion_dependencies_repository_factory f;
    return f.make(srp, pc, idrp, m);
}

enablement_repository formatter_properties_repository_factory::
create_enablement_repository(const dynamic::repository& srp,
    const dynamic::object& root_object, const formatters::container& fc,
    const sml::model& m) const {
    enablement_repository_factory f;
    return f.make(srp, root_object, fc, m);
}

std::unordered_map<
    sml::qname,
    formatter_properties_repository_factory::merged_formatter_data
    >
formatter_properties_repository_factory::merge(
    const path_derivatives_repository& pdrp,
    const inclusion_dependencies_repository& idrp,
    const enablement_repository& erp) const {

    std::unordered_map<sml::qname, merged_formatter_data> r;
    for (const auto& pair : pdrp.path_derivatives_by_qname())
        r[pair.first].path_derivatives = pair.second;

    for (const auto& pair : idrp.inclusion_dependencies_by_qname())
        r[pair.first].inclusion_dependencies = pair.second;

    for (const auto& pair : erp.enablement_by_qname())
        r[pair.first].enablement = pair.second;

    return r;
}

formatter_properties_repository formatter_properties_repository_factory::
create_formatter_properties(
    const dynamic::repository& rp,
    const dynamic::object& root_object,
    const formatters::container& fc,
    const std::unordered_map<sml::qname, merged_formatter_data>& mfd) const {

    formatter_properties_repository r;
    formatter_properties_factory f(rp, root_object, fc);
    for (const auto& pair : mfd) {
        r.formatter_properties_by_qname()[pair.first] = f.make(
            pair.second.path_derivatives,
            pair.second.inclusion_dependencies,
            pair.second.enablement);
    }

    return r;
}

formatter_properties_repository formatter_properties_repository_factory::
make(const config::cpp_options& opts, const dynamic::repository& srp,
    const dynamic::object& root_object, const formatters::container& fc,
    const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Building formatter properties repository.";
    const auto& ro(root_object);
    const auto pdrp(create_path_derivatives_repository(opts, srp, ro, fc, m));
    const auto idrp(create_inclusion_directives_repository(srp, fc, pdrp, m));
    const auto erp(create_enablement_repository(srp, root_object, fc, m));

    registrar rg;
    initialise_registrar(fc, rg);
    const auto pc(rg.container());
    const auto dprp(create_inclusion_dependencies_repository(srp, pc, idrp, m));

    const auto mfd(merge(pdrp, dprp, erp));
    const auto r(create_formatter_properties(srp, ro, fc, mfd));

    BOOST_LOG_SEV(lg, debug) << "Built formatter properties repository: " << r;
    return r;
}

} } }
