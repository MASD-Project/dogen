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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/consumption_workflow.hpp"
#include "dogen/formatters/types/general_settings_handler.hpp"
#include "dogen/backend/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("backend.workflow"));

std::string empty;
const std::string null_registrar("Registrar is null");

}
namespace dogen {
namespace backend {

workflow::workflow(const config::knitting_settings& ks)
    : knitting_settings_(ks) {

    BOOST_LOG_SEV(lg, debug) << "Initialising backend workflow. ";
    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Found " << registrar().backends().size()
                             << " registered backends: ";

    for (const auto& b : registrar().backends())
        BOOST_LOG_SEV(lg, debug) << " backend: '" << b->id() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished initialising backend workflow. ";
}

backend::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<backend::registrar>();

    return *registrar_;
}

std::unordered_map<sml::qname, formatters::general_settings>
workflow::create_general_settings_by_qname_activity(const sml::model& m) const {
    auto h(std::make_shared<formatters::general_settings_handler>());
    std::list<std::shared_ptr<sml::consumer_interface>> l({h});
    sml::consumption_workflow w;
    w.execute(m, l);
    return h->general_settings_by_qname();
}

void workflow::register_backend(std::shared_ptr<backend_interface> b) {
    registrar().register_backend(b);
}

std::list<formatters::file> workflow::execute(const sml::model& m) const {
    create_general_settings_by_qname_activity(m);
    std::list<formatters::file> r;
    return r;
}

} }
