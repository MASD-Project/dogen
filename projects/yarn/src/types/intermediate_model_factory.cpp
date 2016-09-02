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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/yarn/types/persister.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/io/descriptor_io.hpp"
#include "dogen/yarn/types/intermediate_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.intermediate_model_factory"));

}

namespace dogen {
namespace yarn {

std::shared_ptr<frontend_registrar> intermediate_model_factory::registrar_;

intermediate_model_factory::
intermediate_model_factory() {
    BOOST_LOG_SEV(lg, debug) << "Initialising.";
    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << registrar().frontends_by_extension().size()
                             << " registered frontends. Details: ";

    for (const auto& pair : registrar().frontends_by_extension()) {
        BOOST_LOG_SEV(lg, debug) << "extension: '" << pair.first << "' "
                                 << "id: '" << pair.second->id() << "'";
    }
    BOOST_LOG_SEV(lg, debug) << "Finished initialising. ";
}

frontend_registrar& intermediate_model_factory::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<frontend_registrar>();

    return *registrar_;
}

std::list<intermediate_model>
intermediate_model_factory::execute(const dynamic::repository& drp,
    const std::list<descriptor>& descriptors) {
    BOOST_LOG_SEV(lg, debug) << "Creating intermediate models. "
                             << "Descriptors: " << descriptors;

    const dynamic::workflow dw(drp);
    std::list<intermediate_model> r;
    for (const auto& d : descriptors) {
        auto& f(registrar().frontend_for_extension(d.extension()));
        r.push_back(f.execute(dw, d));
    }

    BOOST_LOG_SEV(lg, debug) << "Created intermediate models. Total: "
                             << r.size();
    return r;
}

} }
