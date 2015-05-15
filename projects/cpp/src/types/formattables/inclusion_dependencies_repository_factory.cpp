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
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_dependencies_repository_factory"));

const std::string model_module_not_found("Model module not found for model: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_dependencies_repository_factory::inclusion_dependencies_repository_factory(
    const formatters::container& c) : container_(c) {}

inclusion_directives_repository inclusion_dependencies_repository_factory::
obtain_inclusion_directives_repository_activity(
    const dynamic::schema::repository& rp,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started obtaining inclusion directives.";

    inclusion_directives_repository_factory f;
    const auto r(f.make(rp, container_, m));

    BOOST_LOG_SEV(lg, debug) << "Finished obtaining inclusion directives.";
    return r;
}

void inclusion_dependencies_repository_factory::
initialise_registrar_activity(registrar& rg) const {
    BOOST_LOG_SEV(lg, debug) << "Started registering all providers.";
    for (const auto f : container_.all_formatters()) {
        BOOST_LOG_SEV(lg, debug) << "Registered: "
                                 << f->ownership_hierarchy().formatter_name();
        f->register_inclusion_dependencies_provider(rg);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished registering all providers.";
}

inclusion_dependencies_repository inclusion_dependencies_repository_factory::
obtain_inclusion_dependencies_activity(
    const dynamic::schema::repository& srp, const container& c,
    const inclusion_directives_repository& idrp,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started obtaining inclusion dependencies.";

    inclusion_dependencies_factory f;
    inclusion_dependencies_repository r;
    r.inclusion_dependencies_by_qname(f.make(srp, c, idrp, m));

    BOOST_LOG_SEV(lg, debug) << "Finished obtaining inclusion dependencies:";
    return r;
}

inclusion_dependencies_repository inclusion_dependencies_repository_factory::
execute(const dynamic::schema::repository& rp, const sml::model& m) const {
    registrar rg;
    initialise_registrar_activity(rg);
    const auto c(rg.container());
    const auto idrp(obtain_inclusion_directives_repository_activity(rp, m));
    const auto r(obtain_inclusion_dependencies_activity(rp, c, idrp, m));
    return r;
}

} } }
