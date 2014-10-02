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
#include "dogen/frontend/types/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("frontend.registrar"));

const std::string exension_registerd_more_than_once(
    "Extension was registered more than once");
const std::string no_providers("No providers provided.");
const std::string no_provider_for_extension(
    "No provider available for extension:");
const std::string extension_already_registered(
    "Extension has already been registered: ");

const std::string null_provider("Provider supplied is null");

}

namespace dogen {
namespace frontend {

const std::unordered_map<std::string,
                         std::shared_ptr<model_provider_interface>>&
    registrar::providers_by_extension() const {
    return providers_by_extension_;
}

void registrar::validate() const {
    if (providers_by_extension_.empty()) {
        // not logging by design
        BOOST_THROW_EXCEPTION(registrar_error(no_providers));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

void registrar::register_provider_for_extension(const std::string& ext,
    std::shared_ptr<model_provider_interface> s) {

    if (!s) {
        BOOST_LOG_SEV(lg, error) << null_provider;
        BOOST_THROW_EXCEPTION(registrar_error(null_provider));
    }

    const auto i(providers_by_extension_.insert(std::make_pair(ext, s)));
    if (!i.second) {
        BOOST_LOG_SEV(lg, error) << extension_already_registered << ext;
        BOOST_THROW_EXCEPTION(
            registrar_error(extension_already_registered + ext));
    }
}

model_provider_interface& registrar::
provider_for_extension(const std::string& ext) {
    BOOST_LOG_SEV(lg, debug) << "Looking for provider for extension: " << ext;
    const auto i(providers_by_extension_.find(ext));
    if (i != providers_by_extension_.end()) {
        BOOST_LOG_SEV(lg, debug) << "Found provider for extension. Extension '"
                                 << ext << "' provider: '" << i->second->id()
                                 << "'";
        return *i->second;
    }
    BOOST_LOG_SEV(lg, error) << no_provider_for_extension << ext;
    BOOST_THROW_EXCEPTION(registrar_error(no_provider_for_extension + ext));
}

} }
