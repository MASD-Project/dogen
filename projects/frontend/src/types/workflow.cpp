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
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/types/persister.hpp"
#include "dogen/frontend/io/input_descriptor_io.hpp"
#include "dogen/frontend/types/provider_settings.hpp"
#include "dogen/frontend/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("frontend.workflow"));

std::string empty;
const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string invalid_archive_type("Invalid or unexpected archive type");

}

namespace dogen {
namespace frontend {

std::shared_ptr<frontend::registrar> workflow::registrar_;

workflow::workflow(const config::knitting_settings& ks)
    : knitting_settings_(ks) {

    BOOST_LOG_SEV(lg, debug) << "Initialising frontend workflow. ";
    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << registrar().providers_by_extension().size()
                             << " registered providers: ";

    for (const auto& pair : registrar().providers_by_extension()) {
        BOOST_LOG_SEV(lg, debug) << "extension: '" << pair.first << "'"
                                 << " provider: '" << pair.second->id() << "'";
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

boost::filesystem::path workflow::
create_debug_file_path(const config::archive_types at,
    const boost::filesystem::path& original_path) const {

    const auto& ts(knitting_settings_.troubleshooting());
    boost::filesystem::path r(ts.debug_dir());
    r /= original_path.stem();
    r.replace_extension(extension(at));
    return r;
}

provider_settings
workflow::create_provider_settings(const boost::filesystem::path& p) const {
    provider_settings r;

    const auto& is(knitting_settings_.input());
    r.disable_model_module(is.disable_model_module());

    //FIXME: using dia model settings for all providers; mega-hack
    const auto& ts(knitting_settings_.troubleshooting());
    using config::archive_types;
    archive_types at(ts.save_dia_model());
    if (at == archive_types::invalid)
        return r;

    r.save_pre_processed_input(true);
    r.pre_processed_input_path(create_debug_file_path(at, p));

    return r;
}

sml::model workflow::
provide_sml_model_activity(const input_descriptor& d) const {
    const auto extension(d.path().extension().string());
    auto& provider(registrar().provider_for_extension(extension));
    const auto s(create_provider_settings(d.path()));
    return provider.provide(d, s);
}

void workflow::persist_sml_model_activity(const boost::filesystem::path& p,
    const sml::model& m) const {

    const auto& ts(knitting_settings_.troubleshooting());
    using config::archive_types;
    archive_types at(ts.save_sml_model());
    if (at == archive_types::invalid)
        return;

    const auto& dp(create_debug_file_path(at, p));
    sml::persister persister;
    persister.persist(m, dp);
}

void workflow::register_provider_for_extension(const std::string& ext,
    std::shared_ptr<model_provider_interface> s) {
    registrar().register_provider_for_extension(ext, s);
}

std::list<sml::model>
workflow::execute(const std::list<input_descriptor>& descriptors) {
    BOOST_LOG_SEV(lg, debug) << "Started executing frontend workflow. "
                             << "Descriptors: " << descriptors;

    std::list<sml::model> r;
    for (const auto& d : descriptors) {
        r.push_back(provide_sml_model_activity(d));
        persist_sml_model_activity(d.path(), r.back());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished executing frontend workflow.";
    return r;
}

} }
