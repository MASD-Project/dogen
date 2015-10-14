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
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/tack/types/persister.hpp"
#include "dogen/tack/io/model_io.hpp"
#include "dogen/tack/io/input_descriptor_io.hpp"
#include "dogen/tack/types/importer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("tack.importer"));

}

namespace dogen {
namespace tack {

std::shared_ptr<file_importer_registrar> importer::registrar_;

importer::importer(const dynamic::repository& rp)
    : repository_(rp), dynamic_workflow_(repository_) {

    BOOST_LOG_SEV(lg, debug) << "Initialising importer. ";
    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << registrar().file_importers_by_extension().size()
                             << " registered file importers: ";

    for (const auto& pair : registrar().file_importers_by_extension()) {
        BOOST_LOG_SEV(lg, debug) << "extension: '" << pair.first << "'"
                                 << " file importer: '" << pair.second->id()
                                 << "'";
    }

    BOOST_LOG_SEV(lg, debug) << "Finished initialising importer. ";
}

file_importer_registrar& importer::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<file_importer_registrar>();

    return *registrar_;
}

model importer::import_model(const input_descriptor& d) const {
    const auto extension(d.path().extension().string());
    auto& fi(registrar().file_importer_for_extension(extension));
    return fi.import(dynamic_workflow_, d);
}

std::list<model>
importer::import(const std::list<input_descriptor>& descriptors) {
    BOOST_LOG_SEV(lg, debug) << "Started executing importer. "
                             << "Descriptors: " << descriptors;

    std::list<tack::model> r;
    for (const auto& d : descriptors)
        r.push_back(import_model(d));

    BOOST_LOG_SEV(lg, debug) << "Finished executing importer.";
    return r;
}

} }
