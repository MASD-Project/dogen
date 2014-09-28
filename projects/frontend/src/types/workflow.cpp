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
#include "dogen/frontend/types/source_settings.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/frontend/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("frontend.workflow"));

const std::string null_registrar("Registrar is null");
const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string invalid_archive_type("Invalid or unexpected archive type");

}

namespace dogen {
namespace frontend {

workflow::workflow(const config::knitting_settings& ks)
    : knitting_settings_(ks) {

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

std::string workflow::extension(config::archive_types at) const {
    using config::archive_types;
    switch (at) {
    case archive_types::xml: return xml_extension;
    case archive_types::text: return text_extension;
    case archive_types::binary: return binary_extension;
    default:
        break;
    }

    using dogen::utility::exception::invalid_enum_value;
    BOOST_LOG_SEV(lg, error) << invalid_archive_type;
    BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_archive_type));
}

source_settings
workflow::create_source_settings(const boost::filesystem::path& p) const {
    source_settings r;

    const auto& ts(knitting_settings_.troubleshooting());

    //FIXME: mega-hack
    using config::archive_types;
    archive_types at(ts.save_dia_model());
    if (at == archive_types::invalid)
        return r;

    r.save_pre_processed_input(true);
    boost::filesystem::path path(ts.debug_dir());
    path /= p.stem();
    path.replace_extension(extension(at));
    r.pre_processed_input_path(path);

    const auto& is(knitting_settings_.input());
    r.disable_model_module(is.disable_model_module());
    return r;
}

std::list<sml::model>
workflow::execute(const std::list<input_descriptor>& descriptors) {
    std::list<sml::model> r;
    for (const auto& d : descriptors) {
        const auto& extension(d.path().extension().string());
        auto& source(registrar().source_for_extension(extension));
        const auto ss(create_source_settings(d.path()));
        r.push_back(source.read(d, ss));
    }
    return r;
}

} }
