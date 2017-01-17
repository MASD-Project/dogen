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
const std::string multiple_frontends(
    "More than one frontend available for file: ");
const std::string unsupported_path("No frontend is available for path:");
const std::string already_registered("Extension has already been registered: ");
const std::string null_frontend("Frontend supplied is null.");

}

namespace dogen {
namespace yarn {

void frontend_registrar::validate() const {
    if (frontends_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_frontends;
        BOOST_THROW_EXCEPTION(registrar_error(no_frontends));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << frontends_.size()
                             << " registered frontends. Details: ";

    for (const auto& pair : frontends_)
        BOOST_LOG_SEV(lg, debug) << "id: '" << pair.second->id() << "'";
}

void
frontend_registrar::register_frontend(std::shared_ptr<frontend_interface> fi) {

    // note: not logging by design
    if (!fi)
        BOOST_THROW_EXCEPTION(registrar_error(null_frontend));

    const auto i(frontends_.insert(std::make_pair(fi->id(), fi)));
    if (!i.second)
        BOOST_THROW_EXCEPTION(registrar_error(already_registered + fi->id()));
}

frontend_interface&
frontend_registrar::frontend_for_path(const boost::filesystem::path& p) {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Looking for frontend for path: " << gs;

    bool found(false);
    std::shared_ptr<frontend_interface> r;
    for (const auto& pair : frontends_) {
        const auto& fe_id(pair.first);
        const auto& fe(pair.second);
        if (fe->can_read(p)) {
            BOOST_LOG_SEV(lg, debug) << "Found frontend for path. Frontend: '"
                                     << fe_id << "'";

            if (found) {
                BOOST_LOG_SEV(lg, error) << multiple_frontends  << gs
                                         << " Frontend: '" << fe_id << "'";
                BOOST_THROW_EXCEPTION(registrar_error(multiple_frontends + gs));
            }

            found = true;
            r = pair.second;
        }
    }

    if (!found) {
        BOOST_LOG_SEV(lg, error) << unsupported_path  << gs;
        BOOST_THROW_EXCEPTION(registrar_error(unsupported_path + gs));
    }

    return *r;
}

} }
