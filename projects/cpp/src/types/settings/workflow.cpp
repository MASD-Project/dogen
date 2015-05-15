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
#include "dogen/cpp/io/settings/bundle_io.hpp"
#include "dogen/cpp/types/settings/bundle_factory.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/settings/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.workflow"));

}

namespace dogen {
namespace cpp {
namespace settings {

std::shared_ptr<cpp::settings::registrar> workflow::registrar_;

cpp::settings::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::settings::registrar>();

    return *registrar_;
}

workflow::workflow(const dynamic::schema::object& root_object)
    : factory_(root_object, registrar().opaque_settings_factories()) { }

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating workflow.";

    registrar().validate();
    const auto& factories(registrar().opaque_settings_factories());
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(factories.begin(),
                                 factories.end())
                             << " registered opaque settings factories(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all opaque settings factories.";
    for (const auto& f : factories)
        BOOST_LOG_SEV(lg, debug) << "Key: '" << f->settings_key() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished validating workflow.";
}

bundle workflow::execute(const dynamic::schema::object& o) const {
    BOOST_LOG_SEV(lg, debug) << "Creating settings bundle.";
    bundle r(factory_.make(o));

    BOOST_LOG_SEV(lg, debug) << "Settings bundle: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finished creating settings bundle.";

    return r;
}

} } }
