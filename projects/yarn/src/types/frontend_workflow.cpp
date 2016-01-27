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
#include "dogen/yarn/io/input_descriptor_io.hpp"
#include "dogen/yarn/types/frontend_workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.frontend_workflow"));

}

namespace dogen {
namespace yarn {

std::shared_ptr<frontend_registrar> frontend_workflow::registrar_;

frontend_workflow::frontend_workflow(const dynamic::repository& rp)
    : dynamic_workflow_(rp) {

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

frontend_registrar& frontend_workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<frontend_registrar>();

    return *registrar_;
}

intermediate_model frontend_workflow::
obtain_model(const input_descriptor& d) const {
    const auto extension(d.path().extension().string());
    auto& f(registrar().frontend_for_extension(extension));
    return f.execute(dynamic_workflow_, d);
}

std::list<intermediate_model>
frontend_workflow::execute(const std::list<input_descriptor>& descriptors) {
    BOOST_LOG_SEV(lg, debug) << "Started executing. "
                             << "Descriptors: " << descriptors;

    std::list<intermediate_model> r;
    for (const auto& d : descriptors)
        r.push_back(obtain_model(d));

    BOOST_LOG_SEV(lg, debug) << "Finished executing.";
    return r;
}

} }
