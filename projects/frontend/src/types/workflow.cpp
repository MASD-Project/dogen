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
#include "dogen/frontend/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("frontend.workflow"));

const std::string null_registrar("Registrar is null");

}

namespace dogen {
namespace frontend {

workflow::workflow(const workflow_settings& ws)
    : workflow_settings_(ws), source_settings_(
        workflow_settings_.save_original_input(),
        workflow_settings_.original_input_extension(),
        workflow_settings_.disable_model_module()) {

    BOOST_LOG_SEV(lg, debug) << "Initialising frontend workflow. ";
    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Registered sources: ";
    for (const auto& pair : registrar().sources_by_extension()) {
        BOOST_LOG_SEV(lg, debug) << "extension: " << pair.first
                                 << " source: " << pair.second->id();
    }
    BOOST_LOG_SEV(lg, debug) << "Finished initialising frontend workflow. ";

}

frontend::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<frontend::registrar>();

    return *registrar_;
}


std::list<sml::model>
workflow::execute(const std::list<input_descriptor>& descriptors) {
    std::list<sml::model> r;
    for (const auto& d : descriptors) {
        const auto& extension(d.path().extension().string());
        auto& source(registrar().source_for_extension(extension));
        r.push_back(source.read(d, source_settings_));
    }
    return r;
}

} }
