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
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/tack/types/persister.hpp"
#include "dogen/tack/io/model_io.hpp"
#include "dogen/tack/types/string_converter.hpp"
#include "dogen/tack/io/input_descriptor_io.hpp"
#include "dogen/tack/types/preprocessing_settings.hpp"
#include "dogen/tack/types/importer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("tack.importer"));

std::string empty;
const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string invalid_archive_type("Invalid or unexpected archive type");

}

namespace dogen {
namespace tack {

std::shared_ptr<file_importer_registrar> importer::registrar_;

importer::importer(const config::knitting_options& o,
    const dynamic::repository& rp)
    : knitting_options_(o), repository_(rp), dynamic_workflow_(repository_) {

    BOOST_LOG_SEV(lg, debug) << "Initialising importer. ";
    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << registrar().file_importers_by_extension().size()
                             << " registered file importers: ";

    for (const auto& pair : registrar().file_importers_by_extension()) {
        BOOST_LOG_SEV(lg, debug) << "extension: '" << pair.first << "'"
                                 << " file importer: '" << pair.second->id() << "'";
    }

    BOOST_LOG_SEV(lg, debug) << "Finished initialising importer. ";
}

file_importer_registrar& importer::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<file_importer_registrar>();

    return *registrar_;
}

std::string importer::extension(const config::archive_types at) const {
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

boost::filesystem::path importer::
create_debug_file_path(const config::archive_types at,
    const boost::filesystem::path& original_path) const {

    const auto& ts(knitting_options_.troubleshooting());
    boost::filesystem::path r(ts.debug_dir());
    r /= original_path.stem();
    r.replace_extension(extension(at));
    return r;
}

boost::optional<preprocessing_settings> importer::
create_preprocessing_settings(const boost::filesystem::path& p) const {
    //FIXME: using dia model options for all tacks; mega-hack
    const auto& to(knitting_options_.troubleshooting());
    using config::archive_types;
    archive_types at(to.save_dia_model());
    if (at == archive_types::invalid)
        return boost::optional<preprocessing_settings>();

    preprocessing_settings r;
    // FIXME
    r.directory(p);
    r.extension(extension(at));
    /*r.save_pre_processed_input(true);
    r.pre_processed_input_path(create_debug_file_path(at, p));
    */
    return r;
}

model importer::import_model(const input_descriptor& d) const {
    const auto extension(d.path().extension().string());
    auto& fi(registrar().file_importer_for_extension(extension));
    const auto s(create_preprocessing_settings(d.path()));
    return fi.import(dynamic_workflow_, d, s);
}

void importer::handle_model_persistance(const boost::filesystem::path& p,
    const model& m) const {

    const auto& to(knitting_options_.troubleshooting());
    using config::archive_types;
    archive_types at(to.save_tack_model());
    if (at == archive_types::invalid)
        return; // FIXME: should we not throw?

    const auto& dp(create_debug_file_path(at, p));
    tack::persister persister;
    persister.persist(m, dp);
}

std::list<model>
importer::import(const std::list<input_descriptor>& descriptors) {
    BOOST_LOG_SEV(lg, debug) << "Started executing importer. "
                             << "Descriptors: " << descriptors;

    std::list<tack::model> r;
    for (const auto& d : descriptors) {
        auto m(import_model(d));
        handle_model_persistance(d.path(), m);
        r.push_back(m);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished executing importer.";
    return r;
}

} }
