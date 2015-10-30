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
#include "dogen/yarn/types/registrar_error.hpp"
#include "dogen/yarn/types/frontend_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.frontend_registrar"));

const std::string exension_registerd_more_than_once(
    "Extension was registered more than once");
const std::string no_frontends("No frontends provided.");
const std::string extension_unsupported(
    "No frontend is available for extension:");
const std::string already_registered("Extension has already been registered: ");
const std::string null_frontend("Frontend supplied is null.");

}

namespace dogen {
namespace yarn {

const std::unordered_map<std::string, std::shared_ptr<frontend_interface>>&
frontend_registrar::frontends_by_extension() const {
    return frontends_by_extension_;
}

void frontend_registrar::validate() const {
    if (frontends_by_extension_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_frontends;
        BOOST_THROW_EXCEPTION(registrar_error(no_frontends));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

void frontend_registrar::
register_frontend_against_extension(const std::string& extension,
    std::shared_ptr<frontend_interface> fi) {

    // note: not logging by design
    if (!fi)
        BOOST_THROW_EXCEPTION(registrar_error(null_frontend));

    auto& c(frontends_by_extension_);
    const auto i(c.insert(std::make_pair(extension, fi)));
    if (!i.second)
        BOOST_THROW_EXCEPTION(registrar_error(already_registered + extension));
}

frontend_interface& frontend_registrar::
frontend_for_extension(const std::string& extension) {
    BOOST_LOG_SEV(lg, debug) << "Looking for frontend for extension: "
                             << extension;

    auto& c(frontends_by_extension_);
    const auto i(c.find(extension));
    if (i != c.end()) {
        BOOST_LOG_SEV(lg, debug) << "Found frontend for extension. Extension: "
                                 << extension << "' frontend: '"
                                 << i->second->id() << "'";
        return *i->second;
    }
    BOOST_LOG_SEV(lg, error) << extension_unsupported  << extension;
    BOOST_THROW_EXCEPTION(registrar_error(extension_unsupported + extension));
}

} }
