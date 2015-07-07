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
#include "dogen/frontend/types/registrar_error.hpp"
#include "dogen/frontend/types/frontend_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("frontend.frontend_registrar"));

const std::string exension_registerd_more_than_once(
    "Extension was registered more than once");
const std::string no_frontends("No frontends provided.");
const std::string no_frontend_for_extension(
    "No frontend available for extension:");
const std::string extension_already_registered(
    "Extension has already been registered: ");

const std::string null_frontend("Frontends supplied is null");

}

namespace dogen {
namespace frontend {

const std::unordered_map<std::string,
                         std::shared_ptr<frontend_interface>>&
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

void frontend_registrar::register_frontend_for_extension(const std::string& ext,
    std::shared_ptr<frontend_interface> s) {
    // note: not logging by design

    if (!s)
        BOOST_THROW_EXCEPTION(registrar_error(null_frontend));

    const auto i(frontends_by_extension_.insert(std::make_pair(ext, s)));
    if (!i.second)
        BOOST_THROW_EXCEPTION(
            registrar_error(extension_already_registered + ext));
}

frontend_interface& frontend_registrar::
frontend_for_extension(const std::string& ext) {
    BOOST_LOG_SEV(lg, debug) << "Looking for frontend for extension: " << ext;
    const auto i(frontends_by_extension_.find(ext));
    if (i != frontends_by_extension_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Found frontend for extension. Extension '"
                                 << ext << "' frontend: '" << i->second->id()
                                 << "'";
        return *i->second;
    }
    BOOST_LOG_SEV(lg, error) << no_frontend_for_extension << ext;
    BOOST_THROW_EXCEPTION(registrar_error(no_frontend_for_extension + ext));
}

} }
